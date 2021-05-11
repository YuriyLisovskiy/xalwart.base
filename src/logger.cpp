/**
 * logger.cpp
 *
 * Copyright (c) 2019-2021 Yuriy Lisovskiy
 */

#include "./logger.h"

// C++ libraries.
#include <cstring>

// Core libraries.
#include "./datetime.h"


__LOG_BEGIN__

void FileStream::write(const std::string& text)
{
	if (this->_file->is_open())
	{
		this->_file->write(text);
	}
}

void Config::add_console_stream()
{
	if (!this->_has_cout)
	{
		this->streams.push_back(std::make_shared<ConsoleStream>());
		this->_has_cout = true;
	}
}

void Config::add_file_stream(const std::string& fp)
{
	auto fs = std::make_shared<FileStream>(fp);
	if (fs->is_valid())
	{
		this->streams.push_back(fs);
	}
}

void Logger::_log(
	const std::string& msg, int line, const char* function,
	const char* file, Logger::log_level_enum level
)
{
	this->_thread_pool->push([this, level, line, file, function, msg]() -> void {
		std::string level_name;
		bool is_enabled;
		Color colour;
		switch (level)
		{
			case Logger::log_level_enum::ll_warning:
				level_name = "[warning]";
				is_enabled = this->_config.enable_warning;
				colour = Color::YELLOW;
				break;
			case Logger::log_level_enum::ll_error:
				level_name = "[error]";
				is_enabled = this->_config.enable_error;
				colour = Color::RED;
				break;
			case Logger::log_level_enum::ll_debug:
				level_name = "[debug]";
				is_enabled = this->_config.enable_debug;
				colour = Color::MAGENTA;
				break;
			case Logger::log_level_enum::ll_fatal:
				level_name = "[fatal]";
				is_enabled = this->_config.enable_fatal;
				colour = Color::BOLD_RED;
				break;
			case Logger::log_level_enum::ll_trace:
				level_name = "[trace]";
				is_enabled = this->_config.enable_trace;
				colour = Color::BOLD_RED;
				break;
			default:
				level_name = "[info]";
				is_enabled = this->_config.enable_info;
				colour = Color::CYAN;
				break;
		}

		if (!is_enabled)
		{
			return;
		}

		std::string full_msg;
		if (line != 0 && std::strlen(file) > 0 && std::strlen(function) > 0)
		{
			full_msg = "\n\tFile \"" + std::string(file) + "\", line "
			           + std::to_string(line) + ", in "
			           + std::string(function) + "\n" + msg;
		}
		else
		{
			full_msg = " " + msg;
		}

		std::string result;
		if (level != ll_trace)
		{
			result = "[" + dt::Datetime::now().strftime("%F %T") + "] ";
		}

		result += level_name + ":" + full_msg;
		this->_write_to_stream(result, colour);
	});
}

void Logger::_write_to_stream(const std::string& msg, Color colour, char end)
{
	for (auto& stream : this->_config.streams)
	{
		auto is_console = stream->is_console();
		if (is_console)
		{
			this->_set_colour(colour);
		}

		stream->write(msg + (end != '\0' ? std::string(1, end) : ""));
		if (is_console)
		{
			this->_set_colour(Color::DEFAULT);
		}

		stream->flush();
	}
}

void Logger::_set_colour(Color colour) const
{
#if defined(__unix__) || defined(__linux__)
	if (this->use_output_colors)
	{
		if (this->_colors.find(colour) == this->_colors.end())
		{
			colour = Color::DEFAULT;
		}

		std::cout << this->_colors.at(colour);
	}
#endif
}

__LOG_END__
