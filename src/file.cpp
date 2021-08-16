/**
 * file.cpp
 *
 * Copyright (c) 2019-2021 Yuriy Lisovskiy
 */

#include "./file.h"

// C++ libraries.
#include <cmath>

#ifndef _MSC_VER
#include <sys/stat.h>
#endif

// Base libraries.
#include "./exceptions.h"
#include "./string_utils.h"


__MAIN_NAMESPACE_BEGIN__

File::File(const std::string& name, OpenMode mode)
{
	this->_default_chunk_size = 64 * (size_t)std::pow(2, 10);
	this->_name = name;
	switch (mode)
	{
		case OpenMode::ReadOnly:
			this->_mode = std::ios::in;
			this->_file_mode = FileMode::ReadOnly;
			break;
		case OpenMode::ReadBinary:
			this->_file_mode = FileMode::ReadOnly;
			this->_mode = std::ios::in | std::ios::binary;
			break;
		case OpenMode::ReadWrite:
			this->_file_mode = FileMode::ReadWrite;
			this->_mode = std::ios::out | std::ios::in;
			break;
		case OpenMode::ReadWriteBinary:
			this->_file_mode = FileMode::ReadWrite;
			this->_mode = std::ios::out | std::ios::in | std::ios::binary;
			break;
		case OpenMode::WriteOnly:
			this->_file_mode = FileMode::WriteOnly;
			this->_mode = std::ios::out;
			break;
		case OpenMode::WriteBinary:
			this->_file_mode = FileMode::WriteOnly;
			this->_mode = std::ios::out | std::ios::binary;
			break;
		case OpenMode::AppendReadOnly:
			this->_file_mode = FileMode::WriteOnly;
			this->_mode = std::ios::out | std::ios::app;
			break;
		case OpenMode::AppendReadWrite:
			this->_file_mode = FileMode::ReadWrite;
			this->_mode = std::ios::out | std::ios::in | std::ios::app;
			break;
		default:
			throw FileError("invalid file mode: " + this->_name, _ERROR_DETAILS_);
	}
}

File::File(File&& other) noexcept
{
	if (this != &other)
	{
		this->_default_chunk_size = other._default_chunk_size;
		this->_name = std::move(other._name);
		this->_file_mode = other._file_mode;
		this->_mode = other._mode;
		this->_file = std::move(other._file);
	}
}

void File::open()
{
	if (this->_name.empty())
	{
		throw FileError("open: file path is empty", _ERROR_DETAILS_);
	}

	if (this->_file.is_open())
	{
		this->_file.seekg(0);
	}
	else
	{
		this->_file.open(this->_name, this->_mode);
	}
}

void File::save()
{
	if (!this->is_open())
	{
		throw FileError("save: file is not opened: " + this->_name, _ERROR_DETAILS_);
	}

	this->_file.flush();
}

void File::close()
{
	if (!this->is_open())
	{
		throw FileError("close: file is not opened: " + this->_name, _ERROR_DETAILS_);
	}

	this->_file.close();
}

std::vector<unsigned char> File::read(size_t n)
{
	if (!this->is_open())
	{
		throw FileError("read: file is not opened: " + this->_name, _ERROR_DETAILS_);
	}

	if (this->_file_mode == FileMode::WriteOnly)
	{
		throw FileError("read: file is open only for writing: " + this->_name, _ERROR_DETAILS_);
	}

	size_t actual_size = this->size() - this->tell();
	if (n < 0 || n > actual_size)
	{
		n = actual_size;
	}

	std::vector<unsigned char> bytes;
	if (n > 0)
	{
		bytes.resize(n);
		this->_file.read((char*) bytes.data(), n);
	}

	return bytes;
}

std::string File::read_str(size_t n)
{
	std::vector<unsigned char> bytes = this->read(n);
	return {bytes.begin(), bytes.end()};
}

void File::write(const std::vector<unsigned char>& bytes)
{
	if (!this->is_open())
	{
		throw FileError("write: file is not opened: " + this->_name, _ERROR_DETAILS_);
	}

	if (this->_file_mode == FileMode::ReadOnly)
	{
		throw FileError("write: file is open only for reading: " + this->_name, _ERROR_DETAILS_);
	}

	this->_file.write((char*) bytes.data(), bytes.size());
}

File& File::flush()
{
	if (!this->is_open())
	{
		throw FileError("flush: file is not opened: " + this->_name, _ERROR_DETAILS_);
	}

	this->_file.flush();
	return *this;
}

size_t File::size()
{
	if (!this->is_open())
	{
		throw FileError("size: file is not opened: " + this->_name, _ERROR_DETAILS_);
	}

	size_t current_pos = this->tell();
	this->seek(0, std::fstream::end);
	size_t file_size = this->tell();
	this->seek(current_pos);
	return file_size;
}

void File::seek(size_t n, std::ios_base::seekdir seek_dir)
{
	if (!this->is_open())
	{
		throw FileError("seek: file is not opened: " + this->_name, _ERROR_DETAILS_);
	}

	if (this->_file_mode == FileMode::ReadOnly)
	{
		this->_file.seekg(n, seek_dir);
	}
	else
	{
		this->_file.seekp(n, seek_dir);
	}
}

void File::seek(size_t n)
{
	if (!this->is_open())
	{
		throw FileError("seek: file is not opened: " + this->_name, _ERROR_DETAILS_);
	}

	if (this->_file_mode == FileMode::ReadOnly)
	{
		this->_file.seekg(n);
	}
	else
	{
		this->_file.seekp(n);
	}
}

size_t File::tell()
{
	if (!this->is_open())
	{
		throw FileError("tell: file is not opened: " + this->_name, _ERROR_DETAILS_);
	}

	if (this->_file_mode == FileMode::ReadOnly)
	{
		return this->_file.tellg();
	}
	else
	{
		return this->_file.tellp();
	}
}

std::vector<std::vector<unsigned char>> File::chunks(size_t chunk_size)
{
	if (!this->is_open())
	{
		throw FileError("chunks: file is not opened: " + this->_name, _ERROR_DETAILS_);
	}

	if (chunk_size < 1)
	{
		chunk_size = this->_default_chunk_size;
	}

	this->seek(0);
	std::vector<std::vector<unsigned char>> result;
	while (true)
	{
		std::vector<unsigned char> chunk = this->read(chunk_size);
		if (chunk.empty())
		{
			break;
		}

		result.push_back(chunk);
	}

	return result;
}

bool File::multiple_chunks(size_t chunk_size)
{
	if (!this->is_open())
	{
		throw FileError("multiple_chunks: file is not opened: " + this->_name, _ERROR_DETAILS_);
	}

	if (chunk_size < 1)
	{
		chunk_size = this->_default_chunk_size;
	}

	return this->size() > chunk_size;
}

struct stat file_stat(const std::string& file_path)
{
	struct stat buf{};
	auto ret = stat(file_path.c_str(), &buf);
	if (ret != 0)
	{
		if (ret == ENOENT)
		{
			throw FileError("file '" + file_path + "' does not exist", _ERROR_DETAILS_);
		}

		throw FileError("unable to obtain file information: '" + file_path + "'", _ERROR_DETAILS_);
	}

	return buf;
}

__MAIN_NAMESPACE_END__
