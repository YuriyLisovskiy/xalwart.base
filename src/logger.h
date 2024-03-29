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
#include <memory>

// Module definitions.
#include "./_def_.h"

// Base libraries.
#include "./sys.h"
#include "./exceptions.h"
#include "./file.h"
#include "./interfaces/base.h"
#include "./workers/threaded_worker.h"


__LOG_BEGIN__

// TESTME: AbstractStream
// TODO: docs for 'AbstractStream'
class AbstractStream
{
public:
	virtual ~AbstractStream() = default;

	// Assumes writing of text to stream.
	virtual void write(const std::string& text) = 0;

	// Assumes flushing the stream.
	virtual void flush() = 0;

	// Must return 'true' for file streams, 'false' otherwise.
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

// TESTME: ConsoleStream
// TODO: docs for 'ConsoleStream'
class ConsoleStream final : public AbstractStream
{
public:

	// Writes string to console.
	//
	// 'text': string to write.
	inline void write(const std::string& text) override
	{
		std::cout << text;
	}

	// Forces 'std::cout' to print a string.
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

// TESTME: FileStream
// TODO: docs for 'FileStream'
class FileStream : public AbstractStream
{
private:

	// File with log messages.
	std::shared_ptr<File> _file;

public:

	// Creates file from given path with 'append' mode
	// and opens it immediately.
	//
	// 'fp': path to file.
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
	inline void write(const std::string& text) override
	{
		if (this->_file->is_open())
		{
			this->_file->write(text);
		}
	}

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

	// Returns 'true' if file is initialized and open,
	// 'false' otherwise.
	inline bool is_valid()
	{
		return this->_file && this->_file->is_open();
	}
};

// TESTME: Level
// TODO: docs for 'Level'
class Level final
{
public:
	struct Data
	{
		std::string name;
		ILogger::Color color;
	};

	enum Value
	{
		Info = 0, Debug, Warning, Error, Trace, Print
	};

	Level() = default;

	constexpr inline Level(Value value) : _value(value)
	{
	}

	inline operator Value() const
	{
		return this->_value;
	}

	explicit operator bool() = delete;

	constexpr inline bool operator== (Level a) const
	{
		return this->_value == a._value;
	}

	constexpr inline bool operator!= (Level a) const
	{
		return this->_value != a._value;
	}

	[[nodiscard]]
	Data data() const
	{
		switch (this->_value)
		{
			case Level::Info:
				return {"info", ILogger::Color::Cyan};
			case Level::Debug:
				return {"debug", ILogger::Color::Magenta};
			case Level::Warning:
				return {"warning", ILogger::Color::Yellow};
			case Level::Error:
				return {"error", ILogger::Color::Red};
			case Level::Trace:
				return {"trace", ILogger::Color::BoldRed};
			case Level::Print:
				return {"print", ILogger::Color::Default};
			default:
				throw ValueError("invalid 'Level' option", _ERROR_DETAILS_);
		}
	}

private:
	Value _value;
};

// TESTME: Config
// TODO: docs for 'Config'
class Config final
{
public:
	// Used only for console stream.
	bool use_colors = false;

	// A vector of streams to log into.
	std::vector<std::shared_ptr<AbstractStream>> streams;

	void enable(Level level)
	{
		this->_state[level] = true;
	}

	void enable_all_levels()
	{
		this->enable(Level::Info);
		this->enable(Level::Debug);
		this->enable(Level::Warning);
		this->enable(Level::Error);
		this->enable(Level::Trace);
		this->enable(Level::Print);
	}

	void disable(Level level)
	{
		this->_state[level] = false;
	}

	void disable_all_levels()
	{
		this->disable(Level::Info);
		this->disable(Level::Debug);
		this->disable(Level::Warning);
		this->disable(Level::Error);
		this->disable(Level::Trace);
		this->disable(Level::Print);
	}

	[[nodiscard]]
	bool is_enabled(Level level) const
	{
		return this->_state.contains(level) && this->_state.at(level);
	}

	[[nodiscard]]
	bool has_any_level() const
	{
		return std::any_of(this->_state.begin(),  this->_state.end(), [](const auto& item) -> bool
		{
			return item.second;
		});
	}

	[[nodiscard]]
	bool has_all_levels() const
	{
		return this->is_enabled(Level::Info) &&
			this->is_enabled(Level::Debug) &&
			this->is_enabled(Level::Warning) &&
			this->is_enabled(Level::Error) &&
			this->is_enabled(Level::Trace) &&
			this->is_enabled(Level::Print);
	}

	// Appends console stream.
	void add_console_stream()
	{
		if (!this->_has_console_stream)
		{
			this->streams.push_back(std::make_shared<ConsoleStream>());
			this->_has_console_stream = true;
		}
	}

	// Appends a file stream with given file path.
	void add_file_stream(const std::string& filepath)
	{
		auto file_stream = std::make_shared<FileStream>(filepath);
		if (file_stream->is_valid())
		{
			this->streams.push_back(file_stream);
		}
	}

	void add_stream(std::shared_ptr<AbstractStream> stream)
	{
		this->streams.push_back(std::move(stream));
	}

private:
	bool _has_console_stream = false;

	std::map<Level, bool> _state;
};

// TESTME: Logger
// TODO: docs for 'Logger'
class Logger : public ILogger
{
public:
	Logger(Config cfg);

	inline void enable_colors() override
	{
		this->config.use_colors = true;
	}

	inline void disable_colors() override
	{
		this->config.use_colors = false;
	}

	inline ~Logger() override
	{
		this->worker->stop();
	}

	// Logs given text, line, function name and file name with
	// 'info' logging level if it is enabled in config.
	inline void info(const std::string& msg, int line, const char* function, const char* file) const override
	{
		this->_log(msg, line, function, file, Level::Info);
	}

	// Logs given text with 'info' logging level if it is enabled in config.
	inline void info(const std::string& msg) const override
	{
		this->info(msg, 0, "", "");
	}

	// Logs given text, line, function name and file name with
	// 'debug' logging level if it is enabled in config.
	inline void debug(const std::string& msg, int line, const char* function, const char* file) const override
	{
		this->_log(msg, line, function, file, Level::Debug);
	}

	// Logs given text with 'debug' logging level if it is enabled in config.
	inline void debug(const std::string& msg) const override
	{
		this->debug(msg, 0, "", "");
	}

	// Logs given text, line, function name and file name with
	// 'warning' logging level if it is enabled in config.
	inline void warning(const std::string& msg, int line, const char* function, const char* file) const override
	{
		this->_log(msg, line, function, file, Level::Warning);
	}

	// Logs given text with 'warning' logging level if it is enabled in config.
	inline void warning(const std::string& msg) const override
	{
		this->warning(msg, 0, "", "");
	}

	// Logs given text, line, function name and file name with
	// 'error' logging level if it is enabled in config.
	inline void error(const std::string& msg, int line, const char* function, const char* file) const override
	{
		this->_log(msg, line, function, file, Level::Error);
	}

	// Logs given text with 'error' logging level if it is enabled in config.
	inline void error(const std::string& msg) const override
	{
		this->error(msg, 0, "", "");
	}

	// Logs given text, line, function name and file name with
	// 'trace' logging level if it is enabled in config.
	inline void trace(const std::string& msg, int line, const char* function, const char* file) const override
	{
		this->_log(msg, line, function, file, Level::Trace);
	}

	// Logs given text with 'trace' logging level if it is enabled in config.
	inline void trace(const std::string& msg) const override
	{
		this->trace(msg, 0, "", "");
	}

	// Logs text with custom colour and ending if it is enable in config.
	inline void print(const std::string& msg, Color colour, char end) const override
	{
		if (this->config.is_enabled(Level::Print))
		{
			this->_write_to_stream(msg, colour, end);
		}
	}

	// Logs text with custom colour if it is enable in config.
	inline void print(const std::string& msg, Color colour) const override
	{
		this->print(msg, colour, '\n');
	}

	// Logs text if it is enable in config.
	inline void print(const std::string& msg) const override
	{
		this->print(msg, Color::Default, '\n');
	}

	// Logs exception with 'info' logging level if it is enabled in config.
	inline void info(const BaseException& exc) const override
	{
		this->info(exc.get_message(), exc.line(), exc.function(), exc.file());
	}

	// Logs exception with 'debug' logging level if it is enabled in config.
	inline void debug(const BaseException& exc) const override
	{
		this->debug(exc.get_message(), exc.line(), exc.function(), exc.file());
	}

	// Logs exception with 'warning' logging level if it is enabled in config.
	inline void warning(const BaseException& exc) const override
	{
		this->warning(exc.get_message(), exc.line(), exc.function(), exc.file());
	}

	// Logs exception with 'error' logging level if it is enabled in config.
	inline void error(const BaseException& exc) const override
	{
		this->error(exc.get_message(), exc.line(), exc.function(), exc.file());
	}

protected:
	struct LogTask : public AbstractWorker::Task
	{
	public:
		Level level;
		std::string message;
		int line;
		const char* function;
		const char* file;
	};

	static inline const size_t THREADS_COUNT = 1;

#if defined(__linux__) || defined(__mac__)
	// Colours for nice output to a console stream.
	const std::map<Color, const char*> _colors = {
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
#endif // __linux__ || __mac__

	Config config;

	// Worker for non-blocking logging.
	std::shared_ptr<ThreadedWorker> worker;

private:
	void _log(
		const std::string& message, int line, const char* function, const char* file, Level level
	) const;

	// Writes message to all streams one by one.
	void _write_to_stream(const std::string& message, Color colour, char end='\n') const;

	// Sets the color only for console stream.
	void _set_color(Color colour, bool is_console_stream) const;
};

__LOG_END__
