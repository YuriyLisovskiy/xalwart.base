/**
 * object/object.cpp
 *
 * Copyright (c) 2020 Yuriy Lisovskiy
 */

#include "./object.h"

// C++ libraries.
#include <sstream>


__OBJECT_BEGIN__

Object::Object()
{
	std::stringstream oss;
	oss << static_cast<const void*>(this);
	this->_object_address = oss.str();
}

std::string Object::__address__() const
{
	return this->_object_address;
}

Object* Object::__get_attr__(const char* attr_name) const
{
	if (this->__has_attr__(attr_name))
	{
		return this->__attrs__.at(attr_name).get();
	}

	throw AttributeError(
		"'" + this->__type__().name() + "' object has no attribute '" + std::string(attr_name) + "'"
	);
}

void Object::__set_attr__(const char* attr_name, Object* ptr)
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

bool Object::__has_attr__(const char* attr_name) const
{
	return this->__attrs__.find(attr_name) != this->__attrs__.end();
}

short Object::__cmp__(const Object* other) const
{
	auto this_hash = this->__hash__();
	auto other_hash = other->__hash__();
	if (this_hash < other_hash)
	{
		return -1;
	}

	return this_hash == other_hash ? 0 : 1;
}

unsigned long Object::__hash__() const
{
	return reinterpret_cast<std::uintptr_t>(this);
}

Type Object::__type__() const
{
	return Type(*this);
}

std::string Object::__str__() const
{
	return "<" + this->__type__().name() + " object at " + this->_object_address + ">";
}

std::string Object::__repr__() const
{
	return this->__str__();
}

bool Object::operator<(const Object& other) const
{
	return this->__cmp__(&other) == -1;
}

bool Object::operator==(const Object& other) const
{
	return this->__cmp__(&other) == 0;
}

bool Object::operator!=(const Object& other) const
{
	return this->__cmp__(&other) != 0;
}

bool Object::operator>(const Object& other) const
{
	return this->__cmp__(&other) == 1;
}

bool Object::operator<=(const Object& other) const
{
	return *this < other || *this == other;
}

bool Object::operator>=(const Object& other) const
{
	return *this > other || *this == other;
}

std::ostream& operator<<(std::ostream& out, Object& obj)
{
	out << obj.__str__();
	return out;
}

Object::operator bool () const
{
	for (const auto& attr : this->__attrs__)
	{
		if (!(bool)(*attr.second.get()))
		{
			return false;
		}
	}

	return true;
}

__OBJECT_END__
