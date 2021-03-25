/**
 * logger.h
 *
 * Copyright (c) 2019-2021 Yuriy Lisovskiy
 *
 * Logger base, streams and simple logger.
 */

#pragma once

// C++ libraries.
#include <map>
#include <iostream>

// Module definitions.
#include "./_def_.h"

// Core libraries.
#include "./exceptions.h"
#include "./file.h"
#include "./thread_pool.h"
#include "./error.h"


__LOG_BEGIN__

class Stream
{
public:
	virtual ~Stream() = default;

	// Assumes writing of text to stream.
	virtual void write(const std::string& text) = 0;

	// Assumes flushing the stream.
	virtual void flush() = 0;

	// Must return `true` for file streams, `false` otherwise.
	[[nodiscard]]
	virtual inline bool is_file() const
	{
		return false;
	}

	// Must return true only for console stream.
	[[nodiscard]]
	virtual inline bool is_console() const
	{
		return false;
	}
};

class ConsoleStream final : public Stream
{
public:

	// Writes string to console.
	//
	// `text`: string to write.
	inline void write(const std::string& text) override
	{
		std::cout << text;
	}

	// Forces `std::cout` to print a string.
	inline void flush() override
	{
		std::cout.flush();
	}

	// Indicates that this is a console stream.
	[[nodiscard]]
	inline bool is_console() const override
	{
		return true;
	}
};

class FileStream : public Stream
{
private:

	// File with log messages.
	std::shared_ptr<core::File> _file;

public:

	// Creates file from given path with 'append' mode
	// and opens it immediately.
	//
	// `fp`: path to file.
	explicit FileStream(const std::string& fp)
	{
		this->_file = std::make_shared<core::File>(fp, "a");
		this->_file->open();
	}

	// Closes file with log messages.
	inline ~FileStream() override
	{
		this->_file->close();
	}

	// Writes string to file.
	void write(const std::string& text) override;

	// Indicates that this is a file stream.
	[[nodiscard]]
	inline bool is_file() const override
	{
		return true;
	}

	// Forces file to save string.
	inline void flush() override
	{
		this->_file->flush();
	}

	// Returns `true` if file is initialized and open,
	// `false` otherwise.
	inline bool is_valid()
	{
		return this->_file && this->_file->is_open();
	}
};

class Config final
{
private:

	// Indicates whether console stream is added or not.
	bool _has_cout = false;

public:
	bool enable_info = true;
	bool enable_debug = true;
	bool enable_warning = true;
	bool enable_error = true;
	bool enable_fatal = true;
	bool enable_trace = true;
	bool enable_print = true;

	// A vector of streams to log into.
	std::vector<std::shared_ptr<Stream>> streams;

	// Appends console stream.
	void add_console_stream();

	// Appends a file stream with given file path.
	void add_file_stream(const std::string& fp);
};

// An interface for logger.
class ILogger
{
public:
	enum Color
	{
		DEFAULT,
		BLACK,
		RED,
		GREEN,
		YELLOW,
		BLUE,
		MAGENTA,
		CYAN,
		WHITE,
		BOLD_BLACK,
		BOLD_RED,
		BOLD_GREEN,
		BOLD_YELLOW,
		BOLD_BLUE,
		BOLD_MAGENTA,
		BOLD_CYAN,
		BOLD_WHITE,
	};

	// Set indicator whether to use colours in console or not.
	virtual void use_colors(bool use) = 0;

	// Default destructor.
	virtual ~ILogger() = default;

	// Logs given text, line, function name and file name with
	// 'info' logging level if it is enabled in config.
	virtual void info(const std::string& msg, int line, const char* function, const char* file) = 0;

	// Logs given text with 'info' logging level if it is enabled in config.
	virtual void info(const std::string& msg) = 0;

	// Logs given text, line, function name and file name with
	// 'debug' logging level if it is enabled in config.
	virtual void debug(const std::string& msg, int line, const char* function, const char* file) = 0;

	// Logs given text with 'debug' logging level if it is enabled in config.
	virtual void debug(const std::string& msg) = 0;

	// Logs given text, line, function name and file name with
	// `warning` logging level if it is enabled in config.
	virtual void warning(const std::string& msg, int line, const char* function, const char* file) = 0;

	// Logs given text with `warning` logging level if it is enabled in config.
	virtual void warning(const std::string& msg) = 0;

	// Logs given text, line, function name and file name with
	// `error` logging level if it is enabled in config.
	virtual void error(const std::string& msg, int line, const char* function, const char* file) = 0;

	// Logs given text with `error` logging level if it is enabled in config.
	virtual void error(const std::string& msg) = 0;

	// Logs given text, line, function name and file name with
	// `fatal` logging level if it is enabled in config.
	virtual void fatal(const std::string& msg, int line, const char* function, const char* file) = 0;

	// Logs given text with `fatal` logging level if it is enabled in config.
	virtual void fatal(const std::string& msg) = 0;

	// Logs given text, line, function name and file name with
	// `trace` logging level if it is enabled in config.
	virtual void trace(const std::string& msg, int line, const char* function, const char* file) = 0;

	// Logs given text with `trace` logging level if it is enabled in config.
	virtual void trace(const std::string& msg) = 0;

	// Logs text with custom colour and ending if it is enable in config.
	virtual void print(const std::string& msg, Color colour, char end) = 0;

	// Logs text with custom colour if it is enable in config.
	virtual void print(const std::string& msg, Color colour) = 0;

	// Logs text if it is enable in config.
	virtual void print(const std::string& msg) = 0;

	// Logs exception with `info` logging level if it is enabled in config.
	virtual void info(const core::BaseException& exc) = 0;

	// Logs exception with `debug` logging level if it is enabled in config.
	virtual void debug(const core::BaseException& exc) = 0;

	// Logs exception with `warning` logging level if it is enabled in config.
	virtual void warning(const core::BaseException& exc) = 0;

	// Logs exception with `error` logging level if it is enabled in config.
	virtual void error(const core::BaseException& exc) = 0;

	// Logs exception with `fatal` logging level if it is enabled in config.
	virtual void fatal(const core::BaseException& exc) = 0;

	// Logs `Error` with `info` logging level if it is enabled in config.
	virtual void info(const core::Error& exc) = 0;

	// Logs `Error` with `debug` logging level if it is enabled in config.
	virtual void debug(const core::Error& exc) = 0;

	// Logs `Error` with `warning` logging level if it is enabled in config.
	virtual void warning(const core::Error& exc) = 0;

	// Logs `Error` with `error` logging level if it is enabled in config.
	virtual void error(const core::Error& exc) = 0;

	// Logs `Error` with `fatal` logging level if it is enabled in config.
	virtual void fatal(const core::Error& exc) = 0;

	// Sets a config for logger.
	virtual void set_config(const Config& config) = 0;
};

// An implementation of simple logger.
class Logger : public ILogger
{
protected:

	// Indicates whether to use colourful output in
	// console stream.
	bool use_output_colors;

public:

	// Initializes thread pool with one thread.
	inline explicit Logger(Config cfg) : use_output_colors(false), _config(std::move(cfg))
	{
		this->_thread_pool = std::make_shared<core::ThreadPool>("logger", 1);
	}

	// Sets colour mode for console stream.
	inline void use_colors(bool use) override
	{
		this->use_output_colors = use;
	}

	// Finishes all log tasks in thred pool.
	inline ~Logger() override
	{
		this->_thread_pool->wait();
	}

	// Logs given text, line, function name and file name with
	// 'info' logging level if it is enabled in config.
	inline void info(const std::string& msg, int line, const char* function, const char* file) override
	{
		this->_log(msg, line, function, file, Logger::log_level_enum::ll_info);
	}

	// Logs given text with 'info' logging level if it is enabled in config.
	inline void info(const std::string& msg) override
	{
		this->info(msg, 0, "", "");
	}

	// Logs given text, line, function name and file name with
	// 'debug' logging level if it is enabled in config.
	inline void debug(const std::string& msg, int line, const char* function, const char* file) override
	{
		this->_log(msg, line, function, file, Logger::log_level_enum::ll_debug);
	}

	// Logs given text with 'debug' logging level if it is enabled in config.
	inline void debug(const std::string& msg) override
	{
		this->debug(msg, 0, "", "");
	}

	// Logs given text, line, function name and file name with
	// 'warning' logging level if it is enabled in config.
	inline void warning(const std::string& msg, int line, const char* function, const char* file) override
	{
		this->_log(msg, line, function, file, Logger::log_level_enum::ll_warning);
	}

	// Logs given text with 'warning' logging level if it is enabled in config.
	inline void warning(const std::string& msg) override
	{
		this->warning(msg, 0, "", "");
	}

	// Logs given text, line, function name and file name with
	// 'error' logging level if it is enabled in config.
	inline void error(const std::string& msg, int line, const char* function, const char* file) override
	{
		this->_log(msg, line, function, file, Logger::log_level_enum::ll_error);
	}

	// Logs given text with 'error' logging level if it is enabled in config.
	inline void error(const std::string& msg) override
	{
		this->error(msg, 0, "", "");
	}

	// Logs given text, line, function name and file name with
	// 'fatal' logging level if it is enabled in config.
	inline void fatal(const std::string& msg, int line, const char* function, const char* file) override
	{
		this->_log(msg, line, function, file, Logger::log_level_enum::ll_fatal);
	}

	// Logs given text with 'fatal' logging level if it is enabled in config.
	inline void fatal(const std::string& msg) override
	{
		this->fatal(msg, 0, "", "");
	}

	// Logs given text, line, function name and file name with
	// 'trace' logging level if it is enabled in config.
	inline void trace(const std::string& msg, int line, const char* function, const char* file) override
	{
		this->_log(msg, line, function, file, Logger::log_level_enum::ll_trace);
	}

	// Logs given text with 'trace' logging level if it is enabled in config.
	inline void trace(const std::string& msg) override
	{
		this->trace(msg, 0, "", "");
	}

	// Logs text with custom colour and ending if it is enable in config.
	inline void print(const std::string& msg, Color colour, char end) override
	{
		if (this->_config.enable_print)
		{
			this->_write_to_stream(msg, colour, end);
		}
	}

	// Logs text with custom colour if it is enable in config.
	inline void print(const std::string& msg, Color colour) override
	{
		this->print(msg, colour, '\n');
	}

	// Logs text if it is enable in config.
	inline void print(const std::string& msg) override
	{
		this->print(msg, Color::DEFAULT, '\n');
	}

	// Logs exception with `info` logging level if it is enabled in config.
	inline void info(const core::BaseException& exc) override
	{
		this->info(exc.get_message(), exc.line(), exc.function(), exc.file());
	}

	// Logs exception with `debug` logging level if it is enabled in config.
	inline void debug(const core::BaseException& exc) override
	{
		this->debug(exc.get_message(), exc.line(), exc.function(), exc.file());
	}

	// Logs exception with `warning` logging level if it is enabled in config.
	inline void warning(const core::BaseException& exc) override
	{
		this->warning(exc.get_message(), exc.line(), exc.function(), exc.file());
	}

	// Logs exception with `error` logging level if it is enabled in config.
	inline void error(const core::BaseException& exc) override
	{
		this->error(exc.get_message(), exc.line(), exc.function(), exc.file());
	}

	// Logs exception with `fatal` logging level if it is enabled in config.
	inline void fatal(const core::BaseException& exc) override
	{
		this->fatal(exc.get_message(), exc.line(), exc.function(), exc.file());
	}

	// Logs `Error` with `info` logging level if it is enabled in config.
	inline void info(const core::Error& exc) override
	{
		this->info(exc.get_message(), exc.line, exc.func.c_str(), exc.file.c_str());
	}

	// Logs `Error` with `debug` logging level if it is enabled in config.
	inline void debug(const core::Error& exc) override
	{
		this->debug(exc.get_message(), exc.line, exc.func.c_str(), exc.file.c_str());
	}

	// Logs `Error` with `warning` logging level if it is enabled in config.
	inline void warning(const core::Error& exc) override
	{
		this->warning(exc.get_message(), exc.line, exc.func.c_str(), exc.file.c_str());
	}

	// Logs `Error` with `error` logging level if it is enabled in config.
	inline void error(const core::Error& exc) override
	{
		this->error(exc.get_message(), exc.line, exc.func.c_str(), exc.file.c_str());
	}

	// Logs `Error` with `fatal` logging level if it is enabled in config.
	inline void fatal(const core::Error& exc) override
	{
		this->fatal(exc.get_message(), exc.line, exc.func.c_str(), exc.file.c_str());
	}

	// Sets a config for logger.
	inline void set_config(const Config& config) override
	{
		this->_config = config;
	}

private:
#if defined(__unix__) || defined(__linux__)

	// Colours for nice output to a console stream.
	std::map<Color, const char*> _colors = {
		{DEFAULT, "\033[0m"},
		{BLACK, "\033[30m"},
		{RED, "\033[31m"},
		{GREEN, "\033[32m"},
		{YELLOW, "\033[33m"},
		{BLUE, "\033[34m"},
		{MAGENTA, "\033[35m"},
		{CYAN, "\033[36m"},
		{WHITE, "\033[37m"},
		{BOLD_BLACK, "\033[1m\033[30m"},
		{BOLD_RED, "\033[1m\033[31m"},
		{BOLD_GREEN, "\033[1m\033[32m"},
		{BOLD_YELLOW, "\033[1m\033[33m"},
		{BOLD_BLUE, "\033[1m\033[34m"},
		{BOLD_MAGENTA, "\033[1m\033[35m"},
		{BOLD_CYAN, "\033[1m\033[36m"},
		{BOLD_WHITE, "\033[1m\033[37m"},
	};
#endif

	// Supported logging levels.
	enum log_level_enum
	{
		ll_info, ll_debug, ll_warning, ll_error, ll_fatal, ll_trace
	};

	// Logger configuration.
	Config _config;

	// Thread pool which is used for asynchronous logging.
	std::shared_ptr<core::ThreadPool> _thread_pool;

private:

	// Logs message with given parameters.
	void _log(
		const std::string& msg, int line, const char* function,
		const char* file, Logger::log_level_enum level
	);

	// Writes message to all given streams.
	void _write_to_stream(const std::string& msg, Color colour, char end='\n');

	// Sets new colour for console stream.
	void _set_colour(Color colour) const;
};

__LOG_END__
