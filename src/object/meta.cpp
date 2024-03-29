/**
 * object/meta.cpp
 *
 * Copyright (c) 2020-2021 Yuriy Lisovskiy
 */

#include "./meta.h"

// Base libraries.
#include "./object.h"
#include "../string_utils.h"


__OBJ_META_BEGIN__

Type::Type(const Object& obj)
{
	std::string s = demangle(typeid(obj).name());
	auto full_name = str::rsplit(s, ':', 1);
	if (full_name.size() == 2)
	{
		full_name.back() = str::ltrim(full_name.back(), ":");
		this->_namespace = str::rtrim(full_name.front(), ":");
	}

	this->_name = *(full_name.end() - 1);
}

__OBJ_META_END__
