/**
 * thread_pool.h
 *
 * Copyright (c) 2019-2021 Yuriy Lisovskiy
 *
 * Purpose: queued thread pool for executing functions in parallel.
 */

#pragma once

// C++ libraries.
#include <thread>
#include <queue>
#include <functional>
#include <condition_variable>

// Module definitions.
#include "./_def_.h"


__CORE_BEGIN__

class ThreadPool
{
private:
	std::string _name;
	std::mutex _lock_guard;
	std::vector<std::thread> _threads;
	size_t _threads_count;
	std::queue<std::function<void(void)>> _queue;
	std::condition_variable _cond_var;
	bool _quit = false;
	bool _is_finished;

public:
	explicit ThreadPool(std::string name, size_t threads_count=1);

	inline ~ThreadPool()
	{
		this->wait();
	}

	// Pushes and copies function to queue.
	void push(const std::function<void(void)>& func);

	// Pushes and moves function to queue.
	void push(std::function<void(void)>&& func);

	// Returns threads count.
	[[nodiscard]]
	inline size_t threads_count() const
	{
		return this->_threads_count;
	}

	// Waits until all threads finishes.
	void wait();

	inline void close()
	{
		this->wait();
	}

	// Joins all threads.
	void join();

	// Deleted constructors.
	ThreadPool(const ThreadPool& other) = delete;
	ThreadPool(ThreadPool&& other) = delete;

	// Deleted operators.
	ThreadPool& operator=(const ThreadPool& other) = delete;
	ThreadPool& operator=(ThreadPool&& other) = delete;

private:

	// Dispatches function from queue and executes it.
	void _thread_handler(int idx);
};

__CORE_END__
