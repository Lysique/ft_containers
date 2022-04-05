/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 13:11:50 by tamighi           #+#    #+#             */
/*   Updated: 2022/04/05 12:14:39 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include "iterator_traits.hpp"
#include "reverse_iterator.hpp"
#include "equal.hpp"
#include "lexicographical_compare.hpp"
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
		return (*this); }

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
		for (iterator it = this->begin(); it != this->end(); ++it)
			m_alloc.destroy(&(*it));
		m_alloc.deallocate(&(*this->begin()), this->m_capacity);
	}

	/*   VECTOR OPERATORS OVERLOAD  */
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
		if (new_size < this->size())
			this->erase(iterator(this->m_start + new_size), iterator(this->m_start + this->m_size));
		else if (new_size > this->m_capacity)
		{
			if (this->m_size << 1 > new_size)
				this->reserve(this->m_size << 1);
			else
				this->reserve(new_size);
			this->priv_insert_default_constructs(new_size - this->m_size);
		}
	}

	void	resize(size_type new_size, const value_type& val)
	{
		if (new_size < this->size())
			this->erase(iterator(this->m_start + new_size), iterator(this->m_start + this->m_size));
		else if (new_size > this->m_size)
		{
			if (new_size > this->m_capacity)
				this->reserve(new_size);
			this->priv_insert_copy_construct(this->end(), new_size - this->m_size, val);
		}
	}

	template<class Init>
	void	assign(Init first, Init last)
	{
		size_type	n = vector::priv_distance(first, last);
		if (n > this->m_size)
		{
			this->erase(this->begin(), this->end());
			this->reserve(n);
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

	void assign(size_type n, const value_type& val)
	{
		if (n > this->m_size)
		{
			this->erase(this->begin(), this->end());
			this->reserve(n);
			this->insert(this->begin(), n, val);
		}
		else
		{
			iterator	beg = this->begin();
			for (; n != 0; --n)
				*beg = val;
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
		if (this->m_size + n > this->m_capacity)
			this->reserve(this->m_size + n);
		if (this->m_size)
		{
			for (size_type i = n; i != 0; --i)
				m_alloc.construct(&(*(this->end() + i)), *(pos + i));
			for (size_type i = n; i != 0; --i)
				m_alloc.destroy(&(*(pos + i)));
		}
		priv_insert_copy_construct(pos, n, x);
	}

	template<class Init>
	void	insert(iterator pos, Init first, Init last)
	{
		size_type	n = vector::priv_distance(first, last);
		if (this->m_size + n > this->m_capacity)
			this->reserve(this->m_size + n);
		if (this->m_size)
		{
			for (size_type i = n; i != 0; --i)
				m_alloc.construct(&(*(this->end() + i)), *(pos + i));
			for (size_type i = n; i != 0; --i)
				m_alloc.destroy(&(*(pos + i)));
		}
		priv_insert_copy_range_construct(pos, first, last);
	}

	iterator	erase(iterator pos)
	{
		this->erase(pos, pos + 1);
		return (pos);
	}

	iterator	erase(iterator first, iterator last)
	{
		if (first != last)
		{
			iterator	it;
			iterator	it2;
			size_type	erased = 0;
			for (it = first; it != last; ++it, ++erased)
				this->m_alloc.destroy(&(*it));
			for (it = first, it2 = last; it2 != this->end(); ++it2, ++it)
				*it = *it2;
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

	template<class Init>
	void	priv_insert_copy_range_construct(iterator pos, Init first, Init last)
	{
		size_type	n = vector::priv_distance(first, last);

		this->m_size += n;
		for (; first != last; ++first, ++pos)
			m_alloc.construct(&(*pos), *first);
	}

	void	priv_insert_default_constructs(size_type n)
	{
		this->m_size += n;
		for (iterator from = this->end() - 1; n != 0; --n, --from)
			m_alloc.construct(&(*from));
	}

	void	priv_insert_copy_construct(iterator pos, size_type n, const value_type& val)
	{
		this->m_size += n;
		for (; n != 0; --n, ++pos)
			m_alloc.construct(&(*pos), val);
	}

	template<class Init>
	static size_type priv_distance(Init first, Init last)
	{
		size_type	n = 0;
		for (; first != last; ++first, ++n)
			;
		return (n);
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
