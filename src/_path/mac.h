/**
 * _path/mac.h
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 *
 * TODO: Path utilities for Macintosh.
 */

#pragma once

#include "../sys.h"

#if defined(__mac__)

// Module definitions.
#include "../_def_.h"


__PATH_BEGIN__

inline const char current_dir = ':';
inline const char* parent_dir = "::";
inline const char ext_sep = '.';
inline const char sep = ':';
inline const char path_sep = '\n';
inline const char* def_path = ":";
inline const char alt_sep = '\0';
inline const char* dev_null = "Dev:Null";

__PATH_END__

#endif // __mac__
