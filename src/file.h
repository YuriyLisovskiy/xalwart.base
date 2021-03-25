/**
 * files/file.h
 *
 * Copyright (c) 2019-2021 Yuriy Lisovskiy
 *
 * File stream wrapper for easier file handling.
 */

#pragma once

// C++ libraries.
#include <fstream>
#include <vector>

#if defined(__unix__) || defined(__linux__)
#include <sys/stat.h>
#endif

#ifndef _WIN32
#include <unistd.h>
#endif

// Module definitions.
#include "./_def_.h"


__CORE_BEGIN__

// TODO: optimize File functionality.
// TODO: refactor.
class File
{
protected:
	enum file_mode_enum
	{
		m_read_only, m_write_only, m_both
	};

	size_t _default_chunk_size;
	std::fstream _file;
	std::string _name;
	file_mode_enum _file_mode;
	std::string _str_mode;
	std::ios_base::openmode _mode;
	std::vector<unsigned char> _data;

	void init_mode(const std::string& mode);

	void seek(size_t n, std::ios_base::seekdir seek_dir);

	void seek(size_t n);

	size_t tell();

public:
	explicit File(const std::string& name="", const std::string& mode="r");

	File(
		const std::vector<unsigned char>& data,
		const std::string& name,
		const std::string& mode="wb"
	);

	File(const File& other);

	File& operator=(const File& other);

	void open();

	// Saves file without closing.
	void save();

	// Opens file if it is not opened, writes data
	//  if byte vector is not empty and closes file.
	void save_file();

	void close();

	bool is_open();

	std::vector<unsigned char> read(size_t n = -1);

	std::string read_str(size_t n = -1);

	void write(std::vector<unsigned char> bytes);

	void write_str(const std::string& str);

	void flush();

	size_t size();

	std::vector<std::vector<unsigned char>> chunks(size_t chunk_size = -1);

	bool multiple_chunks(size_t chunk_size = -1);

	inline std::string path() const
	{
		return this->_name;
	}

	static struct stat file_stat(const std::string& file_path);
};

__CORE_END__
