/**
 * re/regex.cpp
 *
 * Copyright (c) 2019-2021 Yuriy Lisovskiy
 */

#include "./regex.h"

// Base libraries.
#include "../exceptions.h"


__RE_BEGIN__

Regex& Regex::operator= (const Regex& other)
{
	if (this != &other)
	{
		this->_expr = other._expr;
		this->_raw_expr = other._raw_expr;
		this->_matches = other._matches;
		this->_groups = other._groups;
	}

	return *this;
}

bool Regex::match(const std::string& s)
{
	return std::regex_match(s, this->_expr);
}

bool Regex::search(const std::string& s)
{
	this->_groups.clear();
	auto start = s.cbegin();
	bool is_found = false;
	while (std::regex_search(start, s.cend(), this->_matches, this->_expr))
	{
		for (const auto & match : this->_matches)
		{
			if (match.matched)
			{
				this->_groups.push_back(match.str());
			}
		}

		start = this->_matches.suffix().first;
		is_found = true;
	}

	return is_found;
}

std::string Regex::group(size_t pos) const
{
	if (pos >= 0 && pos < this->_groups.size())
	{
		return this->_groups[pos];
	}

	return "";
}

std::string escape(const std::string& s)
{
	std::string special = R"([\^$.|?*+(){})";
	std::string escaped;
	for (const auto& chr : s)
	{
		if (special.find(chr) != std::string::npos)
		{
			escaped += '\\';
		}

		escaped += chr;
	}

	return escaped;
}

__RE_END__
