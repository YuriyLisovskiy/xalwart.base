/**
 * re/arg_regex.h
 *
 * Copyright (c) 2019-2021 Yuriy Lisovskiy
 *
 * Regular expression with arguments.
 */

#pragma once

// C++ libraries.
#include <regex>

#ifdef _MSC_VER
#include <map>
#endif

// Module definitions.
#include "./_def_.h"


__RE_BEGIN__

class ArgRegex final
{
private:
	enum state_enum
	{
		s_str,
		s_check_if_arg,
		s_arg_name,
		s_regex
	};

	std::smatch _matches;

	// Original regular expression pattern.
	std::string _orig;

	// Regex instance without parameters.
	std::regex _rgx;

	// Vector of parsed parts between arguments.
	std::vector<std::string> _pattern_parts;

	// Vector of parsed arguments.
	std::vector<std::string> _keys;

	// Found groups.
	std::map<std::string, std::string> _groups;

private:

	// Parses original pattern. Searches for arguments names
	// and separates it from actual regular expression.
	std::string _parse(const std::string& pattern);

public:

	// Parses original pattern and constructs `ArgRegex` object.
	inline explicit ArgRegex(std::string pattern) : _orig(std::move(pattern))
	{
		this->_rgx = std::regex(this->_parse(this->_orig));
	}

	// Matches string with regular expression.
	//
	// `s`: string to match.
	//
	// Returns `true` if string is matched, `false` otherwise.
	[[nodiscard]]
	inline bool match(const std::string& s) const
	{
		return std::regex_match(s, this->_rgx);
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
	inline std::map<std::string, std::string> groups() const
	{
		return this->_groups;
	}

	// Returns group by given key.
	//
	// If group is not found returns empty string.
	[[nodiscard]]
	std::string group(
		const std::string& key, const std::string& default_val=""
	) const;

	// Returns parts without arguments.
	[[nodiscard]]
	inline std::vector<std::string> parts() const
	{
		return this->_pattern_parts;
	}

	// Returns original regular expression as `std::string`.
	[[nodiscard]]
	inline std::string original() const
	{
		return this->_orig;
	}
};

__RE_END__
