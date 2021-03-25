/**
 * thread_pool.h
 *
 * Copyright (c) 2019-2021 Yuriy Lisovskiy
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

// Queued thread pool for executing functions in parallel.
class ThreadPool
{
private:

	// Thread pool name.
	std::string _name;

	// Guard for blocking queue when pushing a new tasks.
	std::mutex _lock_guard;

	// Vector of workers of thread pool.
	std::vector<std::thread> _threads;

	// Number of parallel threads.
	size_t _threads_count;

	// Queue of functions which is waiting to be run.
	std::queue<std::function<void(void)>> _queue;

	// Condition variable for threads' notification
	// when pushing a new tasks.
	std::condition_variable _cond_var;

	// Indicates whether thread pool must finish all tasks
	// and close threads.
	bool _quit = false;

	// Indicates whether workers are running or not.
	bool _is_finished;

public:

	// Constructor.
	//
	// `name`: thread pool name, used for debugging.
	// `threads_count`: number of parallel threads.
	explicit ThreadPool(std::string name, size_t threads_count=1);

	// Waits until all threads finishes.
	inline ~ThreadPool()
	{
		this->wait();
	}

	// Pushes and copies function to queue.
	//
	// `func`: function to call.
	void push(const std::function<void(void)>& func);

	// Pushes and moves function to queue.
	//
	// `func`: function to call.
	void push(std::function<void(void)>&& func);

	// Returns threads count.
	[[nodiscard]]
	inline size_t threads_count() const
	{
		return this->_threads_count;
	}

	// Waits until all threads finishes.
	void wait();

	// Waits for threads shutdown.
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
	//
	// `idx`: thread index.
	void _thread_handler(int idx);
};

__CORE_END__
