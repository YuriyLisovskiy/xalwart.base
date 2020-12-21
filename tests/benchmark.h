/**
 * benchmark.h
 *
 * Copyright (c) 2020 Yuriy Lisovskiy
 *
 * Purpose: calculation of average running time and memory usage.
 */

#pragma once

#include <functional>


class Benchmark
{
private:
	std::function<void()> _func;
	double _mem_used{};
	double _avg_time{};

	clock_t _last_cpu{};
	clock_t _last_sys_cpu{};
	clock_t _last_user_cpu{};
	int _num_processors{};

	void _init();
	double _get_usage();

public:
	explicit Benchmark(std::function<void()> func);
	[[nodiscard]] double mem_used() const;
	[[nodiscard]] double avg_time() const;
	void run(size_t iterations);
};
