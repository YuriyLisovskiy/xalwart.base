/**
 * types/fundamental.h
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 *
 * Purpose: Object-based wrapper for basic (fundamental) C++ types.
 */

#pragma once

// Module definitions.
#include "./_def_.h"

// Core libraries.
#include "../object/object.h"
#include "../string_utils.h"
#include "../exceptions.h"


__TYPES_BEGIN__

template<class T>
concept fundamental_type = std::is_fundamental_v<T>;

template <fundamental_type internal_type>
class Fundamental final : public object::Object
{
protected:
	internal_type internal_value;

protected:
	template <fundamental_type OtherT>
	[[nodiscard]] inline short _cmp_result(OtherT other_val) const
	{
		if (this->internal_value < other_val)
		{
			return -1;
		}

		return this->internal_value == other_val ? 0 : 1;
	}

public:
	Fundamental() = default;

	~Fundamental() override = default;

	explicit Fundamental(internal_type val) : Fundamental()
	{
		this->internal_value = std::move(val);
	}

	Fundamental(const Fundamental& other)
	{
		if (this != &other)
		{
			this->internal_value = other.internal_value;
		}
	}

	template <typename T>
	[[nodiscard]] constexpr bool holds_type()
	{
		return std::is_same<internal_type, T>::value;
	}

	[[nodiscard]]
	inline internal_type get() const
	{
		return this->internal_value;
	}

	template <fundamental_type T>
	[[nodiscard]] inline Fundamental<T> fit_to()
	{
		return Fundamental<T>((T)this->internal_value);
	}

	[[nodiscard]]
	inline short __cmp__(const Object* other) const override
	{
		if (auto other_v = dynamic_cast<const Fundamental<bool>*>(other))
		{
			return this->_cmp_result(other_v->get());
		}

		if (auto other_v = dynamic_cast<const Fundamental<short int>*>(other))
		{
			return this->_cmp_result(other_v->get());
		}

		if (auto other_v = dynamic_cast<const Fundamental<unsigned short int>*>(other))
		{
			return this->_cmp_result(other_v->get());
		}

		if (auto other_v = dynamic_cast<const Fundamental<int>*>(other))
		{
			return this->_cmp_result(other_v->get());
		}

		if (auto other_v = dynamic_cast<const Fundamental<unsigned int>*>(other))
		{
			return this->_cmp_result(other_v->get());
		}

		if (auto other_v = dynamic_cast<const Fundamental<long int>*>(other))
		{
			return this->_cmp_result(other_v->get());
		}

		if (auto other_v = dynamic_cast<const Fundamental<unsigned long int>*>(other))
		{
			return this->_cmp_result(other_v->get());
		}

		if (auto other_v = dynamic_cast<const Fundamental<long long int>*>(other))
		{
			return this->_cmp_result(other_v->get());
		}

		if (auto other_v = dynamic_cast<const Fundamental<unsigned long long int>*>(other))
		{
			return this->_cmp_result(other_v->get());
		}

		if (auto other_v = dynamic_cast<const Fundamental<signed char>*>(other))
		{
			return this->_cmp_result(other_v->get());
		}

		if (auto other_v = dynamic_cast<const Fundamental<unsigned char>*>(other))
		{
			return this->_cmp_result(other_v->get());
		}

		if (auto other_v = dynamic_cast<const Fundamental<wchar_t>*>(other))
		{
			return this->_cmp_result(other_v->get());
		}

		if (auto other_v = dynamic_cast<const Fundamental<char8_t>*>(other))
		{
			return this->_cmp_result(other_v->get());
		}

		if (auto other_v = dynamic_cast<const Fundamental<char16_t>*>(other))
		{
			return this->_cmp_result(other_v->get());
		}

		if (auto other_v = dynamic_cast<const Fundamental<char32_t>*>(other))
		{
			return this->_cmp_result(other_v->get());
		}

		if (auto other_v = dynamic_cast<const Fundamental<float>*>(other))
		{
			return this->_cmp_result(other_v->get());
		}

		if (auto other_v = dynamic_cast<const Fundamental<double>*>(other))
		{
			return this->_cmp_result(other_v->get());
		}

		if (auto other_v = dynamic_cast<const Fundamental<long double>*>(other))
		{
			return this->_cmp_result(other_v->get());
		}

		throw core::TypeError(
			"'__cmp__' not supported between instances of '" + this->__type__().name() + "' and '" + other->__type__().name() + "'",
			_ERROR_DETAILS_
		);
	}

	[[nodiscard]]
	inline xw::string __str__() const override
	{
		if constexpr (std::is_same_v<internal_type, bool>)
		{
			return this->internal_value ? "true" : "false";
		}

		if constexpr (
			std::is_same_v<internal_type, double> ||
			std::is_same_v<internal_type, long double> ||
			std::is_same_v<internal_type, float>
		)
		{
			std::string value = str::rtrim(std::to_string(this->internal_value), "0");
			if (value.ends_with('.'))
			{
				value += "0";
			}

			return value;
		}

		if constexpr (std::is_same_v<internal_type, signed char> || std::is_same_v<internal_type, unsigned char>)
		{
			return std::string(1, this->internal_value);
		}

		return std::to_string(this->internal_value);
	}

	[[nodiscard]]
	inline xw::string __repr__() const override
	{
		return "xw::types::Fundamental<" + utility::demangle(
			typeid(internal_type).name()
		) + ">{" + this->__str__() + "}";
	}

	inline Fundamental<internal_type>& operator= (const internal_type& new_val)
	{
		this->internal_value = new_val;
		return *this;
	}

	inline Fundamental<internal_type> operator+ (const Fundamental<internal_type>& right)
	{
		return Fundamental<internal_type>(this->internal_value + right.internal_value);
	}

	inline Fundamental<internal_type> operator- (const Fundamental<internal_type>& right)
	{
		return Fundamental<internal_type>(this->internal_value - right.internal_value);
	}

	inline Fundamental<internal_type> operator+ ()
	{
		return Fundamental<internal_type>(+this->internal_value);
	}

	inline Fundamental<internal_type> operator- ()
	{
		return Fundamental<internal_type>(-this->internal_value);
	}

	inline Fundamental<internal_type> operator* (const Fundamental<internal_type>& right)
	{
		return Fundamental<internal_type>(this->internal_value * right.internal_value);
	}

	inline Fundamental<internal_type> operator/ (const Fundamental<internal_type>& right)
	{
		return Fundamental<internal_type>(this->internal_value / right.internal_value);
	}

	inline Fundamental<internal_type> operator% (const Fundamental<internal_type>& right)
	{
		return Fundamental<internal_type>(this->internal_value % right.internal_value);
	}

	inline bool operator== (const Fundamental<internal_type>& other) const
	{
		return this->__cmp__(&other) == 0;
	}

	inline bool operator!= (const Fundamental<internal_type>& other) const
	{
		return this->__cmp__(&other) != 0;
	}

	inline bool operator< (const Fundamental<internal_type>& other) const
	{
		return this->__cmp__(&other) == -1;
	}

	inline bool operator<= (const Fundamental<internal_type>& other) const
	{
		auto ret_val = this->__cmp__(&other);
		return ret_val == -1 || ret_val == 0;
	}

	inline bool operator> (const Fundamental<internal_type>& other) const
	{
		return this->__cmp__(&other) == 1;
	}

	inline bool operator>= (const Fundamental<internal_type>& other) const
	{
		auto ret_val = this->__cmp__(&other);
		return ret_val == 1 || ret_val == 0;
	}

	inline bool operator! ()
	{
		return !this->internal_value;
	}

	inline bool operator&& (const Fundamental<internal_type>& other) const
	{
		return this->internal_value && other.internal_value;
	}

	inline bool operator|| (const Fundamental<internal_type>& other) const
	{
		return this->internal_value || other.internal_value;
	}

	inline Fundamental<internal_type> operator& (const Fundamental<internal_type>& right)
	{
		return Fundamental<internal_type>(this->internal_value & right.internal_value);
	}

	inline Fundamental<internal_type> operator| (const Fundamental<internal_type>& right)
	{
		return Fundamental<internal_type>(this->internal_value | right.internal_value);
	}

	inline Fundamental<internal_type> operator~ ()
	{
		return Fundamental<internal_type>(~this->internal_value);
	}

	inline Fundamental<internal_type> operator^ (const Fundamental<internal_type>& right)
	{
		return Fundamental<internal_type>(this->internal_value ^ right.internal_value);
	}

	inline friend std::ostream& operator<<(std::ostream& out, Fundamental<internal_type>& obj)
	{
		return out << obj.internal_value;
	}

	inline friend std::istream& operator>>(std::istream& in, Fundamental<internal_type>& obj)
	{
		return in >> obj.internal_value;
	}

	template <std::integral IntegralConstantT>
	inline friend Fundamental<internal_type> operator<<(const Fundamental<internal_type>& value, IntegralConstantT ic)
	{
		return Fundamental<internal_type>(value.internal_value << ic);
	}

	template <std::integral IntegralConstantT>
	inline friend Fundamental<internal_type> operator>>(const Fundamental<internal_type>& value, IntegralConstantT ic)
	{
		return Fundamental<internal_type>(value.internal_value >> ic);
	}

	template <fundamental_type other_internal_type>
	inline friend Fundamental<internal_type> operator<<(
		const Fundamental<internal_type>& left, const Fundamental<other_internal_type>& right
	)
	{
		return Fundamental<internal_type>(left.internal_value << right.internal_value);
	}

	template <fundamental_type other_internal_type>
	inline friend Fundamental<internal_type> operator>>(
		const Fundamental<internal_type>& left, const Fundamental<other_internal_type>& right
	)
	{
		return Fundamental<internal_type>(left.internal_value >> right.internal_value);
	}

	inline Fundamental<internal_type>& operator+= (const Fundamental<internal_type>& other)
	{
		this->internal_value += other.internal_value;
		return *this;
	}

	template <fundamental_type T>
	inline Fundamental<internal_type>& operator+= (const T& other)
	{
		this->internal_value += other;
		return *this;
	}

	inline Fundamental<internal_type>& operator-= (const Fundamental<internal_type>& other)
	{
		this->internal_value -= other.internal_value;
		return *this;
	}

	template <fundamental_type T>
	inline Fundamental<internal_type>& operator-= (const T& other)
	{
		this->internal_value -= other;
		return *this;
	}

	inline Fundamental<internal_type>& operator*= (const Fundamental<internal_type>& other)
	{
		this->internal_value *= other.internal_value;
		return *this;
	}

	template <fundamental_type T>
	inline Fundamental<internal_type>& operator*= (const T& other)
	{
		this->internal_value *= other;
		return *this;
	}

	inline Fundamental<internal_type>& operator/= (const Fundamental<internal_type>& other)
	{
		this->internal_value /= other.internal_value;
		return *this;
	}

	template <fundamental_type T>
	inline Fundamental<internal_type>& operator/= (const T& other)
	{
		this->internal_value /= other;
		return *this;
	}

	inline Fundamental<internal_type>& operator%= (const Fundamental<internal_type>& other)
	{
		this->internal_value %= other.internal_value;
		return *this;
	}

	template <fundamental_type T>
	inline Fundamental<internal_type>& operator%= (const T& other)
	{
		this->internal_value %= other;
		return *this;
	}

	template <fundamental_type other_internal_type>
	inline Fundamental<internal_type>& operator&= (const Fundamental<other_internal_type>& other)
	{
		this->internal_value &= other.internal_value;
		return *this;
	}

	template <fundamental_type T>
	inline Fundamental<internal_type>& operator&= (const T& other)
	{
		this->internal_value &= other;
		return *this;
	}

	template <fundamental_type other_internal_type>
	inline Fundamental<internal_type>& operator|= (const Fundamental<other_internal_type>& other)
	{
		this->internal_value |= other.internal_value;
		return *this;
	}

	template <fundamental_type T>
	inline Fundamental<internal_type>& operator|= (const T& other)
	{
		this->internal_value |= other;
		return *this;
	}

	inline Fundamental<internal_type>& operator^= (const Fundamental<internal_type>& other)
	{
		this->internal_value ^= other.internal_value;
		return *this;
	}

	template <fundamental_type T>
	inline Fundamental<internal_type>& operator^= (const T& other)
	{
		this->internal_value ^= other;
		return *this;
	}

	template <std::integral IntegralConstantT>
	inline Fundamental<internal_type>& operator<<=(const IntegralConstantT& ic)
	{
		this->internal_value <<= ic;
		return *this;
	}

	template <std::integral IntegralConstantT>
	inline Fundamental<internal_type>& operator>>=(const IntegralConstantT& ic)
	{
		this->internal_value >>= ic;
		return *this;
	}

	inline Fundamental<internal_type>& operator<<=(const Fundamental<internal_type>& right)
	{
		this->internal_value <<= right.internal_value;
		return *this;
	}

	inline Fundamental<internal_type>& operator>>=(const Fundamental<internal_type>& right)
	{
		this->internal_value >>= right.internal_value;
		return *this;
	}

	inline internal_type& operator* ()
	{
		return this->internal_value;
	}

	inline explicit operator bool() const override
	{
		return this->internal_value;
	}
};

__TYPES_END__
