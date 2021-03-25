/**
 * re/arg_regex.cpp
 *
 * Copyright (c) 2019-2021 Yuriy Lisovskiy
 */

#include "./arg_regex.h"


__RE_BEGIN__

bool ArgRegex::search(const std::string& s)
{
	auto is_found = std::regex_search(s, this->_matches, this->_rgx);
	this->_groups.clear();
	if (is_found)
	{
		for (size_t i = 1; i < this->_matches.size(); i++)
		{
			if (this->_matches[i].matched)
			{
				this->_groups[this->_keys[i - 1]] = this->_matches[i].str();
			}
		}
	}

	return is_found;
}

std::string ArgRegex::group(const std::string& key, const std::string& default_val) const
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
	ArgRegex::state_enum st = ArgRegex::state_enum::s_str;
	for (char ch : pattern)
	{
		switch (st)
		{
			case ArgRegex::state_enum::s_str:
				if (ch == '<')
				{
					st = ArgRegex::state_enum::s_check_if_arg;
					continue;
				}
				else if (ch == '(')
				{
					st = ArgRegex::state_enum::s_regex;
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
			case ArgRegex::state_enum::s_check_if_arg:
				if (ch == '<')
				{
					part += "<<";
					new_pattern += "<<";
					st = ArgRegex::state_enum::s_str;
				}
				else
				{
					st = ArgRegex::state_enum::s_arg_name;
					this->_pattern_parts.push_back(part);
					part.clear();
					arg_name += ch;
				}
				break;
			case ArgRegex::state_enum::s_arg_name:
				if (ch == '>')
				{
					st = ArgRegex::state_enum::s_str;
					this->_keys.push_back(arg_name);
					arg_name.clear();
				}
				else
				{
					arg_name += ch;
				}
				break;
			case ArgRegex::state_enum::s_regex:
				if (ch == ')')
				{
					st = ArgRegex::state_enum::s_str;
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
