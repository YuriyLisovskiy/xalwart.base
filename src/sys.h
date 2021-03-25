/**
 * sys.h
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 *
 * System helpers and framework definitions.
 */

#pragma once

// C++ libraries.
#include <string>

// Module definitions.
#include "./_def_.h"

__SYS_BEGIN__

inline std::string _version_string(int major, int minor, int patch)
{
	return std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(patch);
}

const std::string compiler =
#ifdef __clang__
	"clang++";
#elif defined(__GNUC__)
	"g++";
#else
	"unknown";
#endif

const std::string compiler_version =
#ifdef __clang__
	_version_string(__clang_major__, __clang_minor__, __clang_patchlevel__);
#elif defined(__GNUC__)
	_version_string(__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
#else
	"NaN.NaN.NaN";
#endif

#ifdef _WIN32
	#define __windows32__
#elif defined(_WIN64)
	#define __windows64__
#endif

#if defined(_WIN32) || defined(_WIN64)
	#define __windows__
#endif

const char dir_separator =
#if defined(__unix__)
	'/';
#elif defined(__windows__)
	'\\';
#endif

__SYS_END__
