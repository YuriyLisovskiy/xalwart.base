/**
 * _path/nt.h
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 *
 * TODO: Path utilities for WindowsNT/Windows95.
 */

#pragma once

#include "../sys.h"

#if defined(__windows__)

// Module definitions.
#include "../_def_.h"


__PATH_BEGIN__

inline const char current_dir = '.';
inline const char* parent_dir = "..";
inline const char ext_sep = '.';
inline const char sep = '\\';
inline const char path_sep = ';';
inline const char alt_sep = '/';
inline const char* def_path = ".;C:\\bin";
inline const char* dev_null = "nul";

__PATH_END__

#endif // __windows__
