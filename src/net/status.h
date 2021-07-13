/**
 * net/status.h
 *
 * Copyright (c) 2019-2021 Yuriy Lisovskiy
 *
 * A collection of all available http statuses, which
 * contains status code, reason phrase and brief explanation.
 */

#pragma once

// C++ libraries.
#include <string>

// Module definitions.
#include "./_def_.h"

// Core libraries.
#include "../collections/dict.h"


__NET_BEGIN__

extern collections::Dict<unsigned short int, std::pair<std::string, std::string>> HTTP_STATUS;

__NET_END__
