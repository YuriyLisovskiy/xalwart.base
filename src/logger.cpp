/**
 * logger.cpp
 *
 * Copyright (c) 2019-2021 Yuriy Lisovskiy
 */

#include "./logger.h"

// C++ libraries.
#include <iostream>
#include <cstring>

// Core libraries.
#include "./datetime.h"
#include "./path.h"


__LOG_BEGIN__

bool Stream::is_file()
{
	return false;
}

bool Stream::is_console()
{
	return false;
}

void ConsoleStream::write(const std::string& text)
{
	std::cout << text;
}

void ConsoleStream::flush()
{
	std::cout.flush();
}

bool ConsoleStream::is_console()
{
	return true;
}

FileStream::FileStream(const std::string& fp)
{
	this->_file = std::make_shared<core::File>(fp, "a");
	this->_file->open();
}

FileStream::~FileStream()
{
	this->_file->close();
}

void FileStream::write(const std::string& text)
{
	if (this->_file->is_open())
	{
		this->_file->write_str(text);
	}
}

bool FileStream::is_file()
{
	return true;
}

void FileStream::flush()
{
	this->_file->flush();
}

bool FileStream::is_valid()
{
	return this->_file && this->_file->is_open();
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

void Logger::use_colors(bool use)
{
	this->use_output_colors = use;
}

Logger::~Logger()
{
	this->_thread_pool->wait();
}

Logger::Logger(const Config& cfg) : use_output_colors(false)
{
	std::cerr << "Logger initialized\n";

	this->_config = cfg;
	this->_thread_pool = std::make_shared<core::ThreadPool>("logger", 1);
}

void Logger::info(const std::string& msg, int line, const char* function, const char* file)
{
	this->_log(msg, line, function, file, Logger::log_level_enum::ll_info);
}

void Logger::debug(const std::string& msg, int line, const char* function, const char* file)
{
	this->_log(msg, line, function, file, Logger::log_level_enum::ll_debug);
}

void Logger::warning(const std::string& msg, int line, const char* function, const char* file)
{
	this->_log(msg, line, function, file, Logger::log_level_enum::ll_warning);
}

void Logger::error(const std::string& msg, int line, const char* function, const char* file)
{
	this->_log(msg, line, function, file, Logger::log_level_enum::ll_error);
}

void Logger::fatal(const std::string& msg, int line, const char* function, const char* file)
{
	this->_log(msg, line, function, file, Logger::log_level_enum::ll_fatal);
}

void Logger::trace(const std::string& msg, int line, const char* function, const char* file)
{
	this->_log(msg, line, function, file, Logger::log_level_enum::ll_trace);
}

void Logger::set_config(const Config& config)
{
	this->_config = config;
}

void Logger::print(const std::string& msg, Color colour, char end)
{
	if (this->_config.enable_print)
	{
		this->_write_to_stream(msg, colour, end);
	}
}

void Logger::print(const char* msg, Color colour, char end)
{
	this->print(std::string(msg), colour, end);
}

void Logger::info(const core::BaseException& exc)
{
	this->info(exc.get_message(), exc.line(), exc.function(), exc.file());
}

void Logger::debug(const core::BaseException& exc)
{
	this->debug(exc.get_message(), exc.line(), exc.function(), exc.file());
}

void Logger::warning(const core::BaseException& exc)
{
	this->warning(exc.get_message(), exc.line(), exc.function(), exc.file());
}

void Logger::error(const core::BaseException& exc)
{
	this->error(exc.get_message(), exc.line(), exc.function(), exc.file());
}

void Logger::fatal(const core::BaseException& exc)
{
	this->fatal(exc.get_message(), exc.line(), exc.function(), exc.file());
}

void Logger::info(const core::Error& exc)
{
	this->info(exc.get_message(), exc.line, exc.func.c_str(), exc.file.c_str());
}

void Logger::debug(const core::Error& exc)
{
	this->debug(exc.get_message(), exc.line, exc.func.c_str(), exc.file.c_str());
}

void Logger::warning(const core::Error& exc)
{
	this->warning(exc.get_message(), exc.line, exc.func.c_str(), exc.file.c_str());
}

void Logger::error(const core::Error& exc)
{
	this->error(exc.get_message(), exc.line, exc.func.c_str(), exc.file.c_str());
}

void Logger::fatal(const core::Error& exc)
{
	this->fatal(exc.get_message(), exc.line, exc.func.c_str(), exc.file.c_str());
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

		stream->write(msg + std::string(1, end));
		if (is_console)
		{
			this->_set_colour(Color::DEFAULT);
		}

		stream->flush();
	}
}

void Logger::_set_colour(Color colour)
{
#if defined(__unix__) || defined(__linux__)
	if (this->use_output_colors)
	{
		if (this->_colors.find(colour) == this->_colors.end())
		{
			colour = Color::DEFAULT;
		}

		std::cout << this->_colors[colour];
	}
#endif
}

__LOG_END__
