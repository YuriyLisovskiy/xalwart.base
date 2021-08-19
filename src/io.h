/**
 * io.h
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 *
 * Purpose: TODO
 */

#pragma once

// C++ libraries.
#include <string>

// Module definitions.
#include "./_def_.h"


__IO_BEGIN__

class IReader
{
public:
	virtual int read_line(std::string& buffer, size_t max_n) = 0;

	virtual int read(std::string& buffer, size_t n) = 0;
};

__IO_END__
