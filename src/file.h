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


__MAIN_NAMESPACE_BEGIN__

class File final
{
public:
	enum open_mode
	{
		r,   // read-only
		rb,  // read in binary mode (read-only)
		rw,  // read and write
		rwb, // read and write in binary mode
		w,   // write-only
		wb,  // write in binary mode (write-only)
		a,   // append (write-only)
		arw  // append (read and write)
	};

private:
	enum file_mode_enum
	{
		m_read_only, m_write_only, m_both
	};

	size_t _default_chunk_size;
	std::fstream _file;
	std::string _name;
	file_mode_enum _file_mode;
	std::ios_base::openmode _mode;

public:

	// Initializes file name and mode.
	explicit File(const std::string& name="", open_mode mode=open_mode::r);

	// Deleted constructor.
	File(const File& other) = delete;

	// Deleted `operator=`.
	File& operator=(const File& other) = delete;

	// Move-constructor.
	File(File&& other) noexcept;

	// Tries to open a file.
	//
	// Throws `core::FileError` if file name is not empty.
	void open();

	// Saves file without closing.
	//
	// Throws `core::FileError` if file is not opened.
	void save();

	// Closes the file without saving.
	//
	// Throws `core::FileError` if file is not opened.
	void close();

	// Returns `true` if file is open, `false` otherwise.
	inline bool is_open() const
	{
		return this->_file.is_open();
	}

	// Reads `n` bytes from file.
	//
	// Throws `core::FileError` if file is not opened.
	std::vector<unsigned char> read(size_t n=-1);

	// Reads `n` characters from file.
	//
	// Throws `core::FileError` if file is not opened.
	std::string read_str(size_t n=-1);

	// Writes a vector of bytes to the file.
	//
	// Throws `core::FileError` if file is not opened.
	void write(const std::vector<unsigned char>& bytes);

	// Writes string to a file.
	//
	// Throws `core::FileError` if file is not opened.
	inline void write(const std::string& str)
	{
		this->write(std::vector<unsigned char>(str.begin(), str.end()));
	}

	// Synchronizes the associated stream buffer with its
	// controlled output sequence.
	//
	// Throws `core::FileError` if file is not opened.
	File& flush();

	// Returns the size of file.
	//
	// Throws `core::FileError` if file is not opened.
	size_t size();

	// This function first clears eofbit. It does not count the
	// number of characters extracted, if any, and therefore
	// does not affect the next call to gcount().
	//
	// Uses `seekg(n, seekdir)` for read-only files and
	// `seekp(n, seekdir)` otherwise.
	void seek(size_t n, std::ios_base::seekdir seek_dir);

	// This function first clears eofbit. It does not count the
	// number of characters extracted, if any, and therefore
	// does not affect the next call to gcount().
	//
	// Uses `seekg(n)` for read-only files and `seekp(n)` otherwise.
	void seek(size_t n);

	// Returns a file position object.
	size_t tell();

	// Divides file into chunks of given size, read them
	// and returns as vector of string vectors.
	//
	// Throws `core::FileError` if file is not opened.
	std::vector<std::vector<unsigned char>> chunks(size_t chunk_size=-1);

	// Checks if file can be divided into chunks of
	// given size.
	//
	// Throws `core::FileError` if file is not opened.
	bool multiple_chunks(size_t chunk_size=-1);

	// Returns file path.
	inline std::string path() const
	{
		return this->_name;
	}
};

// Returns file info as struct `stat`.
struct stat file_stat(const std::string& file_path);

__MAIN_NAMESPACE_END__
