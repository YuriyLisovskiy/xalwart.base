/**
 * object/object.h
 *
 * Copyright (c) 2020 Yuriy Lisovskiy
 *
 * Purpose:
 * 	Main parent for all derived classes which need to be rendered
 * 	or for some other purposes.
 */

#pragma once

// C++ libraries.
#include <map>

// Module definitions.
#include "./_def_.h"

// Core libraries.
#include "./type.h"
#include "./attribute.h"
#include "../exceptions.h"


__OBJECT_BEGIN__

class Object
{
private:
	std::string _object_address;

protected:
	[[nodiscard]] std::string __address__() const;

public:
	std::map<std::string, Attribute> __attrs__;

	Object();
	virtual ~Object() = default;

	std::vector<char> __get_attr__(const char* attr_name) const;

	void __set_attr__(const char* attr_name, const std::vector<char>& data);

	bool __has_attr__(const char* attr_name) const;

	/// Returns 0 if objects are equal, -1 if 'this' is less
	///  than 'other' otherwise returns 1.
	/// Can be overridden.
	virtual short __cmp__(const Object* other) const;

	[[nodiscard]] virtual unsigned long __hash__() const;

	[[nodiscard]] Type __type__() const;

	template <typename _CastT>
	_CastT __cast__() const
	{
//		if constexpr (std::is_pointer<_CastT>::value)
//		{
//			return ((_CastT)this);
//		}

		return *((_CastT*)this);
	}

	[[nodiscard]] virtual std::string __str__() const;
	[[nodiscard]] virtual std::string __repr__() const;

	bool operator<(const Object& other) const;
	bool operator==(const Object& other) const;
	bool operator!=(const Object& other) const;
	bool operator>(const Object& other) const;
	bool operator<=(const Object& other) const;
	bool operator>=(const Object& other) const;

	friend std::ostream& operator<<(std::ostream& out, Object& obj);

	explicit virtual operator bool () const;
};

__OBJECT_END__
