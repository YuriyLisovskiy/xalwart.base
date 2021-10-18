/**
 * logger.cpp
 *
 * Copyright (c) 2019-2021 Yuriy Lisovskiy
 */

#include "./logger.h"

// C++ libraries.
#include <cstring>

// Base libraries.
#include "./datetime.h"


__LOG_BEGIN__

Logger::Logger(Config cfg) : config(std::move(cfg))
{
	this->config.add_console_stream();
	this->worker = std::make_unique<ThreadedWorker>(THREADS_COUNT);
	this->worker->AbstractWorker::add_task_listener<LogTask>([this](AbstractWorker*, LogTask& task)
	{
		auto level_data = task.level.data();
		std::string full_message;
		if (task.line != 0 && std::strlen(task.file) > 0 && std::strlen(task.function) > 0)
		{
			full_message = "\n\tFile \"" + std::string(task.file) + "\", line "
				+ std::to_string(task.line) + ", in "
				+ std::string(task.function) + "\n" + task.message;
		}
		else
		{
			full_message = " " + task.message;
		}

		std::string result;
		if (task.level.operator!=(Level::Trace))
		{
			result = "[" + dt::Datetime::now().strftime("%F %T") + "] ";
		}

		result += "[" + level_data.name + "]:" + full_message;
		this->_write_to_stream(result, level_data.color);
	});
}

void Logger::_log(
	const std::string& message, int line, const char* function, const char* file, Level level
)
{
	if (this->config.is_enabled(level))
	{
		this->worker->AbstractWorker::inject_task<LogTask>(LogTask{
			.level = level, .message = message, .line = line, .function = function, .file = file
		});
	}
}

void Logger::_write_to_stream(const std::string& message, Color color, char end)
{
	auto full_message = message + (end != '\0' ? std::string(1, end) : "");
	for (auto& stream : this->config.streams)
	{
		auto is_console = stream->is_console();
		this->_set_color(color, is_console);
		stream->write(full_message);
		this->_set_color(Color::Default, is_console);
		stream->flush();
	}
}

void Logger::_set_color(Color color, bool is_console_stream) const
{
	if (!is_console_stream)
	{
		return;
	}

#if defined(__linux__) || defined(__mac__)
	if (this->config.use_colors)
	{
		if (this->_colors.find(color) == this->_colors.end())
		{
			color = Color::Default;
		}

		std::cout << this->_colors.at(color);
	}
#endif // __linux__ || __mac__
}

__LOG_END__
