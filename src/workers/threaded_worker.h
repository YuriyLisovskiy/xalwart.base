/**
 * workers/threaded_worker.h
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 */

#pragma once

// C++ libraries.
#include <condition_variable>
#include <functional>
#include <map>
#include <mutex>
#include <queue>
#include <thread>
#include <list>

// Module definitions.
#include "../_def_.h"

// Base libraries.
#include "./abstract_worker.h"


__MAIN_NAMESPACE_BEGIN__

class ThreadedWorker final : public AbstractWorker
{
public:
	inline explicit ThreadedWorker(size_t threads_count)
	{
		this->_is_finished = false;
		for (size_t idx = 0; idx < threads_count; idx++)
		{
			this->_threads.emplace_back(&ThreadedWorker::_run, this);
		}
	}

	ThreadedWorker(const ThreadedWorker& other) = delete;
	ThreadedWorker& operator=(const ThreadedWorker& other) = delete;

	inline ~ThreadedWorker() override
	{
		this->stop();
	}

	void stop() override;

protected:
	inline void add_task_listener(
		const std::type_index& task_type, const AbstractWorker::TaskListener& listener
	) override
	{
		std::lock_guard<std::mutex> guard(this->_task_listeners_mutex);
		this->_task_listeners[task_type].push_back(listener);
	}

	void inject_task(const std::type_index& task_type, std::unique_ptr<Task> task) override;

private:
	std::vector<std::thread> _threads;

	// Indicates whether thread pool must finish all tasks
	// and close threads.
	bool _quit = false;

	// Indicates whether workers are running or not.
	bool _is_finished;

	// Queue of tasks which is waiting to be run.
	std::queue<std::pair<std::unique_ptr<AbstractWorker::Task>, AbstractWorker::TaskListener>> _task_queue;

	// Condition variable for notification when pushing new tasks.
	std::condition_variable _cond_var;

	// Task listeners to be called for injected tasks.
	std::map<std::type_index, std::list<AbstractWorker::TaskListener>> _task_listeners;

	// Guard for blocking queue when injecting new tasks.
	std::mutex _task_queue_mutex;

	// Guard for blocking listeners when creating new task listener.
	std::mutex _task_listeners_mutex;

	void _join_threads();

	void _run();
};

__MAIN_NAMESPACE_END__
