/**
 * event_loop.h
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
#include <typeindex>
#include <list>

// Module definitions.
#include "./_def_.h"


__CORE_BEGIN__

class Event
{
};

// Represent a function that will be called with an event.
using EventListener = std::function<void(Event&)>;

// Utility function for our Event map.
template<typename T>
auto get_event_type()
{
	return std::type_index(typeid(T));
}

class EventLoop final
{
private:

	// Vector of workers.
	std::vector<std::thread> _threads;

	// Indicates whether thread pool must finish all events
	// and close threads.
	bool _quit = false;

	// Indicates whether workers are running or not.
	bool _is_finished;

	// Guard for blocking queue when injecting new events.
	std::mutex _event_queue_mutex;

	// Queue of events which is waiting to be run.
	std::queue<std::pair<std::unique_ptr<Event>, EventListener>> _event_queue;

	// Condition variable for notification when pushing new events.
	std::condition_variable _cond_var;

	// Event listeners to be called for injected events.
	std::map<std::type_index, std::list<EventListener>> _event_listeners;

	// Guard for blocking queue when injecting new events.
	std::mutex _event_listeners_mutex;

private:
	void _join_threads();

	void _run();

public:
	inline explicit EventLoop(size_t threads_count)
	{
		this->_is_finished = false;
		for (size_t idx = 0; idx < threads_count; idx++)
		{
			this->_threads.emplace_back(&EventLoop::_run, this);
		}
	}

	inline ~EventLoop()
	{
		this->wait_for_threads();
	}

	template<class EventType>
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
	}

	void wait_for_threads();
};

__CORE_END__
