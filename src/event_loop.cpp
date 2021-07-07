/**
 * event_loop.cpp
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 */

#include "./event_loop.h"


__MAIN_NAMESPACE_BEGIN__

void EventLoop::_join_threads()
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

void EventLoop::_run()
{
	while (!this->_quit)
	{
		std::unique_lock<std::mutex> guard(this->_event_queue_mutex);

		// Wait until we have data or a quit signal.
		this->_cond_var.wait(guard, [&]{
			return !this->_event_queue.empty() || this->_quit;
		});
		if (this->_quit)
		{
			break;
		}

		if (this->_event_queue.empty())
		{
			continue;
		}

		auto event = std::move(this->_event_queue.front());
		this->_event_queue.pop();
		guard.unlock();

		event.second(*event.first);
	}
}

void EventLoop::wait_for_threads()
{
	if (this->_is_finished || this->_quit)
	{
		return;
	}

	// Signal to dispatch threads that it's time to wrap up.
	{
		std::unique_lock<std::mutex> lock(this->_event_queue_mutex);
		this->_quit = true;
	}

	this->_cond_var.notify_all();

	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	this->_join_threads();

	this->_is_finished = true;
}

__MAIN_NAMESPACE_END__
