/**
 * object/type.h
 *
 * Copyright (c) 2020 Yuriy Lisovskiy
 *
 * Purpose: represents basic metadata of class inherited from Object.
 */

#pragma once

// C++ libraries
#include <string>
#include <vector>

// Module definitions.
#include "./_def_.h"


__OBJECT_BEGIN__

class Object;

class Type final
{
private:

	friend class Object;

	std::string _name;
	bool _is_const;
	bool _is_volatile;
	bool _is_lvalue_ref;
	bool _is_rvalue_ref;
	std::string _namespace;
	std::vector<std::string> _attrs;

	explicit Type(const Object& obj);

	// Converts typeid.name() to full name.
	static std::string demangle(const char* name);

public:
	[[nodiscard]] std::string name() const;
	[[nodiscard]] bool is_const() const;
	[[nodiscard]] bool is_volatile() const;
	[[nodiscard]] bool is_lvalue_ref() const;
	[[nodiscard]] bool is_rvalue_ref() const;
	[[nodiscard]] std::string namespace_() const;
	[[nodiscard]] std::vector<std::string> attributes() const;
	[[nodiscard]] static std::string type_name(const Object& obj);

	template<typename T>
	[[nodiscard]] static std::string type_name()
	{
		return Type::demangle(typeid(T).name());
	}

	template<typename T>
	[[nodiscard]] static std::string type()
	{
		std::string pre = std::is_fundamental<T>::value ? "built-in type" : "class";
		return "<" + pre + " '" + Type::type_name<T>() + "'>";
	}

	bool operator==(const Type& other) const;
	friend std::ostream& operator<<(std::ostream& out, const Type& obj);
};

__OBJECT_END__
