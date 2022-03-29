/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 13:11:50 by tamighi           #+#    #+#             */
/*   Updated: 2022/03/29 12:59:38 by tamighi          ###   ########.fr       */
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

template<typename T>
class	vector_const_iterator
{
	
public:

	typedef T		value_type;
	typedef T*	pointer;
	typedef T&	reference;

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

template<typename T>
class vector_iterator : public vector_const_iterator<T>
{

public:

	typedef T*			pointer;
	typedef T&			reference;
	typedef T			value_type;

public:

	explicit vector_iterator(pointer ptr) : vector_const_iterator<T>(ptr)
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

	typedef vector_iterator<T>		iterator;
	typedef vector_iterator<T>		const_iterator;
	typedef vector_iterator<T>		reverse_iterator;
	typedef vector_iterator<T>		const_reverse_iterator;
	typedef size_t					size_type;
	typedef T						value_type;
	typedef T*						pointer;
	typedef T&						reference;
	typedef const T& 				const_reference;
	typedef	Alloc					allocator_type;

public:

	/*   CONSTRUCTORS  */	
	vector(void)
		: _m_capacity(0), _m_size(0)
	{
	}

	vector(size_t n)
		: _m_capacity(n), _m_size(0)
	{
	}

	/*   DESTRUCTOR  */
	~vector(void)
	{
	}

	/*   VECTOR OPERATORS OVERLOAD  */
	vector&	operator=(vector &cpy)
	{
		_m_capacity = cpy._m_capacity;
		_m_size = cpy._m_size;
		_m_start = cpy._m_start;
		return (*this);
	}

	/*   ITERATORS FUNCTIONS  */	
	iterator	begin(void)
	{
		return (iterator(_m_start));
	}

	const_iterator	begin(void) const
	{
		return (const_iterator(_m_start));
	}

	iterator	end(void)
	{
		return (iterator(_m_start + _m_size));
	}

	const_iterator	end(void) const
	{
		return (const_iterator(_m_start + _m_size));
	}

	reverse_iterator	rbegin(void)
	{
		return (reverse_iterator(this->end()));
	}

	const_reverse_iterator	rbegin(void) const
	{
		return (const_reverse_iterator(this->end()));
	}

	reverse_iterator	rend(void)
	{
		return (reverse_iterator(this->begin()));
	}

	const_reverse_iterator	rend(void) const
	{
		return (const_reverse_iterator(this->begin()));
	}

	const_iterator	cbegin(void)
	{
		return (const_iterator(this->begin()));
	}

	const_iterator	cend(void)
	{
		return (const_iterator(this->end()));
	}

	const_reverse_iterator	crbegin(void)
	{
		return (const_reverse_iterator(this->end()));
	}

	const_reverse_iterator	crend(void)
	{
		return (const_reverse_iterator(this->begin()));
	}

	/*   CAPACITY FUNCTIONS  */
	size_type	size(void) const
	{
		return (this->_m_size);
	}

	size_type	max_size(void) const
	{
	//	return (allocator_traits_type::max_size(this->alloc()));
	//	return max possible size of vector(see alloc fct)
		return (this->_m_size);
	}

	void	resize(size_type new_size)
	{
		if (new_size < this->size())
			//erase elements start + new size to end
			;
		else
			//reserve new_size
			;
	}

	void	resize(size_type new_size, const T& val)
	{
		if (new_size < this->size())
			//erase elements start + new size to end
			;
		else
			//insert x from finish up to new_size - m_size elements
			;
	}

	size_type	capacity(void)
	{
		return (this->_m_capacity);
	}

	bool	empty(void)
	{
		return (this->_m_size == 0);
	}

	void	reserve(size_type new_cap)
	{
		if (this->_m_capacity < new_cap)
			// realloc memory or expand buffer/ + modify members
			;
		// not sure if it has to do something in the other case ...
	}

	void	shrink_to_fit(void)
	{
		//c++11
	}
	
	/*   ELEMENT ACCESS  */
	reference	operator[](size_type n)
	{
		return (this->_m_start[n]);
	}

	const_reference	operator[](size_type n) const
	{
		return (this->_m_start[n]);
	}

	reference	at(size_type n)
	{
		// only if in range
		return (this->_m_start[n];
	}

	const_reference	at(size_type n) const
	{
		// only if in range
		return (this->_m_start[n];
	}

	reference	front(void)
	{
		return (*this->_m_start);
	}

	const_reference	front(void) const
	{
		return (*this->_m_start);
	}

	reference	back(void)
	{
		return (this->_m_start[this->_m_size -1]);
	}

	const_reference	back(void) const
	{
		return (this->_m_start[this->_m_size -1]);
	}

	void	data(void)
	{
		//c++11
	}

	/*   MODIFIERS  */
	template<class InIt>
	void	assign(InIt first, InIt last)
	{
		iterator	it = this->begin();
		for (; it != this->end() && first != last; it++, first++)
			*it = *first;
		if (first == last)
			// erase all the other elements of this
			;
		else
			// insert all reminding elements from first to last
			;
	}

	void assign (size_type n, const value_type& val)
	{
		for (; n < this->_m_size; --n)
			*it = val;
	}

	void	push_back(void)
	{
	}

	void	pop_back(void)
	{
	}

	void	insert(void)
	{
	}

	void	erase(void)
	{
	}

	void	swap(void)
	{
	}

	void	clear(void)
	{
	}

	void	emplace(void)
	{
	}

	void	emplace_back(void)
	{
	}

private:

	pointer	_m_start; 
	size_t	_m_capacity; // size malloced
	size_t	_m_size; // size of the array, x elements
	//max size : max possible size of the array

}; /* End of vector class */



}; /* End of namespace ft */

#endif
