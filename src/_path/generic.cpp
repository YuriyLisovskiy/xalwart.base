/**
 * _path/generic.cpp
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 */

#include "./generic.h"


__PATH_BEGIN__

void _split_text(
	const std::string& full_path,
	char sep, char alt_sep, char ext_sep,
	std::string& root_out, std::string& ext_out
)
{
	root_out = full_path;
	ext_out = "";
	long sep_idx = full_path.rfind(sep);
	if (sep_idx == std::string::npos)
	{
		sep_idx = -1;
	}

	if (alt_sep != '\0')
	{
		long altsep_idx = full_path.rfind(alt_sep);
		if (altsep_idx == std::string::npos)
		{
			altsep_idx = -1;
		}

		sep_idx = std::max(sep_idx, altsep_idx);
	}

	long dot_idx = full_path.rfind(ext_sep);
	if (dot_idx == std::string::npos)
	{
		dot_idx = -1;
	}

	if (dot_idx > sep_idx)
	{
		// skip all leading dots
		size_t file_name_idx = sep_idx + 1;
		while (file_name_idx < dot_idx)
		{
			if (full_path.at(file_name_idx) != ext_sep)
			{
				root_out = full_path.substr(0, dot_idx);
				ext_out = full_path.substr(dot_idx);
				break;
			}

			file_name_idx++;
		}
	}
}

__PATH_END__
