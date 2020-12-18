/**
 * object/object.h
 *
 * Copyright (c) 2020 Yuriy Lisovskiy
 *
 * Purpose:
 * 	Main parent for all derived classes which need to be rendered
 * 	or for some other purposes.
 */

/**
 * core/
 *
 * Purpose:

 */

#pragma once

// C++ libraries.
#include <map>
#include <functional>

// Module definitions.
#include "./_def_.h"

// Core libraries.
#include "./type.h"
#include "../exceptions.h"


__OBJECT_BEGIN__

struct Attr
{
private:
	void* _field;

public:
	Attr() = default;

	explicit Attr(void* field_addr)
	{
		this->_field = field_addr;
	}

	[[nodiscard]] void* get() const
	{
		return this->_field;
	}

	void set(void* val_ptr)
	{
		if (this->_field)
		{
			this->_field = val_ptr;
		}
	}

	template<typename ObjT>
	[[nodiscard]] ObjT get() const
	{
		if (this->_field)
		{
			return *static_cast<ObjT*>(this->_field);
		}

		return ObjT();
	}

	template<typename ObjT>
	void set(ObjT val_ptr)
	{
		this->set((void*) val_ptr);
	}
};

#define attr(name, field) {name, core::object::Attr(&(field))}

class Object
{
private:
	std::string _object_address;

protected:
	[[nodiscard]] std::string __address__() const;

public:
	std::map<std::string, Attr> __attrs__;

	Object();
	virtual ~Object() = default;

	void* __get_attr__(const char* attr_name) const
	{
		if (this->__has_attr__(attr_name))
		{
			return this->__attrs__.at(attr_name).get();
		}

		throw AttributeError(
			"'" + this->__type__().name() + "' object has no attribute '" + std::string(attr_name) + "'"
		);
	}

	void __set_attr__(const char* attr_name, void* ptr)
	{
		if (this->__has_attr__(attr_name))
		{
			this->__attrs__[attr_name].set(ptr);
		}
		else
		{
			throw AttributeError(
				"'" + this->__type__().name() + "' object has no attribute '" + std::string(attr_name) + "'"
			);
		}
	}

	template<typename ObjT>
	ObjT __get_attr__(const char* attr_name) const
	{
		return *(ObjT*)this->__get_attr__(attr_name);
	}

	template<typename ObjT>
	void __set_attr__(const char* attr_name, ObjT ptr)
	{
		this->__set_attr__(attr_name, (void*)ptr);
	}

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
		if constexpr (std::is_pointer<_CastT>::value)
		{
			return ((_CastT)this);
		}

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
