/**
 * object/object.h
 *
 * Copyright (c) 2020-2021 Yuriy Lisovskiy
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


__OBJECT_BEGIN__

class Object
{
private:
	std::string _object_address;

protected:
	std::map<std::string, Attribute> __attrs__;

protected:
	[[nodiscard]]
	inline std::string __address__() const
	{
		return this->_object_address;
	}

public:
	typedef std::map<std::string, Attribute>::const_iterator attrs_iterator;
	typedef std::map<std::string, Attribute>::const_reverse_iterator attrs_reverse_iterator;

	[[nodiscard]]
	inline attrs_iterator attrs_begin() const noexcept
	{
		return this->__attrs__.cbegin();
	}

	[[nodiscard]]
	inline attrs_iterator attrs_end() const noexcept
	{
		return this->__attrs__.cend();
	}

	[[nodiscard]]
	inline attrs_reverse_iterator attrs_rbegin() const noexcept
	{
		return this->__attrs__.crbegin();
	}

	[[nodiscard]]
	inline attrs_reverse_iterator attrs_rend() const noexcept
	{
		return this->__attrs__.crend();
	}

	Object();

	virtual ~Object() = default;

	[[nodiscard]]
	virtual std::shared_ptr<Object> __get_attr__(const char* attr_name) const;

	virtual void __set_attr__(const char* attr_name, const void* data);

	[[nodiscard]]
	virtual inline bool __has_attr__(const char* attr_name) const
	{
		return this->__attrs__.find(attr_name) != this->__attrs__.end();
	}

	// Returns basic meta information of an object.
	[[nodiscard]]
	Type __type__() const;

	// String representation of an object.
	//
	// Can be overridden.
	[[nodiscard]]
	virtual std::string __str__() const;

	// Used for debugging. By default returns '__str__()'.
	//
	// Can be overridden.
	[[nodiscard]]
	virtual std::string __repr__() const;

	// Returns 0 if objects are equal, -1 if 'this' is less
	// than 'other' otherwise returns 1.
	//
	// Must be overridden.
	[[nodiscard]]
	virtual short __cmp__(const Object* other) const = 0;

	// By default returns true if '__attrs__' is not empty,
	// otherwise returns false.
	//
	// Can be overridden.
	explicit virtual operator bool () const;

	// By default returns true if '__attrs__' is empty.
	// otherwise returns false.
	//
	// Can be overridden.
	virtual bool operator! () const;
};

__OBJECT_END__
