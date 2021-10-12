/**
 * _path/nt.cpp
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 */

#include "./nt.h"

#if defined(__windows__)

// C++ libraries.

// Base libraries.
#include "../exceptions.h"


__PATH_BEGIN__

std::pair<std::string, std::string> split(const std::string& s)
{
	std::string seps = "\\/";
	auto [d, p] = split_drive(s);

	// set i to index beyond p's last slash
	auto i = p.size();
	while (i > 0 && !str::contains(seps, p[i - 1]))
	{
		i--;
	}

	// now tail has no slashes
	auto head = p.substr(0, i), tail = p.substr(i);

	// remove trailing slashes from head, unless it's all slashes
	auto new_head = str::rtrim(head, seps);
	if (new_head.empty())
	{
		new_head = head;
	}

	return {d + new_head, tail};
}

std::pair<std::string, std::string> split_drive(const std::string& p)
{
	if (p.size() > 2)
	{
		std::string s_sep = std::string(1, path_sep),
			s_alt_sep = std::string(1, alt_sep),
			colon = ":";
		auto norm_p = str::replace(p, s_alt_sep, s_sep);
		if ((norm_p.substr(0, 2) == s_sep + s_sep) and (norm_p.substr(2, 1) != s_sep))
		{
			// is a UNC path:
			// vvvvvvvvvvvvvvvvvvvv drive letter or UNC path
			// \\machine\mountpoint\directory\etc\...
			//           directory ^^^^^^^^^^^^^^^
			auto index = norm_p.find(s_sep, 2);
			if (index == std::string::npos)
			{
				return {"", p};
			}

			auto index2 = norm_p.find(s_sep, index + 1);

			// a UNC path can't have two slashes in a row
			// (after the initial two)
			if (index2 == index + 1)
			{
				return {"", p};
			}

			if (index2 == std::string::npos)
			{
				index2 = p.size();
			}

			return {p.substr(0, index2), p.substr(index2)};
		}

		if (norm_p.substr(1, 1) == colon)
		{
			return {p.substr(0, 2), p.substr(2)};
		}
	}

	return {"", p};
}

std::pair<std::string, std::string> prefix_and_suffix(const std::string& pattern)
{
	if (str::contains(pattern, path_sep))
	{
		throw ArgumentError("pattern contains path separator", _ERROR_DETAILS_);
	}

	std::string prefix, suffix;
	auto pos = pattern.find_last_of('*');
	if (pos != std::string::npos)
	{
		prefix = pattern.substr(0, pos);
		suffix = pattern.substr(pos + 1);
	}
	else
	{
		prefix = pattern;
	}

	return {prefix, suffix};
}

bool _is_absolute(const std::string& p)
{
	// Paths beginning with \\?\ are always absolute, but do not
	// necessarily contain a drive.
	if (str::replace(p, "/", "\\").starts_with(R"(\\?\)"))
	{
		return true;
	}

	auto s = split_drive(p).second;
	return !s.empty() && str::contains("\\/", s[0]);
}


__PATH_END__

#endif // __windows__
