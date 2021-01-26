/**
 * object/type.h
 *
 * Copyright (c) 2020-2021 Yuriy Lisovskiy
 *
 * Purpose: represents basic metadata of class inherited from Object.
 */

#pragma once

// C++ libraries
#include <string>
#include <vector>

// Module definitions.
#include "./_def_.h"

// Core libraries.
#include "../utility.h"


__OBJECT_BEGIN__

class Object;

class Type final
{
private:
	friend class Object;

private:
	std::string _name;
	bool _is_const;
	bool _is_volatile;
	bool _is_lvalue_ref;
	bool _is_rvalue_ref;
	std::string _namespace;
	std::vector<std::string> _attrs;

	explicit Type(const Object& obj);

public:
	[[nodiscard]]
	inline std::string name() const
	{
		return this->_name;
	}

	[[nodiscard]]
	inline bool is_const() const
	{
		return this->_is_const;
	}

	[[nodiscard]]
	inline bool is_volatile() const
	{
		return this->_is_volatile;
	}

	[[nodiscard]]
	inline bool is_lvalue_ref() const
	{
		return this->_is_lvalue_ref;
	}

	[[nodiscard]]
	inline bool is_rvalue_ref() const
	{
		return this->_is_rvalue_ref;
	}

	[[nodiscard]]
	inline std::string namespace_() const
	{
		return this->_namespace;
	}

	[[nodiscard]]
	inline std::vector<std::string> attributes() const
	{
		return this->_attrs;
	}

	[[nodiscard]]
	static std::string type_name(const Object& obj);

	template<typename T>
	[[nodiscard]] inline static std::string type_name()
	{
		return utility::demangle(typeid(T).name());
	}

	template<typename T>
	[[nodiscard]] inline static std::string type()
	{
		std::string pre = std::is_fundamental<T>::value ? "built-in type" : "class";
		return "<" + pre + " '" + Type::type_name<T>() + "'>";
	}

	inline bool operator==(const Type& other) const
	{
		return this->_name == other._name;
	}

	inline friend std::ostream& operator<<(std::ostream& out, const Type& obj)
	{
		return out << "<class '" + obj._name + "'>";
	}
};

__OBJECT_END__
