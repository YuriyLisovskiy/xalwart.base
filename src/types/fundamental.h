/**
 * types/fundamental.h
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 *
 * Purpose: TODO
 */

#pragma once

// C++ libraries.
#include <iostream>

// Module definitions.
#include "./_def_.h"

// Core libraries.
#include "../object/object.h"


__TYPES_BEGIN__

template<class T>
concept fundamental_type = std::is_fundamental_v<T>;

template <fundamental_type internal_type>
class Fundamental : public object::Object
{
protected:
	internal_type _internal_value;

public:
	Fundamental() = default;

	~Fundamental() override = default;

	explicit Fundamental(internal_type val) : Fundamental()
	{
		this->_internal_value = std::move(val);
	}

	Fundamental(const Fundamental& other)
	{
		if (this != &other)
		{
			this->_internal_value = other._internal_value;
		}
	}

	internal_type get() const
	{
		return this->_internal_value;
	}

	template <typename T>
	constexpr bool holds_type()
	{
		return std::is_same<internal_type, T>::value;
	}

	short __cmp__(const Object* other) const override
	{
		const auto other_val = dynamic_cast<const Fundamental<internal_type>*>(other);
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

	[[nodiscard]]
	std::string __str__() const override
	{
		if constexpr (std::is_same<internal_type, bool>::value)
		{
			return this->_internal_value ? "true" : "false";
		}

		return std::to_string(this->_internal_value);
	}

	[[nodiscard]]
	std::string __repr__() const override
	{
		return this->__str__();
	}

	Fundamental<internal_type>& operator= (const internal_type& new_val)
	{
		this->_internal_value = new_val;
		return *this;
	}

	Fundamental<internal_type> operator+ (const Fundamental<internal_type>& right)
	{
		return Fundamental<internal_type>(this->_internal_value + right._internal_value);
	}

	Fundamental<internal_type> operator- (const Fundamental<internal_type>& right)
	{
		return Fundamental<internal_type>(this->_internal_value - right._internal_value);
	}

	Fundamental<internal_type> operator+ ()
	{
		return Fundamental<internal_type>(+this->_internal_value);
	}

	Fundamental<internal_type> operator- ()
	{
		return Fundamental<internal_type>(-this->_internal_value);
	}

	Fundamental<internal_type> operator* (const Fundamental<internal_type>& right)
	{
		return Fundamental<internal_type>(this->_internal_value * right._internal_value);
	}

	Fundamental<internal_type> operator/ (const Fundamental<internal_type>& right)
	{
		return Fundamental<internal_type>(this->_internal_value / right._internal_value);
	}

	Fundamental<internal_type> operator% (const Fundamental<internal_type>& right)
	{
		return Fundamental<internal_type>(this->_internal_value % right._internal_value);
	}

	bool operator== (const Fundamental<internal_type>& other) const
	{
		return this->__cmp__(&other) == 0;
	}

	bool operator!= (const Fundamental<internal_type>& other) const
	{
		return this->__cmp__(&other) != 0;
	}

	bool operator< (const Fundamental<internal_type>& other) const
	{
		return this->__cmp__(&other) == -1;
	}

	bool operator<= (const Fundamental<internal_type>& other) const
	{
		auto ret_val = this->__cmp__(&other);
		return ret_val == -1 || ret_val == 0;
	}

	bool operator> (const Fundamental<internal_type>& other) const
	{
		return this->__cmp__(&other) == 1;
	}

	bool operator>= (const Fundamental<internal_type>& other) const
	{
		auto ret_val = this->__cmp__(&other);
		return ret_val == 1 || ret_val == 0;
	}

	bool operator! ()
	{
		return !this->_internal_value;
	}

	bool operator&& (const Fundamental<internal_type>& other) const
	{
		return this->_internal_value && other._internal_value;
	}

	bool operator|| (const Fundamental<internal_type>& other) const
	{
		return this->_internal_value || other._internal_value;
	}

	Fundamental<internal_type> operator& (const Fundamental<internal_type>& right)
	{
		return Fundamental<internal_type>(this->_internal_value & right._internal_value);
	}

	Fundamental<internal_type> operator| (const Fundamental<internal_type>& right)
	{
		return Fundamental<internal_type>(this->_internal_value | right._internal_value);
	}

	Fundamental<internal_type> operator~ ()
	{
		return Fundamental<internal_type>(~this->_internal_value);
	}

	Fundamental<internal_type> operator^ (const Fundamental<internal_type>& right)
	{
		return Fundamental<internal_type>(this->_internal_value ^ right._internal_value);
	}

	friend std::ostream& operator<<(std::ostream& out, Fundamental<internal_type>& obj)
	{
		return out << obj._internal_value;
	}

	friend std::istream& operator>>(std::istream& in, Fundamental<internal_type>& obj)
	{
		return in >> obj._internal_value;
	}

	template <std::integral IntegralConstantT>
	friend Fundamental<internal_type> operator<<(const Fundamental<internal_type>& value, IntegralConstantT ic)
	{
		return Fundamental<internal_type>(value._internal_value << ic);
	}

	template <std::integral IntegralConstantT>
	friend Fundamental<internal_type> operator>>(const Fundamental<internal_type>& value, IntegralConstantT ic)
	{
		return Fundamental<internal_type>(value._internal_value >> ic);
	}

	template <fundamental_type other_internal_type>
	friend Fundamental<internal_type> operator<<(
		const Fundamental<internal_type>& left, const Fundamental<other_internal_type>& right
	)
	{
		return Fundamental<internal_type>(left._internal_value << right._internal_value);
	}

	template <fundamental_type other_internal_type>
	friend Fundamental<internal_type> operator>>(
		const Fundamental<internal_type>& left, const Fundamental<other_internal_type>& right
	)
	{
		return Fundamental<internal_type>(left._internal_value >> right._internal_value);
	}

	template <fundamental_type other_internal_type>
	Fundamental<internal_type>& operator+= (const Fundamental<other_internal_type>& other)
	{
		this->_internal_value += other._internal_value;
		return *this;
	}

	template <fundamental_type T>
	Fundamental<internal_type>& operator+= (const T& other)
	{
		this->_internal_value += other;
		return *this;
	}

	template <fundamental_type other_internal_type>
	Fundamental<internal_type>& operator-= (const Fundamental<other_internal_type>& other)
	{
		this->_internal_value -= other._internal_value;
		return *this;
	}

	template <fundamental_type T>
	Fundamental<internal_type>& operator-= (const T& other)
	{
		this->_internal_value -= other;
		return *this;
	}

	template <fundamental_type other_internal_type>
	Fundamental<internal_type>& operator*= (const Fundamental<other_internal_type>& other)
	{
		this->_internal_value *= other._internal_value;
		return *this;
	}

	template <fundamental_type T>
	Fundamental<internal_type>& operator*= (const T& other)
	{
		this->_internal_value *= other;
		return *this;
	}

	template <fundamental_type other_internal_type>
	Fundamental<internal_type>& operator/= (const Fundamental<other_internal_type>& other)
	{
		this->_internal_value /= other._internal_value;
		return *this;
	}

	template <fundamental_type T>
	Fundamental<internal_type>& operator/= (const T& other)
	{
		this->_internal_value /= other;
		return *this;
	}

	template <fundamental_type other_internal_type>
	Fundamental<internal_type>& operator%= (const Fundamental<other_internal_type>& other)
	{
		this->_internal_value %= other._internal_value;
		return *this;
	}

	template <fundamental_type T>
	Fundamental<internal_type>& operator%= (const T& other)
	{
		this->_internal_value %= other;
		return *this;
	}

	template <fundamental_type other_internal_type>
	Fundamental<internal_type>& operator&= (const Fundamental<other_internal_type>& other)
	{
		this->_internal_value &= other._internal_value;
		return *this;
	}

	template <fundamental_type T>
	Fundamental<internal_type>& operator&= (const T& other)
	{
		this->_internal_value &= other;
		return *this;
	}

	template <fundamental_type other_internal_type>
	Fundamental<internal_type>& operator|= (const Fundamental<other_internal_type>& other)
	{
		this->_internal_value |= other._internal_value;
		return *this;
	}

	template <fundamental_type T>
	Fundamental<internal_type>& operator|= (const T& other)
	{
		this->_internal_value |= other;
		return *this;
	}

	template <fundamental_type other_internal_type>
	Fundamental<internal_type>& operator^= (const Fundamental<other_internal_type>& other)
	{
		this->_internal_value ^= other._internal_value;
		return *this;
	}

	template <fundamental_type T>
	Fundamental<internal_type>& operator^= (const T& other)
	{
		this->_internal_value ^= other;
		return *this;
	}

	template <std::integral IntegralConstantT>
	Fundamental<internal_type>& operator<<=(const IntegralConstantT& ic)
	{
		this->_internal_value <<= ic;
		return *this;
	}

	template <std::integral IntegralConstantT>
	Fundamental<internal_type>& operator>>=(const IntegralConstantT& ic)
	{
		this->_internal_value >>= ic;
		return *this;
	}

	template <fundamental_type other_internal_type>
	Fundamental<internal_type>& operator<<=(const Fundamental<other_internal_type>& right)
	{
		this->_internal_value <<= right._internal_value;
		return *this;
	}

	template <fundamental_type other_internal_type>
	Fundamental<internal_type>& operator>>=(const Fundamental<other_internal_type>& right)
	{
		this->_internal_value >>= right._internal_value;
		return *this;
	}

	internal_type& operator* ()
	{
		return this->_internal_value;
	}

	explicit operator bool() const override
	{
		return this->_internal_value;
	}
};

__TYPES_END__
