/**
 * types/vector.cpp
 *
 * Copyright (c) 2020-2021 Yuriy Lisovskiy
 */

#include "./vector.h"


__TYPES_BEGIN__

void Vector::_check_index(size_type i) const
{
	if (i >= this->_arr.size())
	{
		throw std::out_of_range("index is out of range: " + std::to_string(i));
	}
}

std::string Vector::_aggregate(const std::function<std::string(const value_type&)>& func) const
{
	std::string res;
	for (auto it = this->_arr.begin(); it != this->_arr.end(); it++)
	{
		res += func(*it);
		if (it < this->_arr.end() - 1)
		{
			res += ", ";
		}
	}

	return res;
}

Vector::reference Vector::operator[] (size_type i)
{
	this->_check_index(i);
	return this->_arr[i];
}

Vector::const_reference Vector::operator[] (size_type i) const
{
	this->_check_index(i);
	return this->_arr[i];
}

Vector::reference Vector::at(size_type i)
{
	this->_check_index(i);
	return this->_arr.at(i);
}

Vector::const_reference Vector::at(size_type i) const
{
	this->_check_index(i);
	return this->_arr.at(i);
}

std::string Vector::__str__() const
{
	return "{" + this->_aggregate(
		[](const value_type& item) -> std::string { return item->__str__(); }
	) + "}";
}

std::string Vector::__repr__() const
{
	return "xw::types::Vector{" + this->_aggregate(
		[](const value_type& item) -> std::string { return item->__repr__(); }
	) + "}";
}

short Vector::__cmp__(const Object* other) const
{
	if (auto other_v = dynamic_cast<const Vector*>(other))
	{
		if (this->_arr == other_v->_arr)
		{
			return 0;
		}

		return this->_arr > other_v->_arr ? 1 : -1;
	}

	throw core::TypeError(
		"'__cmp__' not supported between instances of '" + this->__type__().name() + "' and '" + other->__type__().name() + "'",
		_ERROR_DETAILS_
	);
}

__TYPES_END__
