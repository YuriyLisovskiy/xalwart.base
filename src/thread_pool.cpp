/**
 * thread_pool.cpp
 *
 * Copyright (c) 2019-2020 Yuriy Lisovskiy
 */

#include "./thread_pool.h"

#include <iostream>


__CORE_BEGIN__

ThreadPool::ThreadPool(std::string name, size_t threads_count) : _name(std::move(name))
{
	this->_threads_count = threads_count;

//	std::cerr << "THREADS: " << this->_threads_count << '\n';

	this->_is_finished = false;
	for (size_t idx = 0; idx < threads_count; idx++)
	{
		this->_threads.emplace_back(&ThreadPool::_thread_handler, this, idx);
	}
}

ThreadPool::~ThreadPool()
{
	this->wait();
}

void ThreadPool::push(const std::function<void(void)>& func)
{
	{
		std::unique_lock<std::mutex> lock(this->_lock_guard);
		this->_queue.push(func);
	}

	// Manual unlocking is done before notifying, to avoid waking up
	// the waiting thread only to block again (see notify_one for details)
//	lock.unlock();
	this->_cond_var.notify_all();
}

void ThreadPool::push(std::function<void(void)>&& func)
{
	{
		std::unique_lock<std::mutex> lock(this->_lock_guard);
		this->_queue.push(std::move(func));
	}

	// Manual unlocking is done before notifying, to avoid waking up
	// the waiting thread only to block again (see notify_one for details)
//	lock.unlock();
	this->_cond_var.notify_all();
}

size_t ThreadPool::threads_count() const
{
	return this->_threads_count;
}

void ThreadPool::wait()
{
	if (this->_is_finished || this->_quit)
	{
		return;
	}

//	std::cerr << "Waiting [" << this->_name << "]...\n";

	// Signal to dispatch threads that it's time to wrap up.
	{
		std::unique_lock<std::mutex> lock(this->_lock_guard);
		this->_quit = true;
	}

//	lock.unlock();
	this->_cond_var.notify_all();

	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	this->join();

	this->_is_finished = true;

//	std::cerr << "Waited [" << this->_name << "].\n";
}

void ThreadPool::close()
{
	this->wait();
}

void ThreadPool::join()
{
	std::cerr << "Joining [" << this->_name << "]...\n";

	// Wait for threads to finish before we exit.
	for (auto& thread : this->_threads)
	{
		if (thread.joinable())
		{
			thread.join();
		}
	}

	std::cerr << "Joined [" << this->_name << "].\n";
}

void ThreadPool::_thread_handler(int idx)
{
//	std::function<void()> job;
//	while (!this->_quit)
//	{
//		{
//			std::unique_lock<std::mutex> lock(this->_lock_guard);
//			this->_cond_var.wait(lock, [this] {
//				return (!this->_queue.empty() || this->_quit);
//			});
//			job = this->_queue.front();
//			this->_queue.pop();
//		}
//
//		std::cerr << "STARTED [" << idx << "]\n";
//		job();
//		std::cerr << "FINISHED [" << idx << "]\n";
//	}

//	std::unique_lock<std::mutex> guard(this->_lock_guard);

	while (!this->_quit)
	{
//		std::cerr << "[" << this->_name << "] LOCKED [" << idx << "]\n";

		std::unique_lock<std::mutex> guard(this->_lock_guard);
//		std::cerr << "Locked [" << idx << "]\n";

		// Wait until we have data or a quit signal.
		this->_cond_var.wait(guard, [this] {
			return (!this->_queue.empty() || this->_quit);
		});

//		std::cerr << "[" << this->_name << "] " << (this->_quit ? "RELEASED" : "NOTIFIED") << " [" << idx << "]\n";

//		std::cerr << "[" << this->_name << "] NOTIFIED [" << idx << "], QUIT: " << this->_quit << ", SIZE: " << this->_queue.size() << "\n";

		if (this->_quit)
		{
			break;
		}

		if (this->_queue.empty())
		{
			continue;
		}

//		std::cerr << '[' << idx << "]QUEUE SIZE: " << this->_queue.size() << '\n';

		// After wait, we own the lock.
//		if (!this->_quit && !this->_queue.empty())
//		{
//			std::unique_lock<std::mutex> guard(this->_lock_guard);
		auto func = this->_queue.front();

//		std::cerr << "[" << this->_name << "] GOT NEW JOB [" << idx << "]\n";

		this->_queue.pop();

//			std::cerr << "[" << this->_name << "] Q SIZE: " << this->_queue.size() << '\n';

//			std::cerr << "[" << this->_name << "] job started in [" << idx << "]\n";
			// Unlock now that we're done messing with the queue.
			guard.unlock();
//			std::cerr << "STARTED [" << idx << "]\n";

			func();

//			guard.lock();
//			std::cerr << "[" << this->_name << "] job finished in [" << idx << "]\n";
//			guard.unlock();

//			std::cerr << "FINISHED [" << idx << "]\n";
//			guard.lock();
//		}

//		std::cerr << '[' << idx << "]QUEUE SIZE: " << this->_queue.size() << '\n';
	}

//	std::cerr << "FINISHED [" << idx << "]\n";
}

__CORE_END__
