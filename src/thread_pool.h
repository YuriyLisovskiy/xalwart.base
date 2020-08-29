/*
 * Copyright (c) 2019-2020 Yuriy Lisovskiy
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * core/thread_pool.h
 *
 * Purpose:
 * 	Queued thread pool for executing functions in parallel.
 */

#pragma once

// C++ libraries.
#include <thread>
#include <queue>
#include <functional>
#include <condition_variable>

// Module definitions.
#include "./_def_.h"


__CORE_INTERNAL_BEGIN__

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
	explicit ThreadPool(size_t threads_count = 1);
	~ThreadPool();

	/// Pushes and copies function to queue.
	void push(const std::function<void(void)>& func);

	/// Pushes and moves function to queue.
	void push(std::function<void(void)>&& func);

	/// Returns threads count.
	[[nodiscard]] size_t threads_count() const;

	/// Waits until all threads finishes.
	void wait();

	void join();

	/// Deleted constructors.
	ThreadPool(const ThreadPool& other) = delete;
	ThreadPool(ThreadPool&& other) = delete;

	/// Deleted operators.
	ThreadPool& operator=(const ThreadPool& other) = delete;
	ThreadPool& operator=(ThreadPool&& other) = delete;

private:

	/// Dispatches function from queue and executes it.
	void _thread_handler(int idx);
};

__CORE_INTERNAL_END__
