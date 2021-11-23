/**
 * workers/threaded_worker.cpp
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 */

#include "./threaded_worker.h"


__MAIN_NAMESPACE_BEGIN__

void ThreadedWorker::stop()
{
	if (this->_is_finished || this->_quit)
	{
		return;
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(100));

	// Signal to dispatch threads that it's time to wrap up.
	{
		std::unique_lock<std::mutex> lock(this->_task_queue_mutex);
		this->_quit = true;
	}

	this->_cond_var.notify_all();
	this->_join_threads();

	this->_is_finished = true;
}

void ThreadedWorker::inject_task(const std::type_index& task_type, std::unique_ptr<Task> task)
{
	{
		std::unique_lock<std::mutex> listeners_guard(this->_task_listeners_mutex);
		auto& listeners = this->_task_listeners[task_type];
		std::lock_guard<std::mutex> task_queue_guard(this->_task_queue_mutex);
		std::for_each(listeners.begin(), listeners.end(), [&](const auto& listener)
		{
			this->_task_queue.emplace(std::move(task), listener);
		});
	}

	this->_cond_var.notify_one();
}

void ThreadedWorker::_join_threads()
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

void ThreadedWorker::_run()
{
	while (!this->_quit)
	{
		std::unique_lock<std::mutex> guard(this->_task_queue_mutex);

		// Wait until we have data or a quit signal.
		this->_cond_var.wait(guard, [this]{
			return !this->_task_queue.empty() || this->_quit;
		});
		if (this->_quit)
		{
			break;
		}

		if (this->_task_queue.empty())
		{
			continue;
		}

		auto task = std::move(this->_task_queue.front());
		this->_task_queue.pop();
		guard.unlock();

		task.second(*task.first);
	}
}

__MAIN_NAMESPACE_END__
