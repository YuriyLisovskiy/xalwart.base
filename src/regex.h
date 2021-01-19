/**
 * regex.h
 *
 * Copyright (c) 2019-2020 Yuriy Lisovskiy
 *
 * Purpose: C++ regular expression's wrapper and utilities.
 */

#pragma once

// C++ libraries.
#include <regex>

#ifdef _MSC_VER
#include <map>
#endif

// Module definitions.
#include "./_def_.h"

// Core libraries.
#include "./str.h"


__RGX_BEGIN__

class Regex final
{
private:
	bool _is_matched;
	bool _is_searched;
	std::string _to_match;
	std::regex _expr;
	std::string _raw_expr;
	std::smatch _matches;
	std::vector<std::string> _groups;

public:
	explicit Regex();
	explicit Regex(const std::string& expr);
	explicit Regex(
		const std::string& expr,
		std::regex_constants::syntax_option_type sot
	);

	// Copy assignment.
	Regex& operator= (const Regex& other);

	bool match(const std::string& to_match);
	bool search(const std::string& to_search);
	std::vector<std::string> groups();
	std::string group(size_t pos);

	[[nodiscard]]
	std::string str() const;

	static std::string escape(const std::string& input);
};


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

	bool _is_matched;
	bool _is_searched;
	bool _groups_are_made;
	std::string _to_match;

	std::string _s;
	std::string _orig;
	std::regex _rgx;

	std::vector<std::string> _pattern_parts;
	std::vector<std::string> _keys;

	std::map<std::string, std::string> _groups;

public:
	explicit ArgRegex(const std::string& rgx);
	bool match(const std::string& to_match);
	bool search(const std::string& to_search);
	std::map<std::string, std::string> groups();
	std::string group(const std::string& key, const std::string& default_val = "");
	std::vector<std::string> parts();
	std::string original();

private:
	void _make_groups();
	virtual std::string _parse(const std::string& pattern);
};

__RGX_END__
