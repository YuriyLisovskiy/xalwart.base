/**
 * object/meta.h
 *
 * Copyright (c) 2020-2021 Yuriy Lisovskiy
 *
 * Basic metadata representation of class inherited from `Object`.
 */

#pragma once

// C++ libraries
#include <string>

// Module definitions.
#include "./_def_.h"

// Base libraries.
#include "../utility.h"


__OBJ_BEGIN__
class Object;
__OBJ_END__


__OBJ_META_BEGIN__

class Type final
{
private:
	friend class xw::obj::Object;

private:
	std::string _name;
	std::string _namespace;

	// Splits name and namespace of the object into `_name` and
	// `_namespace`.
	explicit Type(const Object& obj);

public:
	[[nodiscard]]
	inline std::string name() const
	{
		return this->_name;
	}

	[[nodiscard]]
	inline std::string namespace_() const
	{
		return this->_namespace;
	}

	// Compares `Type` objects by name.
	inline bool operator==(const Type& other) const
	{
		return this->_name == other._name;
	}

	// Formats and writes to stream `Type` object.
	inline friend std::ostream& operator<<(std::ostream& out, const Type& obj)
	{
		return out << "<class '" + obj._name + "'>";
	}
};

// Retrieves a full name of any type including namespace.
template<typename T>
inline std::string type_name()
{
	return util::demangle(typeid(T).name());
}

__OBJ_META_END__
