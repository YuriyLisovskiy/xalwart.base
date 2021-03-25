/**
 * object/meta.cpp
 *
 * Copyright (c) 2020-2021 Yuriy Lisovskiy
 */

#include "./meta.h"

// Core libraries.
#include "./object.h"
#include "../string_utils.h"


__OBJ_META_BEGIN__

Type::Type(const Object& obj)
{
	std::string s = utility::demangle(typeid(obj).name());
	auto full_name = str::rsplit(s, ':', 1);
	if (full_name.size() == 2)
	{
		str::ltrim(full_name.back(), ":");
		str::rtrim(full_name.front(), ":");
		this->_namespace = full_name.front();
	}

	this->_name = full_name.back();
}

__OBJ_META_END__
