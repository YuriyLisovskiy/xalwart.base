/**
 * types/vector.h
 *
 * Copyright (c) 2020-2021 Yuriy Lisovskiy
 *
 * Purpose: TODO
 */

#pragma once

// Module definitions.
#include "./_def_.h"

// Core libraries.
#include "../object/object.h"
#include "./fundamental.h"


__TYPES_BEGIN__

class Vector final : public object::Object
{
private:
	std::vector<std::shared_ptr<object::Object>> _arr;

public:
	typedef std::shared_ptr<object::Object> value_type;

	typedef std::allocator<value_type> allocator_type;

	typedef value_type& reference;
	typedef const value_type& const_reference;

	typedef typename std::allocator_traits<allocator_type>::pointer pointer;
	typedef typename std::allocator_traits<allocator_type>::const_pointer const_pointer;

	typedef typename std::vector<value_type>::iterator iterator;
	typedef typename std::vector<value_type>::const_iterator const_iterator;

	typedef typename std::reverse_iterator<iterator> reverse_iterator;
	typedef typename std::reverse_iterator<const_iterator> const_reverse_iterator;

	typedef typename std::iterator_traits<iterator>::difference_type difference_type;
	typedef typename std::vector<value_type>::size_type size_type;

private:
	void _check_index(size_type i) const;

	xw::string _aggregate(const std::function<xw::string(const value_type&)>& func) const;

public:
	inline explicit Vector(size_type size=0)
	{
		this->_arr = std::vector<value_type>(size);
	}

	inline explicit Vector(const std::vector<value_type>& other)
	{
		this->_arr = other;
	}

	template <fundamental_type T>
	inline explicit Vector(const std::vector<T>& other)
	{
		this->_arr.clear();
		for (const auto& o : other)
		{
			this->_arr.push_back(std::make_shared<Fundamental<T>>(o));
		}
	}

	inline Vector& operator= (const std::vector<value_type>& other)
	{
		this->_arr = other;
		return *this;
	}

	inline Vector& operator= (const Vector& other)
	{
		if (this != &other)
		{
			this->_arr = other._arr;
		}

		return *this;
	}

	template <fundamental_type T>
	inline Vector& operator= (const std::vector<T>& other)
	{
		this->_arr.clear();
		for (const auto& o : other)
		{
			this->_arr.push_back(std::make_shared<Fundamental<T>>(o));
		}

		return *this;
	}

	inline iterator begin()
	{
		return this->_arr.begin();
	}

	[[nodiscard]]
	inline const_iterator begin() const
	{
		return this->_arr.begin();
	}

	[[nodiscard]]
	inline const_iterator cbegin() const noexcept
	{
		return this->_arr.cbegin();
	}

	inline reverse_iterator rbegin()
	{
		return this->_arr.rbegin();
	}

	[[nodiscard]]
	inline const_reverse_iterator rbegin() const
	{
		return this->_arr.rbegin();
	}

	[[nodiscard]]
	inline const_reverse_iterator crbegin() const noexcept
	{
		return this->_arr.crbegin();
	}

	inline iterator end()
	{
		return this->_arr.end();
	}

	[[nodiscard]]
	inline const_iterator end() const
	{
		return this->_arr.end();
	}

	[[nodiscard]]
	inline const_iterator cend() const noexcept
	{
		return this->_arr.cend();
	}

	inline reverse_iterator rend()
	{
		return this->_arr.rend();
	}

	[[nodiscard]]
	inline const_reverse_iterator rend() const
	{
		return this->_arr.rend();
	}

	[[nodiscard]]
	inline const_reverse_iterator crend() const noexcept
	{
		return this->_arr.crend();
	}

	[[nodiscard]]
	inline size_type size() const noexcept
	{
		return this->_arr.size();
	}

	[[nodiscard]]
	inline size_type max_size() const noexcept
	{
		return this->_arr.max_size();
	}

	inline void resize(size_type new_size)
	{
		this->_arr.resize(new_size);
	}

	inline void resize(size_type new_size, const value_type& val)
	{
		this->_arr.resize(new_size, val);
	}

	[[nodiscard]]
	inline size_type capacity() const noexcept
	{
		return this->_arr.capacity();
	}

	[[nodiscard]]
	inline bool empty() const noexcept
	{
		return this->_arr.empty();
	}

	inline void reserve(size_type n)
	{
		this->_arr.reserve(n);
	}

	inline void shrink_to_fit()
	{
		this->_arr.shrink_to_fit();
	}

	reference operator[] (size_type i);

	const_reference operator[] (size_type i) const;

	reference at(size_type i);

	[[nodiscard]]
	const_reference at(size_type i) const;

	inline reference front()
	{
		return this->_arr.front();
	}

	[[nodiscard]]
	inline const_reference front() const
	{
		return this->_arr.front();
	}

	inline reference back()
	{
		return this->_arr.back();
	}

	[[nodiscard]]
	inline const_reference back() const
	{
		return this->_arr.back();
	}

	inline value_type* data() noexcept
	{
		return this->_arr.data();
	}

	[[nodiscard]]
	inline const value_type* data() const noexcept
	{
		return this->_arr.data();
	}

	template <class InputIterator>
	inline void assign(InputIterator first, InputIterator last)
	{
		this->_arr.assign(first, last);
	}

	inline void assign(size_type n, const value_type& val)
	{
		this->_arr.assign(n, val);
	}

	inline void assign(std::initializer_list<value_type> il)
	{
		this->_arr.assign(il);
	}

	template <class T>
	inline void push_back(const T& val)
	{
		if constexpr (std::is_fundamental_v<T>)
		{
			this->_arr.push_back(std::make_shared<Fundamental<T>>(val));
		}
		else if constexpr (std::is_base_of<Object, T>::value)
		{
			this->_arr.push_back(std::make_shared<T>(val));
		}
		else
		{
			throw std::invalid_argument("type mismatch");
		}
	}

// TODO: change const char* to std::string
//	inline void push_back(const char* val)
//	{
//		this->_arr->push_back(std::make_shared<Fundamental<const char*>>(val));
//	}

	inline void push_back(value_type&& val)
	{
		this->_arr.push_back(std::forward<value_type>(val));
	}

	inline void pop_back() noexcept
	{
		this->_arr.pop_back();
	}

	// single element (1)
	inline iterator insert(const_iterator position, const value_type& val)
	{
		return this->_arr.insert(position, val);
	}

	// single element (fundamentals or Object-inherited) (2)
	template <class T>
	inline iterator insert(const_iterator position, const T& val)
	{
		if constexpr (std::is_fundamental_v<T>)
		{
			return this->_arr.insert(position, std::make_shared<Fundamental<T>>(val));
		}
		else if constexpr (std::is_base_of<Object, T>::value)
		{
			return this->_arr.insert(position, std::make_shared<T>(val));
		}
		else
		{
			throw std::invalid_argument("type mismatch");
		}
	}

	// single element (c-string) (3)
// TODO: change const char* to std::string
//	inline iterator insert(const_iterator position, const char* val)
//	{
//		return this->_arr->insert(position, std::make_shared<Value<const char*>>(val));
//	}

	// fill (4)
	inline iterator insert(const_iterator position, size_type n, const value_type& val)
	{
		return this->_arr.insert(position, n, val);
	}

	// fill (fundamental or Object-inherited) (5)
	template <class T>
	inline iterator insert(const_iterator position, size_type n, const T& val)
	{
		if constexpr (std::is_fundamental_v<T>)
		{
			return this->_arr.insert(position, n, std::make_shared<Fundamental<T>>(val));
		}
		else if constexpr (std::is_base_of<Object, T>::value)
		{
			return this->_arr.insert(position, n, std::make_shared<T>(val));
		}
		else
		{
			throw std::invalid_argument("type mismatch");
		}
	}

	// fill (c-string) (6)
// TODO: change const char* to std::string
//	inline iterator insert(const_iterator position, size_type n, const char* val)
//	{
//		return this->_arr->insert(position, n, std::make_shared<Fundamental<const char*>>(val));
//	}

	// range (7)
	template <class InputIterator>
	inline iterator insert(const_iterator position, InputIterator first, InputIterator last)
	{
		return this->_arr.insert(position, first, last);
	}

	// move (8)
	inline iterator insert(const_iterator position, value_type&& val)
	{
		return this->_arr.insert(position, std::forward<value_type>(val));
	}

	// initializer list (9)
	inline iterator insert(const_iterator position, std::initializer_list<value_type> il)
	{
		return this->_arr.insert(position, il);
	}

	inline iterator erase(const_iterator position)
	{
		return this->_arr.erase(position);
	}

	inline iterator erase(const_iterator first, const_iterator last)
	{
		return this->_arr.erase(first, last);
	}

	inline void swap(Vector& x) noexcept
	{
		this->_arr.swap(x._arr);
	}

	inline void swap(std::vector<value_type>& x) noexcept
	{
		this->_arr.swap(x);
	}

	inline void clear() noexcept
	{
		this->_arr.clear();
	}

	template <class... Args>
	inline iterator emplace(const_iterator position, Args&&... args)
	{
		return this->_arr.emplace(position, std::forward<Args>(args)...);
	}

	template <class... Args>
	inline void emplace_back(Args&&... args)
	{
		this->_arr.emplace_back(std::forward<Args>(args)...);
	}

	[[nodiscard]]
	inline allocator_type get_allocator() const noexcept
	{
		return this->_arr.get_allocator();
	}

	inline friend bool operator== (const Vector& lhs, const Vector& rhs)
	{
		return lhs._arr == rhs._arr;
	}

	inline friend bool operator!= (const Vector& lhs, const Vector& rhs)
	{
		return lhs._arr != rhs._arr;
	}

	inline friend bool operator< (const Vector& lhs, const Vector& rhs)
	{
		return lhs._arr < rhs._arr;
	}

	inline friend bool operator<= (const Vector& lhs, const Vector& rhs)
	{
		return lhs._arr <= rhs._arr;
	}

	inline friend bool operator> (const Vector& lhs, const Vector& rhs)
	{
		return lhs._arr > rhs._arr;
	}

	inline friend bool operator>= (const Vector& lhs, const Vector& rhs)
	{
		return lhs._arr >= rhs._arr;
	}

	inline explicit operator bool () const override
	{
		return !this->_arr.empty();
	}

	inline void reverse()
	{
		std::reverse(this->_arr.begin(), this->_arr.end());
	}

	[[nodiscard]]
	xw::string __str__() const;

	[[nodiscard]]
	xw::string __repr__() const;

	[[nodiscard]]
	short __cmp__(const Object* other) const override;
};

__TYPES_END__
