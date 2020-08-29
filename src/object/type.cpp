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
 * An implementation of core/object/type.h
 */

#include "./type.h"

// C++ libraries
#include <memory>

#ifdef _MSC_VER
#include <stdexcept>
#else
#include <cxxabi.h>
#endif

// Framework modules.
#include "../strings.h"
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
	for (const auto& attr : obj.__attrs__)
	{
		this->_attrs.push_back(attr.first);
	}

	using T = decltype(obj);
	this->_is_const = std::is_const<T>::value;
	this->_is_volatile = std::is_volatile<T>::value;
	this->_is_lvalue_ref = std::is_lvalue_reference<T>::value;
	this->_is_rvalue_ref = std::is_rvalue_reference<T>::value;
}

// Statuses:
// 0 - operation succeeded
// 1 - a memory allocation failure occurred
// 2 - mangled_name is not a valid name under the C++ ABI mangling rules
// 3 - one of the arguments is invalid
std::string Type::demangle(const char* name)
{
#ifdef _MSC_VER
	return core::str::ltrim(core::str::ltrim(name, "class"));
#else
	int status = -4;
	std::unique_ptr<char, void(*)(void*)> res {
		abi::__cxa_demangle(name, nullptr, nullptr, &status),
		std::free
	};

	return status == 0 ? res.get() : name;
#endif
}

std::string Type::name() const
{
	return this->_name;
}

bool Type::is_const() const
{
	return this->_is_const;
}

bool Type::is_volatile() const
{
	return this->_is_volatile;
}

bool Type::is_lvalue_ref() const
{
	return this->_is_lvalue_ref;
}

bool Type::is_rvalue_ref() const
{
	return this->_is_rvalue_ref;
}

std::string Type::namespace_() const
{
	return this->_namespace;
}

std::vector<std::string> Type::attributes() const
{
	return this->_attrs;
}

bool Type::operator==(const Type& other) const
{
	return this->_name == other._name;
}

std::ostream& operator<<(std::ostream& out, const Type& obj)
{
	out << "<class '" + obj._name + "'>";
	return out;
}

[[nodiscard]] std::string Type::type_name(const Object& obj)
{
	return Type::demangle(typeid(obj).name());
}

__OBJECT_END__
