/* re/arg_regex.h
 *
 * Copyright (c) 2019-2021 Yuriy Lisovskiy
 */

#pragma once

// C++ libraries.
#include <regex>
#include <string>
#include <vector>
#include <map>

// Module definitions.
#include "./_def_.h"

// Base libraries.
#include "../utility.h"


__RE_BEGIN__

/** Regular expression with arguments.
 */
class ArgRegex final
{
private:
	enum class StateEnum
	{
		Str, CheckIfArg, ArgName, Regex
	};

	std::smatch _matches;

	/** Original regular expression pattern.
	 */
	std::string _orig;

	/** Regex instance without parameters.
	 */
	std::regex _rgx;

	/** Vector of parsed parts between arguments.
	 */
	std::vector<std::string> _pattern_parts;

	/** Vector of parsed arguments.
	 */
	std::vector<std::string> _keys;

	/** Found groups.
	 */
	std::map<std::string, std::string> _groups;

	/** List of found groups in same order as provided in regex.
	 */
	std::vector<std::string> _list_groups;

private:

	/** Parses original pattern. Searches for arguments names
	 * and separates it from actual regular expression.
	 */
	std::string _parse(const std::string& pattern);

public:

	inline explicit ArgRegex() : ArgRegex("")
	{
	}

	/** Parses the original pattern and constructs `ArgRegex` object.
	 */
	inline explicit ArgRegex(std::string pattern) : _orig(std::move(pattern))
	{
		this->_rgx = std::regex(this->_parse(this->_orig));
	}

	ArgRegex& operator= (const ArgRegex& other);

	/** Matches string with regular expression.
	 *
	 * \return `true` if string is matched, `false` otherwise
	 */
	[[nodiscard]]
	inline bool match(const std::string& s) const
	{
		return std::regex_match(s, this->_rgx);
	}

	/** Clears the previous result and searches for substrings in given string.
	 *
	 * \return `true` if string matches the regular expression,
	 * `false` otherwise.
	 */
	bool search(const std::string& s);

	/**
	 * \return found arguments
	 */
	[[nodiscard]]
	inline std::map<std::string, std::string> args() const
	{
		return this->_groups;
	}

	/** Builds the tuple from found groups.
	 *
	 * \return tuple of arguments converted from string
	 * \throw ArgumentError when tuple and group lengths are not equals
	 */
	template <typename ...Args>
	inline std::tuple<Args...> args_tuple() const
	{
		std::tuple<Args...> result;
		auto sz = this->_list_groups.size();
		if (sz != std::tuple_size_v<std::tuple<Args...>>)
		{
			throw ArgumentError("expected result does not match found arguments count", _ERROR_DETAILS_);
		}

		util::tuple_for_each(result, [this](size_t i, auto& elem) -> void {
			elem = util::as<typename std::remove_reference<decltype(elem)>::type>(this->_list_groups[i].c_str());
		});
		return result;
	}

	/** Searches for argument by given key.
	 *
	 * If arg is not found returns empty string.
	 *
	 * \param key - key to search for
	 * \param default_val - value to return in case when key is not found
	 * \return argument's value
	 */
	[[nodiscard]]
	std::string arg(const std::string& key, const std::string& default_val="") const;

	/** Returns parts without arguments.
	 *
	 * \return vector of regular expression parts.
	 */
	[[nodiscard]]
	inline std::vector<std::string> parts() const
	{
		return this->_pattern_parts;
	}

	/** Returns original regular expression.
	 *
	 * \return regular expression as `std::string`
	 */
	[[nodiscard]]
	inline std::string to_string() const
	{
		return this->_orig;
	}
};

__RE_END__
