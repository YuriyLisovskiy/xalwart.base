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

// Base libraries.
#include "./exceptions.h"
#include "./file.h"
#include "./thread_pool.h"


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
	std::shared_ptr<File> _file;

public:

	// Creates file from given path with 'append' mode
	// and opens it immediately.
	//
	// `fp`: path to file.
	explicit FileStream(const std::string& fp)
	{
		this->_file = std::make_shared<File>(fp, File::OpenMode::AppendReadWrite);
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
	enum class Color
	{
		Default,
		Black,
		Red,
		Green,
		Yellow,
		Blue,
		Magenta,
		Cyan,
		White,
		BoldBlack,
		BoldRed,
		BoldGreen,
		BoldYellow,
		BoldBlue,
		BoldMagenta,
		BoldCyan,
		BoldWhite,
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
	virtual void info(const BaseException& exc) = 0;

	// Logs exception with `debug` logging level if it is enabled in config.
	virtual void debug(const BaseException& exc) = 0;

	// Logs exception with `warning` logging level if it is enabled in config.
	virtual void warning(const BaseException& exc) = 0;

	// Logs exception with `error` logging level if it is enabled in config.
	virtual void error(const BaseException& exc) = 0;

	// Logs exception with `fatal` logging level if it is enabled in config.
	virtual void fatal(const BaseException& exc) = 0;

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
		this->_thread_pool = std::make_shared<ThreadPool>("logger", 1);
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
		this->_log(msg, line, function, file, Logger::LogLevel::Info);
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
		this->_log(msg, line, function, file, Logger::LogLevel::Debug);
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
		this->_log(msg, line, function, file, Logger::LogLevel::Warning);
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
		this->_log(msg, line, function, file, Logger::LogLevel::Error);
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
		this->_log(msg, line, function, file, Logger::LogLevel::Fatal);
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
		this->_log(msg, line, function, file, Logger::LogLevel::Trace);
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
		this->print(msg, Color::Default, '\n');
	}

	// Logs exception with `info` logging level if it is enabled in config.
	inline void info(const BaseException& exc) override
	{
		this->info(exc.get_message(), exc.line(), exc.function(), exc.file());
	}

	// Logs exception with `debug` logging level if it is enabled in config.
	inline void debug(const BaseException& exc) override
	{
		this->debug(exc.get_message(), exc.line(), exc.function(), exc.file());
	}

	// Logs exception with `warning` logging level if it is enabled in config.
	inline void warning(const BaseException& exc) override
	{
		this->warning(exc.get_message(), exc.line(), exc.function(), exc.file());
	}

	// Logs exception with `error` logging level if it is enabled in config.
	inline void error(const BaseException& exc) override
	{
		this->error(exc.get_message(), exc.line(), exc.function(), exc.file());
	}

	// Logs exception with `fatal` logging level if it is enabled in config.
	inline void fatal(const BaseException& exc) override
	{
		this->fatal(exc.get_message(), exc.line(), exc.function(), exc.file());
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
		{Color::Default, "\033[0m"},
		{Color::Black, "\033[30m"},
		{Color::Red, "\033[31m"},
		{Color::Green, "\033[32m"},
		{Color::Yellow, "\033[33m"},
		{Color::Blue, "\033[34m"},
		{Color::Magenta, "\033[35m"},
		{Color::Cyan, "\033[36m"},
		{Color::White, "\033[37m"},
		{Color::BoldBlack, "\033[1m\033[30m"},
		{Color::BoldRed, "\033[1m\033[31m"},
		{Color::BoldGreen, "\033[1m\033[32m"},
		{Color::BoldYellow, "\033[1m\033[33m"},
		{Color::BoldBlue, "\033[1m\033[34m"},
		{Color::BoldMagenta, "\033[1m\033[35m"},
		{Color::BoldCyan, "\033[1m\033[36m"},
		{Color::BoldWhite, "\033[1m\033[37m"},
	};
#endif

	// Supported logging levels.
	enum class LogLevel
	{
		Info, Debug, Warning, Error, Fatal, Trace
	};

	// Logger configuration.
	Config _config;

	// Thread pool which is used for asynchronous logging.
	std::shared_ptr<ThreadPool> _thread_pool;

private:

	// Logs message with given parameters.
	void _log(
		const std::string& msg, int line, const char* function, const char* file, Logger::LogLevel level
	);

	// Writes message to all given streams.
	void _write_to_stream(const std::string& msg, Color colour, char end='\n');

	// Sets new colour for console stream.
	void _set_colour(Color colour) const;
};

__LOG_END__
