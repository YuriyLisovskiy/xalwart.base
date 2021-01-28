/**
 * html.h
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


__HTML_BEGIN__

// Replace special characters "&", "<" and ">" to HTML-safe sequences.
// If the optional flag quote is true (the default), the quotation mark
// characters, both double quote (") and single quote (') characters are also
// translated.
extern std::string escape(const std::string& s, bool quote=true);

__HTML_END__
