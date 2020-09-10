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
 * core/types/value.h
 *
 * Purpose:
 * 	Wrapper for fundamental types and classes which inherit Object.
 *
 * 	Provides arithmetic operations for fundamentals and some helper
 * 	methods.
 */

#pragma once

// Module definitions.
#include "./_def_.h"

// Framework modules.
#include "../object/object.h"
#include "../utility.h"
#include "../exceptions.h"


__TYPES_BEGIN__

template <typename _T>
class Value : public object::Object
{
protected:
	_T _internal_value;

public:
	Value() = default;

	~Value() override = default;

	explicit Value(_T val) : Value()
	{
		this->_internal_value = std::move(val);
	}

	Value(const Value& other)
	{
		if (this != &other)
		{
			this->_internal_value = other._internal_value;
		}
	}

	_T get() const
	{
		return this->_internal_value;
	}

	template <typename InternalType>
	constexpr bool internal_type_is()
	{
		return std::is_same<_T, InternalType>::value;
	}

	short __cmp__(const Object* other) const override
	{
		const Value<_T>* other_val = dynamic_cast<const Value<_T>*>(other);
		if (!other_val)
		{
			throw core::TypeError(
				"'__cmp__' not supported between instances of '" + this->__type__().name() + "' and unknown type"
			);
		}

		if (this->get() < other_val->get())
		{
			return -1;
		}

		return this->get() == other_val->get() ? 0 : 1;
	}

	[[nodiscard]] std::string __str__() const override
	{
		if constexpr (std::is_same<_T, std::string>::value)
		{
			return this->_internal_value;
		}
		else if constexpr (std::is_same<_T, const char*>::value)
		{
			return std::string(this->_internal_value);
		}
		else if constexpr (std::is_fundamental<_T>::value)
		{
			if constexpr (std::is_same<_T, bool>::value)
			{
				return this->_internal_value ? "true" : "false";
			}

			return std::to_string(this->_internal_value);
		}
		else if constexpr (std::is_base_of<Object, _T>::value)
		{
			return this->_internal_value.__str__();
		}

		return "<" + this->__type__().name() + " object at " + this->__address__() + ">";
	}

	[[nodiscard]] std::string __repr__() const override
	{
		if constexpr (std::is_same<_T, std::string>::value)
		{
			return "\"" + this->_internal_value + "\"";
		}
		else if constexpr (std::is_same<_T, const char*>::value)
		{
			return "\"" + std::string(this->_internal_value) + "\"";
		}
		else if constexpr (std::is_fundamental<_T>::value)
		{
			if constexpr (std::is_same<_T, bool>::value)
			{
				return this->_internal_value ? "true" : "false";
			}

			return std::to_string(this->_internal_value);
		}
		else if constexpr (std::is_base_of<Object, _T>::value)
		{
			return this->_internal_value.__repr__();
		}

		return "<" + this->__type__().name() + " object at " + this->__address__() + ">";
	}

	Value<_T>& operator=(const _T& new_val)
	{
		this->_internal_value = new_val;
		return *this;
	}

	Value<_T> operator+(const Value<_T>& right)
	{
		return Value<_T>(this->_internal_value + right._internal_value);
	}

	Value<_T> operator-(const Value<_T>& right)
	{
		return Value<_T>(this->_internal_value - right._internal_value);
	}

	Value<_T> operator*(const Value<_T>& right)
	{
		return Value<_T>(this->_internal_value * right._internal_value);
	}

	Value<_T> operator/(const Value<_T>& right)
	{
		return Value<_T>(this->_internal_value / right._internal_value);
	}

	Value<_T> operator%(const Value<_T>& right)
	{
		return Value<_T>(this->_internal_value % right._internal_value);
	}

	Value<_T> operator&(const Value<_T>& right)
	{
		return Value<_T>(this->_internal_value & right._internal_value);
	}

	Value<_T> operator|(const Value<_T>& right)
	{
		return Value<_T>(this->_internal_value | right._internal_value);
	}

	Value<_T> operator~()
	{
		return Value<_T>(~this->_internal_value);
	}

	Value<_T> operator^(const Value<_T>& right)
	{
		return Value<_T>(this->_internal_value ^ right._internal_value);
	}

	_T& operator*()
	{
		return this->_internal_value;
	}

	operator bool() const override
	{
		if constexpr (std::is_fundamental<_T>::value)
		{
			return this->_internal_value;
		}
		else if constexpr (
			std::is_same<_T, const char*>::value ||
			std::is_base_of<Object, _T>::value
		)
		{
			return this->_internal_value != nullptr;
		}
		else if constexpr (std::is_same<std::string, _T>::value)
		{
			return !this->_internal_value.empty();
		}

		return Object::operator bool();
	}
};

__TYPES_END__
