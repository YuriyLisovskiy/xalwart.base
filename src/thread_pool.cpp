/**
 * thread_pool.cpp
 *
 * Copyright (c) 2019-2020 Yuriy Lisovskiy
 */

#include "./thread_pool.h"


__CORE_INTERNAL_BEGIN__

ThreadPool::ThreadPool(size_t threads_count)
{
	this->_threads_count = threads_count;
	this->_is_finished = false;
	for (int idx = 0; idx < threads_count; idx++)
	{
		this->_threads[idx] = std::thread(&ThreadPool::_thread_handler, this, idx);
	}
}

ThreadPool::~ThreadPool()
{
	this->wait();
}

void ThreadPool::push(const std::function<void(void)>& func)
{
	std::unique_lock<std::mutex> lock(this->_lock_guard);
	this->_queue.push(func);

	// Manual unlocking is done before notifying, to avoid waking up
	// the waiting thread only to block again (see notify_one for details)
	lock.unlock();
	this->_cond_var.notify_one();
}

void ThreadPool::push(std::function<void(void)>&& func)
{
	std::unique_lock<std::mutex> lock(this->_lock_guard);
	this->_queue.push(std::move(func));

	// Manual unlocking is done before notifying, to avoid waking up
	// the waiting thread only to block again (see notify_one for details)
	lock.unlock();
	this->_cond_var.notify_one();
}

size_t ThreadPool::threads_count() const
{
	return this->_threads_count;
}

void ThreadPool::wait()
{
	if (this->_is_finished)
	{
		return;
	}

	// Signal to dispatch threads that it's time to wrap up.
	std::unique_lock<std::mutex> lock(this->_lock_guard);
	this->_quit = true;

	lock.unlock();
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
	std::unique_lock<std::mutex> guard(this->_lock_guard);
	do
	{
		// Wait until we have data or a quit signal.
		this->_cond_var.wait(guard, [this] {
			return (!this->_queue.empty() || this->_quit);
		});

		// After wait, we own the lock.
		if (!this->_quit && !this->_queue.empty())
		{
			auto func = std::move(this->_queue.front());
			this->_queue.pop();

			// Unlock now that we're done messing with the queue.
			guard.unlock();
			func();
			guard.lock();
		}
	} while (!this->_quit);
}

__CORE_INTERNAL_END__
