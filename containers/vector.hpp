/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 13:11:50 by tamighi           #+#    #+#             */
/*   Updated: 2022/03/28 11:08:04 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <iostream>
#include <memory>

namespace ft
{

/*									Vector const iterator class
 *
 */

template<class Pointer>
class	vector_const_iterator
{
	
public:

	typedef Pointer		value_type;
	typedef Pointer*	pointer;
	typedef Pointer&	reference;

public:

	/*  Default constructor */
	vector_const_iterator(void)
		: _ptr(0)
	{
	}

	/*  Pointer constructor */
	explicit	vector_const_iterator(pointer ptr)
		: _ptr(ptr)
	{
	}

	/*  			Operators overload 
	 */

	/*  Pointers operator */
	value_type	operator*(void) const
	{
		return(*_ptr);
	}

	const value_type*	operator->(void) const
	{
		return (_ptr);
	}

	reference operator[](value_type index) const
	{
		return (_ptr[index]);
	}

	vector_const_iterator	operator=(pointer ptr)
	{
		this->_ptr = ptr;
		return (*this);
	}

	/*  Increment/decrement */
	vector_const_iterator	&operator++(void)
	{
		++_ptr;
		return (*this);
	}

	vector_const_iterator	operator++(int)
	{
		pointer	ptr;

		ptr = _ptr;
		++*this;
		return (vector_const_iterator(ptr));
	}

	vector_const_iterator	&operator--(void)
	{
		--_ptr;
		return (*this);
	}

	vector_const_iterator	operator--(int)
	{
		pointer	ptr;

		ptr = _ptr;
		--*this;
		return (vector_const_iterator(ptr));
	}

	/*  Arithmetic operators */
	vector_const_iterator	&operator+=(int off)
	{
		_ptr += off;
		return (*this);
	}

	vector_const_iterator	&operator-=(int off)
	{
		_ptr -= off;
		return (*this);
	}

	vector_const_iterator operator+(int off) const
	{
		return (vector_const_iterator(_ptr + off));
	}

	vector_const_iterator operator-(int off) const
	{
		return (vector_const_iterator(_ptr - off));
	}

	//Friend needed for n + vector iterator arithmetic
	friend vector_const_iterator operator+(int off, vector_const_iterator& vec)
	{
		return (vector_const_iterator(off + vec._ptr));
	}

	friend vector_const_iterator operator-(int off, vector_const_iterator& vec)
	{
		return (vector_const_iterator(off - vec._ptr));
	}

	/*  Comparison operators */
	bool	operator==(vector_const_iterator& vec)
	{
		return (_ptr == vec._ptr);
	}

	bool	operator!=(vector_const_iterator& vec)
	{
		return (_ptr != vec._ptr);
	}

	bool	operator>=(vector_const_iterator& vec)
	{
		return (_ptr >= vec._ptr);
	}

	bool	operator<=(vector_const_iterator& vec)
	{
		return (_ptr <= vec._ptr);
	}

	bool	operator>(vector_const_iterator& vec)
	{
		return (_ptr > vec._ptr);
	}

	bool	operator<(vector_const_iterator& vec)
	{
		return (_ptr < vec._ptr);
	}

protected:
	
	pointer	_ptr;
};

	/*  End vector const iterator class */

	/*  									Vector iterator class 
	 *
	 */

template<class Pointer>
class vector_iterator : public vector_const_iterator<Pointer>
{

public:

	typedef Pointer*			pointer;
	typedef Pointer&			reference;
	typedef Pointer				value_type;

public:

	explicit vector_iterator(pointer ptr) : vector_const_iterator<Pointer>(ptr)
	{
	}

	vector_iterator(void)
	{
	}

	/*  Pointers operators overloads */
	
	reference	operator*(void)
	{
		return (*this->_ptr);
	}

	value_type*	operator->(void) const
	{
		return (this->_ptr);
	}

	reference operator[](value_type index) const
	{
		return (this->_ptr[index]);
	}

	/*  Increment/decrement */
	vector_iterator	&operator++(void)
	{
		++this->_ptr;
		return (*this);
	}

	vector_iterator	operator++(int)
	{
		pointer	ptr;

		ptr = this->_ptr;
		++*this;
		return (vector_iterator(ptr));
	}

	vector_iterator	&operator--(void)
	{
		--this->_ptr;
		return (*this);
	}

	vector_iterator	operator--(int)
	{
		pointer	ptr;

		ptr = this->_ptr;
		--*this;
		return (vector_iterator(ptr));
	}

	/*  Arithmetic operators */
	vector_iterator	&operator+=(int off)
	{
		this->_ptr += off;
		return (*this);
	}

	vector_iterator	&operator-=(int off)
	{
		this->_ptr -= off;
		return (*this);
	}

	vector_iterator operator+(int off) const
	{
		return (vector_iterator(this->_ptr + off));
	}

	vector_iterator operator-(int off) const
	{
		return (vector_iterator(this->_ptr - off));
	}

	friend vector_iterator operator+(int off, vector_iterator& vec)
	{
		return (vector_iterator(off + vec._ptr));
	}

	friend vector_iterator operator-(int off, vector_iterator& vec)
	{
		return (vector_iterator(off - vec._ptr));
	}

};
	/*										 Vector class
 	*
 	*/

template<typename T, class Alloc = std::allocator<T> >
class vector
{

	/*  TYPEDEFS */
public:

	typedef T	value_type;
	typedef T*	pointer;
	typedef T&	reference;

public:

	vector(void)
		: _capacity(0), _size(0)
	{
	}

private:

	pointer	_startPtr;
	size_t	_capacity;
	size_t	_size;


}; /* End of vector class */



}; /* End of namespace ft */

#endif
