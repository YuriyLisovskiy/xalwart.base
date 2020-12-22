/**
 * benchmark.cpp.cc
 *
 * Copyright (c) 2020 Yuriy Lisovskiy
 */

#include "./benchmark.h"

#include <chrono>
#include <cstring>
#include <sys/times.h>
#include <cstdio>


void Benchmark::_init()
{
	FILE* file;
	struct tms timeSample{};
	char line[128];

	_last_cpu = times(&timeSample);
	_last_sys_cpu = timeSample.tms_stime;
	_last_user_cpu = timeSample.tms_utime;

	file = fopen("/proc/cpuinfo", "r");
	_num_processors = 0;
	while(fgets(line, 128, file) != nullptr)
	{
		if (strncmp(line, "processor", 9) == 0)
		{
			_num_processors++;
		}
	}

	fclose(file);
}

double Benchmark::_get_usage()
{
	struct tms timeSample{};
	clock_t now;
	double percent;

	now = times(&timeSample);
	if (now <= _last_cpu || timeSample.tms_stime < _last_sys_cpu ||
	    timeSample.tms_utime < _last_user_cpu)
	{
		//Overflow detection. Just skip this value.
		percent = -1.0;
	}
	else
	{
		percent = (timeSample.tms_stime - _last_sys_cpu) +
		          (timeSample.tms_utime - _last_user_cpu);
		percent /= (now - _last_cpu);
		percent /= _num_processors;
		percent *= 100;
	}

	_last_cpu = now;
	_last_sys_cpu = timeSample.tms_stime;
	_last_user_cpu = timeSample.tms_utime;

	return percent;
}

Benchmark::Benchmark(std::function<void()> func) : _func(std::move(func))
{
}

double Benchmark::mem_used() const
{
	return this->_mem_used;
}

double Benchmark::avg_time() const
{
	return this->_avg_time;
}

void Benchmark::run(size_t iterations)
{
	this->_init();
	double sum = 0;
	size_t calls_count = iterations;
	for (size_t i = 0; i < calls_count; i++)
	{
		auto start = std::chrono::high_resolution_clock::now();
		this->_func();
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
		sum += (double)duration.count();
	}

	this->_mem_used = this->_get_usage();
	this->_avg_time = sum / (calls_count * 1.0);
}
