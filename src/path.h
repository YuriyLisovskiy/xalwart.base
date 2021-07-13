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

#include "./_path/nt.h"

#endif // __windows__


#ifdef __mac__

#error "Path utilities is not supported on Mac"

#endif // __mac__
