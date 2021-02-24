/**
 * object/attribute.h
 *
 * Copyright (c) 2020 Yuriy Lisovskiy
 *
 * Purpose: holds address to a variable/class field and allows get and set it's value.
 */

#pragma once

// Module definitions.
#include "./_def_.h"

// Core libraries.
#include "../types/fundamental.h"
#include "../types/string.h"


__OBJECT_BEGIN__

template<typename T>
struct item_return{ typedef T type; };

template<typename T>
typename item_return<T>::type as(const void*);

template<>
struct item_return<int>{ typedef int type; };
template<>
int as<int>(const void* data)
{
	return std::stoi((const char*)data);
}

template<>
struct item_return<double>{ typedef double type; };
template<>
double as<double>(const void* data)
{
	return std::stod((const char*)data);
}

template<>
struct item_return<std::string>{ typedef std::string type; };
template<>
std::string as<std::string>(const void* data)
{
	return std::string((const char*)data);
}

template <typename T>
inline xw::object::Attribute set_only(T* field)
{
	return xw::object::Attribute(
		[field](const std::shared_ptr<object::Object>& val) -> void {
			const auto str_val = val->__str__();
			*field = as<T>(str_val.c_str());
		}
	);
}

template<>
xw::object::Attribute set_only<std::string>(std::string* field)
{
	return xw::object::Attribute(
		[field](const std::shared_ptr<object::Object>& val) -> void {
			*field = val->__str__();
		}
	);
}

template <typename T>
xw::object::Attribute set_only(T* field)
{
	return xw::object::Attribute(
		[field](const std::shared_ptr<object::Object>& val) -> void {
			*field = as<T>(val->__str__().c_str());
		}
	);
}

template <typename T>
inline xw::object::Attribute full_access(T* field)
{
	return xw::object::Attribute(
		[field]() -> std::shared_ptr<object::Object> {
			return std::make_shared<types::Fundamental<T>>(*field);
		},
		[field](const std::shared_ptr<object::Object>& val) -> void {
			const auto str_val = val->__str__();
			*field = as<T>(str_val.c_str());
		}
	);
}

template<>
xw::object::Attribute full_access<std::string>(std::string* field)
{
	return xw::object::Attribute(
		[field]() -> std::shared_ptr<object::Object> {
			return std::make_shared<types::String>(*field);
		},
		[field](const std::shared_ptr<object::Object>& val) -> void {
			*field = val->__str__();
		}
	);
}

__OBJECT_END__
