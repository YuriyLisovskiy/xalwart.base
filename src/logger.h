/**
 * logger.h
 *
 * Copyright (c) 2019-2021 Yuriy Lisovskiy
 *
 * Purpose: logger base, streams and simple logger.
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

	virtual void write(const std::string& text) = 0;

	virtual void flush() = 0;

	[[nodiscard]]
	virtual inline bool is_file() const
	{
		return false;
	}

	[[nodiscard]]
	virtual inline bool is_console() const
	{
		return false;
	}
};

class ConsoleStream final : public Stream
{
public:
	inline void write(const std::string& text) override
	{
		std::cout << text;
	}

	inline void flush() override
	{
		std::cout.flush();
	}

	[[nodiscard]]
	inline bool is_console() const override
	{
		return true;
	}
};

class FileStream : public Stream
{
private:
	std::shared_ptr<core::File> _file;

public:
	explicit FileStream(const std::string& fp)
	{
		this->_file = std::make_shared<core::File>(fp, "a");
		this->_file->open();
	}

	inline ~FileStream() override
	{
		this->_file->close();
	}

	// Writes string to file.
	void write(const std::string& text) override;

	[[nodiscard]]
	inline bool is_file() const override
	{
		return true;
	}

	inline void flush() override
	{
		this->_file->flush();
	}

	inline bool is_valid()
	{
		return this->_file && this->_file->is_open();
	}
};

class Config
{
private:
	bool _has_cout = false;

public:
	bool enable_info = true;
	bool enable_debug = true;
	bool enable_warning = true;
	bool enable_error = true;
	bool enable_fatal = true;
	bool enable_trace = true;
	bool enable_print = true;

	std::vector<std::shared_ptr<Stream>> streams;

	void add_console_stream();

	void add_file_stream(const std::string& fp);
};

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

	virtual void use_colors(bool use) = 0;

	virtual ~ILogger() = default;

	virtual void info(const std::string& msg, int line, const char* function, const char* file) = 0;
	virtual void info(const std::string& msg) = 0;

	virtual void debug(const std::string& msg, int line, const char* function, const char* file) = 0;
	virtual void debug(const std::string& msg) = 0;

	virtual void warning(const std::string& msg, int line, const char* function, const char* file) = 0;
	virtual void warning(const std::string& msg) = 0;

	virtual void error(const std::string& msg, int line, const char* function, const char* file) = 0;
	virtual void error(const std::string& msg) = 0;

	virtual void fatal(const std::string& msg, int line, const char* function, const char* file) = 0;
	virtual void fatal(const std::string& msg) = 0;

	virtual void trace(const std::string& msg, int line, const char* function, const char* file) = 0;
	virtual void trace(const std::string& msg) = 0;

	virtual void print(const std::string& msg, Color colour, char end) = 0;
	virtual void print(const std::string& msg, Color colour) = 0;
	virtual void print(const std::string& msg) = 0;

	virtual void print(const char* msg, Color colour, char end) = 0;
	virtual void print(const char* msg, Color colour) = 0;
	virtual void print(const char* msg) = 0;

	virtual void info(const core::BaseException& exc) = 0;

	virtual void debug(const core::BaseException& exc) = 0;

	virtual void warning(const core::BaseException& exc) = 0;

	virtual void error(const core::BaseException& exc) = 0;

	virtual void fatal(const core::BaseException& exc) = 0;

	virtual void info(const core::Error& exc) = 0;

	virtual void debug(const core::Error& exc) = 0;

	virtual void warning(const core::Error& exc) = 0;

	virtual void error(const core::Error& exc) = 0;

	virtual void fatal(const core::Error& exc) = 0;

	virtual void set_config(const Config& config) = 0;
};

class Logger : public ILogger
{
protected:
	bool use_output_colors;

public:
	inline explicit Logger(Config cfg) : use_output_colors(false), _config(std::move(cfg))
	{
		this->_thread_pool = std::make_shared<core::ThreadPool>("logger", 1);
	}

	inline void use_colors(bool use) override
	{
		this->use_output_colors = use;
	}

	inline ~Logger() override
	{
		this->_thread_pool->wait();
	}

	inline void info(const std::string& msg, int line, const char* function, const char* file) override
	{
		this->_log(msg, line, function, file, Logger::log_level_enum::ll_info);
	}

	inline void info(const std::string& msg) override
	{
		this->info(msg, 0, "", "");
	}

	inline void debug(const std::string& msg, int line, const char* function, const char* file) override
	{
		this->_log(msg, line, function, file, Logger::log_level_enum::ll_debug);
	}

	inline void debug(const std::string& msg) override
	{
		this->debug(msg, 0, "", "");
	}

	inline void warning(const std::string& msg, int line, const char* function, const char* file) override
	{
		this->_log(msg, line, function, file, Logger::log_level_enum::ll_warning);
	}

	inline void warning(const std::string& msg) override
	{
		this->warning(msg, 0, "", "");
	}

	inline void error(const std::string& msg, int line, const char* function, const char* file) override
	{
		this->_log(msg, line, function, file, Logger::log_level_enum::ll_error);
	}

	inline void error(const std::string& msg) override
	{
		this->error(msg, 0, "", "");
	}

	inline void fatal(const std::string& msg, int line, const char* function, const char* file) override
	{
		this->_log(msg, line, function, file, Logger::log_level_enum::ll_fatal);
	}

	inline void fatal(const std::string& msg) override
	{
		this->fatal(msg, 0, "", "");
	}

	inline void trace(const std::string& msg, int line, const char* function, const char* file) override
	{
		this->_log(msg, line, function, file, Logger::log_level_enum::ll_trace);
	}

	inline void trace(const std::string& msg) override
	{
		this->trace(msg, 0, "", "");
	}

	inline void print(const std::string& msg, Color colour, char end) override
	{
		if (this->_config.enable_print)
		{
			this->_write_to_stream(msg, colour, end);
		}
	}

	inline void print(const std::string& msg, Color colour) override
	{
		this->print(msg, colour, '\n');
	}

	inline void print(const std::string& msg) override
	{
		this->print(msg, Color::DEFAULT, '\n');
	}

	inline void print(const char* msg, Color colour, char end) override
	{
		this->print(std::string(msg), colour, end);
	}

	inline void print(const char* msg, Color colour) override
	{
		this->print(msg, colour, '\n');
	}

	inline void print(const char* msg) override
	{
		this->print(msg, Color::DEFAULT, '\n');
	}

	inline void info(const core::BaseException& exc) override
	{
		this->info(exc.get_message(), exc.line(), exc.function(), exc.file());
	}

	inline void debug(const core::BaseException& exc) override
	{
		this->debug(exc.get_message(), exc.line(), exc.function(), exc.file());
	}

	inline void warning(const core::BaseException& exc) override
	{
		this->warning(exc.get_message(), exc.line(), exc.function(), exc.file());
	}

	inline void error(const core::BaseException& exc) override
	{
		this->error(exc.get_message(), exc.line(), exc.function(), exc.file());
	}

	inline void fatal(const core::BaseException& exc) override
	{
		this->fatal(exc.get_message(), exc.line(), exc.function(), exc.file());
	}

	inline void info(const core::Error& exc) override
	{
		this->info(exc.get_message(), exc.line, exc.func.c_str(), exc.file.c_str());
	}

	inline void debug(const core::Error& exc) override
	{
		this->debug(exc.get_message(), exc.line, exc.func.c_str(), exc.file.c_str());
	}

	inline void warning(const core::Error& exc) override
	{
		this->warning(exc.get_message(), exc.line, exc.func.c_str(), exc.file.c_str());
	}

	inline void error(const core::Error& exc) override
	{
		this->error(exc.get_message(), exc.line, exc.func.c_str(), exc.file.c_str());
	}

	inline void fatal(const core::Error& exc) override
	{
		this->fatal(exc.get_message(), exc.line, exc.func.c_str(), exc.file.c_str());
	}

	inline void set_config(const Config& config) override
	{
		this->_config = config;
	}

private:
#if defined(__unix__) || defined(__linux__)
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
