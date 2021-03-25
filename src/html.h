/**
 * html.h
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 *
 * Common html utilities.
 */

#pragma once

// C++ libraries.
#include <string>

// Module definitions.
#include "./_def_.h"


__HTML_BEGIN__

// Replace special characters "&", "<" and ">" to HTML-safe sequences.
// If the optional flag quote is true (the default), the quotation mark
// characters, both double quote (") and single quote (') characters are also
// translated.
//
// `input`: string to escape.
// `quote`: indicates whether to escape quotes (' and ") or not.
//
// Returns escaped copy of input string.
extern std::string escape(const std::string& input, bool quote=true);

__HTML_END__
