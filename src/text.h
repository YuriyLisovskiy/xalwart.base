/**
 * text.h
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 *
 * Purpose: text utilities.
 */

#pragma once

// Module definitions.
#include "./_def_.h"

// Core libraries.
#include "./regex.h"


__TEXT_BEGIN__

const auto SMART_SPLIT_REGEX = rgx::IterRegex(
	R"((?:[^\s'"]*(?:(?:"(?:[^"\\]|\\.)*"|'(?:[^'\\]|\\.)*')[^\s'"]*)+)|\S+)",
	std::regex_constants::optimize
);

// Generator that splits a string by spaces, leaving quoted phrases together.
// Supports both single and double quotes, and supports escaping quotes with
// backslashes. In the output, strings will keep their initial and trailing
// quote marks and escaped quotes will remain escaped.
extern std::vector<std::string> smart_split(const std::string& text);

__TEXT_END__
