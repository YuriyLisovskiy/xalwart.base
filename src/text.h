/**
 * text.h
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 *
 * Text utilities.
 */

#pragma once

// Module definitions.
#include "./_def_.h"

// Core libraries.
#include "./re/iter_regex.h"


__TEXT_BEGIN__

const auto SMART_SPLIT_REGEX = re::IterRegex(
	R"((?:[^\s'"]*(?:(?:"(?:[^"\\]|\\.)*"|'(?:[^'\\]|\\.)*')[^\s'"]*)+)|\S+)",
	std::regex_constants::optimize
);

// Splits a string by spaces, leaving quoted phrases together.
// Supports both single and double quotes, and supports escaping quotes with
// backslashes. In the output, strings will keep their initial and trailing
// quote marks and escaped quotes will remain escaped.
//
// `text`: string to split.
//
// Returns vector of input string's parts. If `text` is empty, returns
// empty vector.
extern std::vector<std::string> smart_split(const std::string& text);

__TEXT_END__
