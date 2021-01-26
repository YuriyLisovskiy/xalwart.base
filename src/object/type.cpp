/**
 * object/type.cpp
 *
 * Copyright (c) 2020-2021 Yuriy Lisovskiy
 */

#include "./type.h"

// Core libraries.
#include "../string_utils.h"
#include "./object.h"


__OBJECT_BEGIN__

Type::Type(const Object& obj)
{
	std::string s = Type::type_name(obj);
	auto full_name = str::rsplit(s, ':', 1);
	if (full_name.size() == 2)
	{
		str::ltrim(full_name.back(), ":");
		str::rtrim(full_name.front(), ":");
		this->_namespace = full_name.front();
	}

	this->_name = full_name.back();
	for (auto attr_it = obj.attrs_begin(); attr_it != obj.attrs_end(); attr_it++)
	{
		this->_attrs.push_back(attr_it->first);
	}

	using T = decltype(obj);
	this->_is_const = std::is_const<T>::value;
	this->_is_volatile = std::is_volatile<T>::value;
	this->_is_lvalue_ref = std::is_lvalue_reference<T>::value;
	this->_is_rvalue_ref = std::is_rvalue_reference<T>::value;
}

[[nodiscard]] std::string Type::type_name(const Object& obj)
{
	return utility::demangle(typeid(obj).name());
}

__OBJECT_END__
