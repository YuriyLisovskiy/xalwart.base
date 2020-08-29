/*
 * Copyright (c) 2020 Yuriy Lisovskiy
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * core/object/type.h
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
