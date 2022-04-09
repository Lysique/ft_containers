/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 13:11:50 by tamighi           #+#    #+#             */
/*   Updated: 2022/04/09 09:52:25 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <cstring>
#include "iterator_traits.hpp"
#include "reverse_iterator.hpp"
#include "equal.hpp"
#include "lexicographical_compare.hpp"
#include "is_integral.hpp"
#include "enable_if.hpp"
#include <iostream>

namespace ft
{

/*									Vector const iterator class
 *
 */

template<typename T>
class	vector_const_iterator
{
	
public:

	typedef T								value_type;
	typedef T*								pointer;
	typedef T&								reference;
	typedef	ft::iterator_traits<pointer>	difference_type;
	typedef	std::random_access_iterator_tag	iterator_category;

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

	friend vector_const_iterator operator+(int off, vector_const_iterator& vec)
	{
		return (vector_const_iterator(off + vec._ptr));
	}

	friend vector_const_iterator operator-(int off, vector_const_iterator& vec)
	{
		return (vector_const_iterator(off - vec._ptr));
	}

	/*  Comparison operators */
	bool	operator==(const vector_const_iterator& vec) const
	{
		return (_ptr == vec._ptr);
	}

	bool	operator!=(const vector_const_iterator& vec) const
	{
		return (_ptr != vec._ptr);
	}

	bool	operator>=(const vector_const_iterator& vec) const
	{
		return (_ptr >= vec._ptr);
	}

	bool	operator<=(const vector_const_iterator& vec) const
	{
		return (_ptr <= vec._ptr);
	}

	bool	operator>(const vector_const_iterator& vec) const
	{
		return (_ptr > vec._ptr);
	}

	bool	operator<(const vector_const_iterator& vec) const
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

	typedef vector_iterator<T>						iterator;
	typedef vector_const_iterator<T>				const_iterator;
	typedef ft::reverse_iterator<iterator>			reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
	typedef size_t									size_type;
	typedef T										value_type;
	typedef T*										pointer;
	typedef const T*								const_pointer;
	typedef ptrdiff_t								difference_type;
	typedef T&										reference;
	typedef const T& 								const_reference;
	typedef	Alloc									allocator_type;

public:

	/*   CONSTRUCTORS  */	

	vector(void)
		: m_start(0), m_capacity(0), m_size(0), m_alloc()
	{
	}

	explicit vector(const allocator_type& alloc)
		: m_start(0), m_capacity(0), m_size(0), m_alloc(alloc)
	{
	}

	explicit vector(size_t n, const allocator_type& alloc = allocator_type())
		: m_start(0), m_capacity(0), m_size(0), m_alloc(alloc)
	{
		this->resize(n);
	}

	explicit vector(size_t n, const value_type& val, const allocator_type& alloc = allocator_type())
		: m_start(0), m_capacity(0), m_size(0), m_alloc(alloc)
	{
		this->resize(n, val);
	}

	template<class Init>
	vector(Init first, Init last, const allocator_type& alloc = allocator_type())
		: m_start(0), m_capacity(0), m_size(0), m_alloc(alloc)
	{
		this->assign(first, last);
	}

	vector(const vector& other)
		: m_start(0), m_capacity(0), m_size(0), m_alloc()
	{
		*this = other;
	}

	/*   DESTRUCTOR  */
	~vector(void)
	{
		this->erase(this->begin(), this->end());
		m_alloc.deallocate(&(*this->begin()), this->m_capacity);
	}

	/*   VECTOR OPERATOR= */
	vector&	operator=(const vector &cpy)
	{
		this->assign(cpy.begin(), cpy.end());
		return (*this);
	}

	/*   GET_ALLOC  */

	allocator_type	get_allocator(void) const
	{
		return (this->alloc);
	}

	/*   ITERATORS FUNCTIONS  */	
	iterator	begin(void)
	{
		return (iterator(m_start));
	}

	const_iterator	begin(void) const
	{
		return (const_iterator(m_start));
	}

	iterator	end(void)
	{
		return (iterator(this->m_start + this->m_size));
	}

	const_iterator	end(void) const
	{
		return (const_iterator(m_start + m_size));
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

	/*   CAPACITY FUNCTIONS  */
	size_type	size(void) const
	{
		return (this->m_size);
	}

	size_type	max_size(void) const
	{
		return (this->m_alloc.max_size());
	}

	size_type	capacity(void) const
	{
		return (this->m_capacity);
	}

	bool	empty(void) const
	{
		return (this->m_size == 0);
	}

	void	reserve(size_type new_cap)
	{
		if (this->m_capacity < new_cap)
		{
			pointer new_start = m_alloc.allocate(new_cap, this->m_start);
			for (size_type i = 0; i < this->m_size; i++)
				m_alloc.construct(&(*(new_start + i)), *(this->m_start + i));
			for (size_type i = 0; i < this->m_size; i++)
				m_alloc.destroy(&(*(this->m_start + i)));
			if (this->m_start)
				m_alloc.deallocate(this->m_start, this->m_capacity);
			this->m_capacity = new_cap;
			this->m_start = new_start;
		}
	}

	/*   ELEMENT ACCESS  */
	reference	operator[](size_type n)
	{
		return (this->m_start[n]);
	}

	const_reference	operator[](size_type n) const
	{
		return (this->m_start[n]);
	}

	reference	at(size_type n)
	{
		if (n >= this->m_size)
			throw vector::OutOfRangeException();
		return (this->m_start[n]);
	}

	const_reference	at(size_type n) const
	{
		if (n >= this->m_size)
			throw vector::OutOfRangeException();
		return (this->m_start[n]);
	}

	reference	front(void)
	{
		return (*this->m_start);
	}

	const_reference	front(void) const
	{
		return (*this->m_start);
	}

	reference	back(void)
	{
		return (this->m_start[this->m_size -1]);
	}

	const_reference	back(void) const
	{
		return (this->m_start[this->m_size -1]);
	}

	pointer	data(void)
	{
		return (&(*this->m_start));
	}

	const_pointer	data(void) const
	{
		return (&(*this->m_start));
	}

	/*   MODIFIERS  */

	void	resize(size_type new_size)
	{
		if (new_size < this->m_size)
			this->erase(this->begin() + new_size, this->begin() + this->m_size);
		else if (new_size > this->m_size)
		{
			if (new_size > this->m_capacity)
				this->priv_opt_reserve(new_size);
			vector::priv_default_unin_copy(this->end(), new_size - this->m_size);
			this->m_size = new_size;
		}
	}

	void	resize(size_type new_size, const value_type& val)
	{
		if (new_size < this->size())
			this->erase(this->begin() + new_size, this->begin() + this->m_size);
		else if (new_size > this->m_size)
		{
			if (new_size > this->m_capacity)
				this->priv_opt_reserve(new_size);
			vector::priv_value_unin_copy(this->end(), val, new_size - this->m_size);
			this->m_size = new_size;
		}
	}

	void assign(size_type n, const value_type& val)
	{
		if (n > this->m_size)
		{
			this->erase(this->begin(), this->end());
			this->insert(this->begin(), n, val);
		}
		else
		{
			iterator	beg = this->begin();
			for (; n != 0; --n, ++beg)
				*beg = val;
			this->erase(beg, this->end());
		}
	}

	template<class Init>
	typename ft::enable_if<!ft::is_integral<Init>::value >::type	assign(Init first, Init last)
	{
		size_type	n = vector::priv_distance(first, last);
		if (n > this->m_size)
		{
			this->erase(this->begin(), this->end());
			this->insert(this->begin(), first, last);
		}
		else
		{
			iterator	beg = this->begin();
			for (; first != last; ++first, ++beg)
				*beg = *first;
			this->erase(beg, this->end());
		}
	}

	void	push_back(const value_type& val)
	{
		this->resize(this->m_size + 1, val);
	}

	void	pop_back(void)
	{
		this->m_alloc.destroy(&(*(this->end() - 1)));
		--this->m_size;
	}

	iterator	insert(iterator pos, const T& x)
	{
		this->insert(pos, 1, x);
		return (pos);
	}

	void	insert(iterator pos, size_type n, const T& x)
	{
		size_type n_pos = vector::priv_distance(this->begin(), pos);
		if (this->m_size + n > this->m_capacity)
			this->priv_alloc_and_insert_value(n_pos, x, n);
		else
			this->priv_move_and_insert_value(n_pos, x, n);
	}

	template<class Init>
	typename ft::enable_if<!ft::is_integral<Init>::value >::type	insert(iterator pos, Init first, Init last)
	{
		size_type	n = vector::priv_distance(first, last);
		size_type	n_pos = vector::priv_distance(this->begin(), pos);
		if (this->m_size + n > this->m_capacity)
			this->priv_alloc_and_insert_range(n_pos, first, last);
		else
			this->priv_move_and_insert_range(n_pos, first, last);
	}

	iterator	erase(iterator pos)
	{
		return (this->erase(pos, pos + 1));
	}

	iterator	erase(iterator first, iterator last)
	{
		if (first != last)
		{
			size_type	erased = vector::priv_distance(first, last);
			pointer		it2 = &*last;
			for (pointer it = &*first; it2 != &*this->end(); ++it2, ++it)
				*it = *it2;
			for (pointer new_end = &*(this->end() - erased); new_end != &*this->end(); ++new_end)
				this->m_alloc.destroy(new_end);
			this->m_size -= erased;
		}
		return (first);
	}

	void	swap(vector& x)
	{
		vector	vec;

		vec = *this;
		*this = x;
		x = vec;
	}

	void	clear(void)
	{
		for (iterator it = this->begin(); it != this->end(); ++it)
			this->m_alloc.destroy(it);
		this->m_size = 0;
	}

private:

	void	priv_opt_reserve(size_type new_size)
	{
		if (this->m_capacity << 1 > new_size)
			this->reserve(this->m_capacity << 1);
		else
			this->reserve(new_size);
	}

	void	priv_alloc_and_insert_value(size_type pos, const value_type& val, size_type n)
	{
		pointer		new_start;
		size_type	new_size = this->m_size + n;
		size_type	new_capacity;
		if (this->m_capacity << 1 > new_size)
		{
			new_capacity = this->m_capacity << 1;
			new_start = m_alloc.allocate(this->m_capacity << 1);
		}
		else
		{
			new_capacity = new_size;
			new_start = m_alloc.allocate(new_size);
		}
		vector::priv_value_unin_copy(iterator(new_start + pos), val, n);
		vector::priv_range_unin_copy(iterator(new_start), this->begin(), this->begin() + pos);
		vector::priv_range_unin_copy(iterator(new_start) + pos + n, this->begin() + pos, this->end());
		this->erase(this->begin(), this->end());
		m_alloc.deallocate(&*this->m_start, this->m_capacity);
		this->m_capacity = new_capacity;
		this->m_start = new_start;
		this->m_size = new_size;
	}

	void	priv_move_and_insert_value(size_type pos, const value_type& val, size_type n)
	{
		if (this->m_size - pos >= n)
		{
			vector::priv_range_unin_copy(this->end(), this->end() - n, this->end());
			vector::priv_range_copy_backward(this->end(), this->end() - n,  this->begin() + pos);
			vector::priv_value_copy(this->begin() + pos, val, n);
		}
		else
		{
			size_type	elem_moved = this->m_size - pos;
			vector::priv_range_unin_copy_backward(this->end() + n, this->end(), this->end() - elem_moved);
			vector::priv_value_unin_copy_backward(this->end() + n - elem_moved, val, n - elem_moved);
			vector::priv_value_copy_backward(this->end(), val, elem_moved);
		}
		this->m_size += n;
	}

	template<class Init>
	void	priv_alloc_and_insert_range(size_type pos, Init first, Init last)
	{
		pointer		new_start;
		size_type	n = vector::priv_distance(first, last);
		size_type	new_size = this->m_size + n;
		size_type	new_capacity;
		if (this->m_capacity << 1 > new_size)
		{
			new_capacity = this->m_capacity << 1;
			new_start = m_alloc.allocate(this->m_capacity << 1);
		}
		else
		{
			new_capacity = new_size;
			new_start = m_alloc.allocate(new_size);
		}
		vector::priv_range_unin_copy(iterator(new_start + pos), first, last);
		vector::priv_range_unin_copy(iterator(new_start), this->begin(), this->begin() + pos);
		vector::priv_range_unin_copy(iterator(new_start + pos + n), this->begin() + pos, this->end());
		this->erase(this->begin(), this->end());
		m_alloc.deallocate(&*this->m_start, this->m_capacity);
		this->m_capacity = new_capacity;
		this->m_start = new_start;
		this->m_size = new_size;
	}

	template<class Init>
	void	priv_move_and_insert_range(size_type pos, Init first, Init last)
	{
		size_type	n = vector::priv_distance(first, last);
		if (this->m_size - pos >= n)
		{
			vector::priv_range_unin_copy(this->end(), this->end() - n, this->end());
			vector::priv_range_copy_backward(this->end(), this->end() - n,  this->begin() + pos);
			vector::priv_range_copy(this->begin() + pos, first, last);
		}
		else
		{
			size_type	elem_moved = this->m_size - pos;
			vector::priv_range_unin_copy_backward(this->end() + n, this->end(), this->end() - elem_moved);
			vector::priv_range_unin_copy_backward(this->end() + n - elem_moved, last, first + elem_moved);
			vector::priv_range_copy_backward(this->end(), first + elem_moved, first);
		}
		this->m_size += n;
	}

	/*	Insert a copy at initialized memory, using the = operator */
	static void	priv_value_copy(iterator pos, const value_type& val, size_type n)
	{
		for (pointer p_pos = &*pos; n != 0; --n, ++p_pos)
			*p_pos = val;
	}

	static void	priv_value_copy_backward(iterator pos,	const value_type& val, size_type n)
	{
		pointer	p_pos = &*pos - 1;
		
		for (; n != 0; --n, --p_pos)
			*p_pos = val;
	}

	template<class Init>
	static void	priv_range_copy(iterator pos, Init first, Init last)
	{
		for (; first != last; ++first, ++pos)
			*pos = *first;
	}

	static void	priv_range_copy(iterator pos, iterator first, iterator last)
	{
		pointer	p_pos = &*pos;
		pointer	p_first = &*first;
		pointer	p_last = &*last;
		
		for (; p_first != p_last; ++p_first, ++p_pos)
			*p_pos = *p_first;
	}

	template<class Init>
	static void	priv_range_copy_backward(iterator pos, Init first, Init last)
	{
		pointer	p_pos = &*pos - 1;
		Init	p_first = first - 1;
		Init	p_last = last - 1;
		
		for (; p_first != p_last; --p_first, --p_pos)
			*p_pos = *p_first;
	}

	static void	priv_range_copy_backward(iterator pos, iterator first, iterator last)
	{
		pointer	p_pos = &*pos - 1;
		pointer	p_first = &*first - 1;
		pointer	p_last = &*last - 1;
		
		for (; p_first != p_last; --p_first, --p_pos)
			*p_pos = *p_first;
	}

	/*   Insert a copy at an uninitialized memory, using Allocator.construct() */
	void	priv_default_unin_copy(iterator pos, size_type n)
	{
		for (pointer it = &*pos; n != 0; --n, ++it)
			m_alloc.construct(&(*it));
	}

	void	priv_value_unin_copy_backward(iterator pos, const value_type& val, size_type n)
	{
		for (pointer p_pos = &*pos - 1; n != 0; --n, --p_pos)
			m_alloc.construct(p_pos, val);
	}

	void	priv_value_unin_copy(iterator pos, const value_type& val, size_type n)
	{
		for (pointer it = &*pos; n != 0; --n, ++it)
			m_alloc.construct(it, val);
	}

	template<class Init>
	void	priv_range_unin_copy_backward(iterator pos, Init first, Init last)
	{
		pointer	p_pos = &*pos - 1;
		Init	p_first = first - 1;
		Init	p_last = last - 1;
		
		for (; p_first != p_last; --p_first, --p_pos)
			m_alloc.construct(p_pos, *p_first);
	}

	void	priv_range_unin_copy_backward(iterator pos, iterator first, iterator last)
	{
		pointer	p_pos = &*pos - 1;
		pointer	p_first = &*first - 1;
		pointer	p_last = &*last - 1;
		
		for (; p_first != p_last; --p_first, --p_pos)
			m_alloc.construct(p_pos, *p_first);
	}

	template<class Init>
	void	priv_range_unin_copy(iterator pos, Init first, Init last)
	{
		for (; first != last; ++first, ++pos)
			m_alloc.construct(&*pos, *first);
	}

	void	priv_range_unin_copy(iterator pos, iterator first, iterator last)
	{
		pointer	p_first = &*first;
		pointer	p_last = &*last;
		pointer	p_pos = &*pos;
		for (; p_first != p_last; ++p_first, ++p_pos)
			m_alloc.construct(&(*p_pos), *p_first);
	}

	template<class Init>
	static size_type priv_distance(Init first, Init last)
	{
		size_type	n = 0;
		for (; first != last; ++first, ++n)
			;
		return (n);
	}

	static size_type priv_distance(iterator first, iterator last) 
	{
		difference_type	ptrdiff = &(*last) - &(*first);
		return (ptrdiff);
	}

private:

	class	OutOfRangeException : public std::out_of_range
	{
	public :
		OutOfRangeException()
			: std::out_of_range("Ft::vector : Index out of bounds") {}
	};

private:

	pointer		m_start; 
	size_t		m_capacity;
	size_t		m_size;
	Alloc		m_alloc;

}; /* End of vector class */

	/*	NON-MEMBER FUNCTIONS*/
template<class T, class Alloc>
bool	operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
	return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template<class T, class Alloc>
bool	operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
	return (!(lhs == rhs));
}

template<class T, class Alloc>
bool	operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
	return (!(lhs < rhs));
}

template<class T, class Alloc>
bool	operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
	return (!(lhs > rhs));
}

template<class T, class Alloc>
bool	operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
	return (!(lhs >= rhs));
}

template<class T, class Alloc>
bool	operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
	return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template<class T, class Alloc>
void	swap(vector<T, Alloc>& lhs, vector<T, Alloc>& rhs)
{
	lhs.swap(rhs);
}

} /* End of namespace ft */

#endif
