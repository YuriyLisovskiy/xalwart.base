/**
 * _path/generic.h
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 *
 * Generic utilities for working with path.
 */

#pragma once

// C++ libraries.
#include <string>

// Module definitions.
#include "../_def_.h"


__PATH_BEGIN__

// Split a path in root and extension.
// The extension is everything starting at the last dot in the last
// pathname component; the root is everything before that.
// It is always true that root + ext == p.
//
// Generic implementation of splitext, to be parametrized with
// the separators.
extern void _split_text(
	const std::string& full_path,
	char sep, char alt_sep, char ext_sep,
	std::string& root_out, std::string& ext_out
);

__PATH_END__
