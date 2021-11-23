/**
 * re/arg_regex.cpp
 *
 * Copyright (c) 2019-2021 Yuriy Lisovskiy
 */

#include "./arg_regex.h"


__RE_BEGIN__

ArgRegex& ArgRegex::operator= (const ArgRegex& other)
{
	if (this != &other)
	{
		this->_matches = other._matches;
		this->_orig = other._orig;
		this->_rgx = other._rgx;
		this->_pattern_parts = other._pattern_parts;
		this->_keys = other._keys;
		this->_groups = other._groups;
	}

	return *this;
}

bool ArgRegex::search(const std::string& s)
{
	auto is_found = std::regex_search(s, this->_matches, this->_rgx);
	this->_groups.clear();
	this->_list_groups.clear();
	if (is_found)
	{
		for (size_t i = 1; i < this->_matches.size(); i++)
		{
			if (this->_matches[i].matched)
			{
				auto str_match = this->_matches[i].str();
				this->_groups[this->_keys[i - 1]] = str_match;
				this->_list_groups.push_back(str_match);
			}
		}
	}

	return is_found;
}

std::string ArgRegex::arg(const std::string& key, const std::string& default_val) const
{
	if (this->_groups.find(key) != this->_groups.end())
	{
		return this->_groups.at(key);
	}

	return default_val;
}

std::string ArgRegex::_parse(const std::string& pattern)
{
	std::string new_pattern, part, arg_name;
	ArgRegex::StateEnum state = ArgRegex::StateEnum::Str;
	for (char ch : pattern)
	{
		switch (state)
		{
			case ArgRegex::StateEnum::Str:
				if (ch == '<')
				{
					state = ArgRegex::StateEnum::CheckIfArg;
					continue;
				}
				else if (ch == '(')
				{
					state = ArgRegex::StateEnum::Regex;
				}
				else if (ch == '/')
				{
					new_pattern += "\\";
					part += ch;
				}
				else
				{
					part += ch;
				}

				new_pattern += ch;
				break;
			case ArgRegex::StateEnum::CheckIfArg:
				if (ch == '<')
				{
					part += "<<";
					new_pattern += "<<";
					state = ArgRegex::StateEnum::Str;
				}
				else
				{
					state = ArgRegex::StateEnum::ArgName;
					this->_pattern_parts.push_back(part);
					part.clear();
					arg_name += ch;
				}
				break;
			case ArgRegex::StateEnum::ArgName:
				if (ch == '>')
				{
					state = ArgRegex::StateEnum::Str;
					this->_keys.push_back(arg_name);
					arg_name.clear();
				}
				else
				{
					arg_name += ch;
				}
				break;
			case ArgRegex::StateEnum::Regex:
				if (ch == ')')
				{
					state = ArgRegex::StateEnum::Str;
				}

				new_pattern += ch;
				break;
		}
	}

	if (!part.empty())
	{
		this->_pattern_parts.push_back(part);
	}

	return new_pattern;
}

__RE_END__
