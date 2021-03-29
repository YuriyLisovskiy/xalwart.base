/**
 * path.h
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 *
 * Platform-dependent includes of path utilities.
 */

#pragma once

#include "./sys.h"


#ifdef __unix__

#include "./_path/posix.h"

#endif // __unix__


#ifdef __windows__

// TODO: include windows path utilities.
#error "Path utilities is not supported on Windows"

#endif // __windows__


#ifdef __mac__

// TODO: include windows path utilities.
#error "Path utilities is not supported on Mac"

#endif // __mac__
