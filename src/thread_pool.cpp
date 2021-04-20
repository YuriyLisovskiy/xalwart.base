/**
 * thread_pool.cpp
 *
 * Copyright (c) 2019-2021 Yuriy Lisovskiy
 */

#include "./thread_pool.h"


__MAIN_NAMESPACE_BEGIN__

ThreadPool::ThreadPool(std::string name, size_t threads_count) : _name(std::move(name))
{
	this->_threads_count = threads_count;
	this->_is_finished = false;
	for (size_t idx = 0; idx < threads_count; idx++)
	{
		this->_threads.emplace_back(&ThreadPool::_thread_handler, this, idx);
	}
}

void ThreadPool::push(const std::function<void(void)>& func)
{
	{
		std::unique_lock<std::mutex> lock(this->_lock_guard);
		this->_queue.push(func);
	}

	this->_cond_var.notify_all();
}

void ThreadPool::push(std::function<void(void)>&& func)
{
	{
		std::unique_lock<std::mutex> lock(this->_lock_guard);
		this->_queue.push(std::move(func));
	}

	this->_cond_var.notify_all();
}

void ThreadPool::wait()
{
	if (this->_is_finished || this->_quit)
	{
		return;
	}

	// Signal to dispatch threads that it's time to wrap up.
	{
		std::unique_lock<std::mutex> lock(this->_lock_guard);
		this->_quit = true;
	}

	this->_cond_var.notify_all();

	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	this->join();

	this->_is_finished = true;
}

void ThreadPool::join()
{
	// Wait for threads to finish before we exit.
	for (auto& thread : this->_threads)
	{
		if (thread.joinable())
		{
			thread.join();
		}
	}
}

void ThreadPool::_thread_handler(int idx)
{
	while (!this->_quit)
	{
		std::unique_lock<std::mutex> guard(this->_lock_guard);

		// Wait until we have data or a quit signal.
		this->_cond_var.wait(guard, [this] {
			return (!this->_queue.empty() || this->_quit);
		});
		if (this->_quit)
		{
			break;
		}

		if (this->_queue.empty())
		{
			continue;
		}

		auto func = this->_queue.front();
		this->_queue.pop();

		guard.unlock();
		func();
	}
}

__MAIN_NAMESPACE_END__
