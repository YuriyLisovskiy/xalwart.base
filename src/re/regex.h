/**
 * re/regex.h
 *
 * Copyright (c) 2019-2021 Yuriy Lisovskiy
 *
 * C++ regular expressions' wrapper and utilities.
 */

#pragma once

// C++ libraries.
#include <regex>

// Module definitions.
#include "./_def_.h"


__RE_BEGIN__

class Regex final
{
private:
	std::regex _expr;
	std::string _raw_expr;
	std::smatch _matches;
	std::vector<std::string> _groups;

public:

	// Default constructor.
	inline explicit Regex() : Regex("")
	{
	}

	// Constructs regular expression from string.
	//
	// `expr`: regular expression pattern.
	inline explicit Regex(const std::string& expr) : _raw_expr(expr)
	{
		this->_expr = std::regex(expr);
	}

	// Constructs regular expression from string with
	// additional syntax options.
	//
	// `expr`: regular expression pattern.
	// `sot`: syntax options for regular expression.
	inline explicit Regex(const std::string& expr, std::regex_constants::syntax_option_type type) :
		_raw_expr(expr)
	{
		this->_expr = std::regex(expr, type);
	}

	// Copy assignment operator.
	Regex& operator= (const Regex& other);

	// Matches string with regular expression.
	//
	// `s`: string to match.
	//
	// Returns `true` if string is matched, `false` otherwise.
	[[nodiscard]]
	inline bool match(const std::string& s) const
	{
		return std::regex_match(s, this->_expr);
	}

	// Searches for substrings in given string.
	//
	// `s`: string to search.
	//
	// Returns `true` if string matches the regular expression,
	// `false` otherwise.
	bool search(const std::string& s);

	// Returns found groups.
	[[nodiscard]]
	inline std::vector<std::string> groups() const
	{
		return this->_groups;
	}

	// Returns group by given position.
	//
	// If group is not found returns empty string.
	[[nodiscard]]
	std::string group(size_t pos) const;

	// Returns regular expression as `std::string`.
	[[nodiscard]]
	inline std::string str() const
	{
		return this->_raw_expr;
	}
};

// Escapes special symbols in regular expression string.
//
// `s`: string to escape.
//
// Returns escaped copy of the input string.
std::string escape(const std::string& s);

__RE_END__
