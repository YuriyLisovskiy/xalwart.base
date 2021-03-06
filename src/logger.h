/**
 * logger.h
 *
 * Copyright (c) 2019-2021 Yuriy Lisovskiy
 *
 * Purpose: TODO
 */

#pragma once

// C++ libraries.
#include <map>
#include <vector>
#include <memory>

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
	virtual bool is_file();
	virtual bool is_console();
};

class ConsoleStream : public Stream
{
public:
	void write(const std::string& text) override;
	void flush() override;
	bool is_console() override;
};

class FileStream : public Stream
{
private:
	std::shared_ptr<core::File> _file;

public:
	explicit FileStream(const std::string& fp);
	~FileStream() override;
	void write(const std::string& text) override;
	bool is_file() override;
	void flush() override;
	bool is_valid();
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
	virtual void info(const std::string& msg, int line=0, const char* function="", const char* file="") = 0;
	virtual void debug(const std::string& msg, int line=0, const char* function="", const char* file="") = 0;
	virtual void warning(const std::string& msg, int line=0, const char* function="", const char* file="") = 0;
	virtual void error(const std::string& msg, int line=0, const char* function="", const char* file="") = 0;
	virtual void fatal(const std::string& msg, int line=0, const char* function="", const char* file="") = 0;
	virtual void trace(const std::string& msg, int line=0, const char* function="", const char* file="") = 0;
	virtual void print(const std::string& msg, Color colour = Color::DEFAULT, char end='\n') = 0;
	virtual void print(const char* msg, Color colour = Color::DEFAULT, char end='\n') = 0;

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
	explicit Logger(const Config& cfg);

	void use_colors(bool use) override;

	~Logger() override;

	void info(const std::string& msg, int line=0, const char* function="", const char* file="") override;
	void debug(const std::string& msg, int line=0, const char* function="", const char* file="") override;
	void warning(const std::string& msg, int line=0, const char* function="", const char* file="") override;
	void error(const std::string& msg, int line=0, const char* function="", const char* file="") override;
	void fatal(const std::string& msg, int line=0, const char* function="", const char* file="") override;
	void trace(const std::string& msg, int line=0, const char* function="", const char* file="") override;
	void print(const std::string& msg, Color colour = Color::DEFAULT, char end='\n') override;
	void print(const char* msg, Color colour = Color::DEFAULT, char end='\n') override;

	void info(const core::BaseException& exc) override;
	void debug(const core::BaseException& exc) override;
	void warning(const core::BaseException& exc) override;
	void error(const core::BaseException& exc) override;
	void fatal(const core::BaseException& exc) override;

	void info(const core::Error& exc) override;
	void debug(const core::Error& exc) override;
	void warning(const core::Error& exc) override;
	void error(const core::Error& exc) override;
	void fatal(const core::Error& exc) override;

	void set_config(const Config& config) override;

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

	Config _config;

	std::shared_ptr<core::ThreadPool> _thread_pool;

private:
	void _log(
		const std::string& msg, int line, const char* function,
		const char* file, Logger::log_level_enum level
	);

	void _write_to_stream(const std::string& msg, Color colour, char end='\n');

	void _set_colour(Color colour);
};

__LOG_END__
