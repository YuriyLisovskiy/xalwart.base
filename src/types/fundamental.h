/**
 * types/fundamental.h
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 *
 * Object-based wrapper for basic (fundamental) C++ types.
 */

#pragma once

// STL libraries.
// TODO

// Module definitions.
#include "./_def_.h"

// Base libraries.
#include "../object/object.h"
#include "../string_utils.h"
#include "../exceptions.h"


__TYPES_BEGIN__

template<class T>
concept fundamental_type = std::is_fundamental_v<T>;

template <fundamental_type InternalT>
class Fundamental final : public obj::Object
{
protected:
	InternalT internal_value;

protected:

	// Compares two fundamentals.
	template <fundamental_type OtherT>
	[[nodiscard]]
	inline short _cmp_result(OtherT other_val) const
	{
		if (this->internal_value < other_val)
		{
			return -1;
		}

		return this->internal_value == other_val ? 0 : 1;
	}

public:

	// Default constructor.
	Fundamental() = default;

	// Calls `Object` destructor.
	inline ~Fundamental() override
	{
		obj::Object::~Object();
	};

	// Constructs `Fundamental` from value of basic type.
	inline Fundamental(InternalT val) : Fundamental()
	{
		this->internal_value = std::move(val);
	}

	// Copy constructor.
	inline Fundamental(const Fundamental& other)
	{
		if (this != &other)
		{
			this->internal_value = other.internal_value;
		}
	}

	// Checks if fundamental type is `T`.
	template <typename T>
	[[nodiscard]]
	inline constexpr bool holds_type()
	{
		return std::is_same<InternalT, T>::value;
	}

	// Returns an internal value.
	[[nodiscard]]
	inline InternalT get() const
	{
		return this->internal_value;
	}

	// Casts internal type to `T` and returns a new `Fundamental`
	// object.
	template <fundamental_type T>
	[[nodiscard]]
	inline Fundamental<T> fit_to()
	{
		return Fundamental<T>((T)this->internal_value);
	}

	// Compares `Fundamental` types.
	//
	// Throws `TypeError` if `other` object is not
	// `Fundamental` type.
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

		throw TypeError(
			"'__cmp__' not supported between instances of '" + this->__type__().name() +
			"' and '" + other->__type__().name() + "'",
			_ERROR_DETAILS_
		);
	}

	// Converts fundamental type to `std::string`. If internal type
	// is `bool`, returns `true`/`false`. If type is floating-point
	// (double, long double, float) trims unnecessary ending zeros.
	// Otherwise returns string representation of `internal_value`.
	[[nodiscard]]
	inline std::string __str__() const override
	{
		if constexpr (std::is_same_v<InternalT, bool>)
		{
			return this->internal_value ? "true" : "false";
		}

		if constexpr (
			std::is_same_v<InternalT, double> ||
			std::is_same_v<InternalT, long double> ||
			std::is_same_v<InternalT, float>
		)
		{
			std::string value = str::rtrim(std::to_string(this->internal_value), "0");
			if (value.ends_with('.'))
			{
				value += "0";
			}

			return value;
		}

		if constexpr (
			std::is_same_v<InternalT, signed char> ||
			std::is_same_v<InternalT, unsigned char> ||
			std::is_same_v<InternalT, char>
		)
		{
			return std::string(1, this->internal_value);
		}

		return std::to_string(this->internal_value);
	}

	[[nodiscard]]
	inline std::string __repr__() const override
	{
		if constexpr (
			std::is_same_v<InternalT, signed char> ||
			std::is_same_v<InternalT, unsigned char> ||
			std::is_same_v<InternalT, char>
		)
		{
			return "'" + std::string(1, this->internal_value) + "'";
		}

		return this->__str__();
	}

	inline Fundamental<InternalT>& operator= (const InternalT& new_val)
	{
		this->internal_value = new_val;
		return *this;
	}

	inline Fundamental<InternalT> operator+ (const Fundamental<InternalT>& right)
	{
		return Fundamental<InternalT>(this->internal_value + right.internal_value);
	}

	inline Fundamental<InternalT> operator- (const Fundamental<InternalT>& right)
	{
		return Fundamental<InternalT>(this->internal_value - right.internal_value);
	}

	inline Fundamental<InternalT> operator+ ()
	{
		return Fundamental<InternalT>(+this->internal_value);
	}

	inline Fundamental<InternalT> operator- ()
	{
		return Fundamental<InternalT>(-this->internal_value);
	}

	inline Fundamental<InternalT> operator* (const Fundamental<InternalT>& right)
	{
		return Fundamental<InternalT>(this->internal_value * right.internal_value);
	}

	inline Fundamental<InternalT> operator/ (const Fundamental<InternalT>& right)
	{
		return Fundamental<InternalT>(this->internal_value / right.internal_value);
	}

	inline Fundamental<InternalT> operator% (const Fundamental<InternalT>& right)
	{
		return Fundamental<InternalT>(this->internal_value % right.internal_value);
	}

	inline bool operator== (const Fundamental<InternalT>& other) const
	{
		return this->__cmp__(&other) == 0;
	}

	inline bool operator!= (const Fundamental<InternalT>& other) const
	{
		return this->__cmp__(&other) != 0;
	}

	inline bool operator< (const Fundamental<InternalT>& other) const
	{
		return this->__cmp__(&other) == -1;
	}

	inline bool operator<= (const Fundamental<InternalT>& other) const
	{
		auto ret_val = this->__cmp__(&other);
		return ret_val == -1 || ret_val == 0;
	}

	inline bool operator> (const Fundamental<InternalT>& other) const
	{
		return this->__cmp__(&other) == 1;
	}

	inline bool operator>= (const Fundamental<InternalT>& other) const
	{
		auto ret_val = this->__cmp__(&other);
		return ret_val == 1 || ret_val == 0;
	}

	inline bool operator! ()
	{
		return !this->operator bool();
	}

	inline bool operator&& (const Fundamental<InternalT>& other) const
	{
		return this->internal_value && other.internal_value;
	}

	inline bool operator|| (const Fundamental<InternalT>& other) const
	{
		return this->internal_value || other.internal_value;
	}

	inline Fundamental<InternalT> operator& (const Fundamental<InternalT>& right)
	{
		return Fundamental<InternalT>(this->internal_value & right.internal_value);
	}

	inline Fundamental<InternalT> operator| (const Fundamental<InternalT>& right)
	{
		return Fundamental<InternalT>(this->internal_value | right.internal_value);
	}

	inline Fundamental<InternalT> operator~ ()
	{
		return Fundamental<InternalT>(~this->internal_value);
	}

	inline Fundamental<InternalT> operator^ (const Fundamental<InternalT>& right)
	{
		return Fundamental<InternalT>(this->internal_value ^ right.internal_value);
	}

	inline friend std::ostream& operator<<(std::ostream& out, Fundamental<InternalT>& obj)
	{
		return out << obj.internal_value;
	}

	inline friend std::istream& operator>>(std::istream& in, Fundamental<InternalT>& obj)
	{
		return in >> obj.internal_value;
	}

	template <xw::integral IntegralConstantT>
	inline friend Fundamental<InternalT> operator<<(const Fundamental<InternalT>& value, IntegralConstantT ic)
	{
		return Fundamental<InternalT>(value.internal_value << ic);
	}

	template <xw::integral IntegralConstantT>
	inline friend Fundamental<InternalT> operator>>(const Fundamental<InternalT>& value, IntegralConstantT ic)
	{
		return Fundamental<InternalT>(value.internal_value >> ic);
	}

	template <fundamental_type other_internal_type>
	inline friend Fundamental<InternalT> operator<<(
		const Fundamental<InternalT>& left, const Fundamental<other_internal_type>& right
	)
	{
		return Fundamental<InternalT>(left.internal_value << right.internal_value);
	}

	template <fundamental_type other_internal_type>
	inline friend Fundamental<InternalT> operator>>(
		const Fundamental<InternalT>& left, const Fundamental<other_internal_type>& right
	)
	{
		return Fundamental<InternalT>(left.internal_value >> right.internal_value);
	}

	inline Fundamental<InternalT>& operator+= (const Fundamental<InternalT>& other)
	{
		this->internal_value += other.internal_value;
		return *this;
	}

	template <fundamental_type T>
	inline Fundamental<InternalT>& operator+= (const T& other)
	{
		this->internal_value += other;
		return *this;
	}

	inline Fundamental<InternalT>& operator-= (const Fundamental<InternalT>& other)
	{
		this->internal_value -= other.internal_value;
		return *this;
	}

	template <fundamental_type T>
	inline Fundamental<InternalT>& operator-= (const T& other)
	{
		this->internal_value -= other;
		return *this;
	}

	inline Fundamental<InternalT>& operator*= (const Fundamental<InternalT>& other)
	{
		this->internal_value *= other.internal_value;
		return *this;
	}

	template <fundamental_type T>
	inline Fundamental<InternalT>& operator*= (const T& other)
	{
		this->internal_value *= other;
		return *this;
	}

	inline Fundamental<InternalT>& operator/= (const Fundamental<InternalT>& other)
	{
		this->internal_value /= other.internal_value;
		return *this;
	}

	template <fundamental_type T>
	inline Fundamental<InternalT>& operator/= (const T& other)
	{
		this->internal_value /= other;
		return *this;
	}

	inline Fundamental<InternalT>& operator%= (const Fundamental<InternalT>& other)
	{
		this->internal_value %= other.internal_value;
		return *this;
	}

	template <fundamental_type T>
	inline Fundamental<InternalT>& operator%= (const T& other)
	{
		this->internal_value %= other;
		return *this;
	}

	template <fundamental_type other_internal_type>
	inline Fundamental<InternalT>& operator&= (const Fundamental<other_internal_type>& other)
	{
		this->internal_value &= other.internal_value;
		return *this;
	}

	template <fundamental_type T>
	inline Fundamental<InternalT>& operator&= (const T& other)
	{
		this->internal_value &= other;
		return *this;
	}

	template <fundamental_type other_internal_type>
	inline Fundamental<InternalT>& operator|= (const Fundamental<other_internal_type>& other)
	{
		this->internal_value |= other.internal_value;
		return *this;
	}

	template <fundamental_type T>
	inline Fundamental<InternalT>& operator|= (const T& other)
	{
		this->internal_value |= other;
		return *this;
	}

	inline Fundamental<InternalT>& operator^= (const Fundamental<InternalT>& other)
	{
		this->internal_value ^= other.internal_value;
		return *this;
	}

	template <fundamental_type T>
	inline Fundamental<InternalT>& operator^= (const T& other)
	{
		this->internal_value ^= other;
		return *this;
	}

	template <xw::integral IntegralConstantT>
	inline Fundamental<InternalT>& operator<<=(const IntegralConstantT& ic)
	{
		this->internal_value <<= ic;
		return *this;
	}

	template <xw::integral IntegralConstantT>
	inline Fundamental<InternalT>& operator>>=(const IntegralConstantT& ic)
	{
		this->internal_value >>= ic;
		return *this;
	}

	inline Fundamental<InternalT>& operator<<=(const Fundamental<InternalT>& right)
	{
		this->internal_value <<= right.internal_value;
		return *this;
	}

	inline Fundamental<InternalT>& operator>>=(const Fundamental<InternalT>& right)
	{
		this->internal_value >>= right.internal_value;
		return *this;
	}

	inline InternalT& operator* ()
	{
		return this->internal_value;
	}

	inline explicit operator bool() const override
	{
		return this->internal_value;
	}
};

// Lower-case wrapper for Fundamental<T> type.
template <typename T>
using fundamental = Fundamental<T>;

using char_ = fundamental<char>;
using unsigned_char = fundamental<unsigned char>;
using signed_char = fundamental<signed char>;
using int_ = fundamental<int>;
using unsigned_int = fundamental<unsigned int>;
using signed_int = fundamental<signed int>;
using short_int = fundamental<short int>;
using unsigned_short_int = fundamental<unsigned short int>;
using signed_short_int = fundamental<signed short int>;
using long_int = fundamental<long int>;
using signed_long_int = fundamental<signed long int>;
using unsigned_long_int = fundamental<unsigned long int>;
using long_long_int = fundamental<long long int>;
using unsigned_long_long_int = fundamental<unsigned long long int>;
using float_ = fundamental<float>;
using double_ = fundamental<double>;
using long_double = fundamental<long double>;
using wchar_t_ = fundamental<wchar_t>;

__TYPES_END__
