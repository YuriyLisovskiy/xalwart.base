/**
 * re/iter_regex.cpp
 *
 * Copyright (c) 2020-2021 Yuriy Lisovskiy
 */

#include "./iter_regex.h"

// Base libraries.
#include "../exceptions.h"


__RE_BEGIN__

IterRegex& IterRegex::operator= (const IterRegex& other)
{
	if (this != &other)
	{
		this->_start = other._start;
		this->_end = other._end;
		this->_is_initialized = other._is_initialized;
		this->_to_search = other._to_search;
		this->_expr = other._expr;
		this->_raw_expr = other._raw_expr;
		this->_groups = other._groups;
	}

	return *this;
}

void IterRegex::setup(std::string s)
{
	this->_to_search = std::move(s);
	this->_start = this->_to_search.cbegin();
	this->_end = this->_to_search.cend();
	this->_is_initialized = true;
}

bool IterRegex::search_next()
{
	if (!this->_is_initialized)
	{
		throw RuntimeError(
			"IterRegex instance is not initialized with string to search in",
			_ERROR_DETAILS_
		);
	}

	this->_groups.clear();
	std::smatch matches;
	bool is_found = false;
	if (std::regex_search(this->_start, this->_end, matches, this->_expr))
	{
		for (const auto & match : matches)
		{
			if (match.matched)
			{
				this->_groups.push_back(match.str());
			}
		}

		this->_start = matches.suffix().first;
		is_found = true;
	}

	return is_found;
}

std::string IterRegex::group(size_t pos) const
{
	if (pos >= 0 && pos < this->_groups.size())
	{
		return this->_groups[pos];
	}

	return "";
}

__RE_END__
