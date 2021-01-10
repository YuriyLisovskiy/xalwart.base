/**
 * sys.cpp
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 */

#include "./sys.h"


__SYS_BEGIN__

std::string _version_string(int major, int minor, int patch)
{
	return std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(patch);
}

__SYS_END__
