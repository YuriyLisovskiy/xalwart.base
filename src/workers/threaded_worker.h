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

//class Event
//{
//};

// Represent a function that will be called with an event.
//using EventListener = std::function<void(Event&)>;

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

/*	template<class EventType>
	inline void add_event_listener(const std::function<void(EventLoop&, EventType&)>& listener)
	{
		std::lock_guard<std::mutex> guard(this->_event_listeners_mutex);
		this->_event_listeners[get_event_type<EventType>()].push_back([this, listener](auto& e)
		{
			listener(*this, static_cast<EventType&>(e));
		});
	}

	// Push the event to queue to be handled by the event loop.
	template <class EventT, typename ...EventParamsT>
	inline void inject_event(EventParamsT&&... params)
	{
		{
			std::unique_lock<std::mutex> listeners_guard(this->_event_listeners_mutex);
			auto& listeners = this->_event_listeners[get_event_type<EventT>()];
			std::lock_guard<std::mutex> event_queue_guard(this->_event_queue_mutex);
			std::for_each(listeners.begin(), listeners.end(), [&](const auto& listener)
			{
				this->_event_queue.emplace(
					std::make_unique<EventT>(std::forward<EventParamsT>(params)...), listener
				);
			});
		}

		this->_cond_var.notify_all();
	}*/

private:

	// Vector of workers.
	std::vector<std::thread> _threads;

	// Indicates whether thread pool must finish all tasks
	// and close threads.
	bool _quit = false;

	// Indicates whether workers are running or not.
	bool _is_finished;

	// Guard for blocking queue when injecting new tasks.
	std::mutex _task_queue_mutex;

	// Queue of tasks which is waiting to be run.
	std::queue<std::pair<std::unique_ptr<AbstractWorker::Task>, AbstractWorker::TaskListener>> _task_queue;

	// Condition variable for notification when pushing new tasks.
	std::condition_variable _cond_var;

	// Task listeners to be called for injected tasks.
	std::map<std::type_index, std::list<AbstractWorker::TaskListener>> _task_listeners;

	// Guard for blocking queue when injecting new tasks.
	std::mutex _task_listeners_mutex;

	void _join_threads();

	void _run();
};

__MAIN_NAMESPACE_END__
