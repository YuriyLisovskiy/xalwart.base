/**
 * re/iter_regex.h
 *
 * Copyright (c) 2020-2021 Yuriy Lisovskiy
 *
 * Regular expression which allows to iterate over matches.
 */

#pragma once

// C++ libraries.
#include <regex>

// Module definitions.
#include "./_def_.h"


__RE_BEGIN__

class IterRegex final
{
private:
	std::string::const_iterator _start;
	std::string::const_iterator _end;
	bool _is_initialized;
	std::string _to_search;
	std::regex _expr;
	std::string _raw_expr;
	std::vector<std::string> _groups;

public:

	// Default constructor.
	inline explicit IterRegex() : IterRegex("")
	{
	}

	// Constructs regular expression from string.
	//
	// `expr`: regular expression pattern.
	inline explicit IterRegex(const std::string& expr)
		: _raw_expr(expr), _is_initialized(false)
	{
		this->_expr = std::regex(expr);
	}

	// Constructs regular expression from string with
	// additional syntax options.
	//
	// `expr`: regular expression pattern.
	// `sot`: syntax options for regular expression.
	inline explicit IterRegex(
		const std::string& expr, std::regex_constants::syntax_option_type sot
	) : _raw_expr(expr), _is_initialized(false)
	{
		this->_expr = std::regex(expr, sot);
	}

	// Copy assignment operator.
	IterRegex& operator= (const IterRegex& other);

	// Setups given string and iterators.
	//
	// `s`: string to search.
	void setup(std::string s);

	// Searches for substrings in current iteration and
	// builds groups.
	//
	// Returns `true` if string matches the regular expression,
	// `false` otherwise.
	bool search_next();

	// Returns groups found during current iteration step.
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

__RE_END__
