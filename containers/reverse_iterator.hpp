/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 11:07:11 by tamighi           #+#    #+#             */
/*   Updated: 2022/04/04 12:18:54 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_REVERSE_ITERATOR_HPP
# define FT_REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft
{

template<class It>
class reverse_iterator
{

public:

	/*   DEFINES  */

	typedef It													iterator_type;
	typedef typename ft::iterator_traits<It>::iterator_category	iterator_category;
	typedef typename ft::iterator_traits<It>::value_type		value_type;
	typedef typename ft::iterator_traits<It>::difference_type	difference_type;
	typedef typename ft::iterator_traits<It>::pointer			pointer;
	typedef typename ft::iterator_traits<It>::reference			reference;

	/*   CONSTRUCTORS  */

	reverse_iterator(void)
	{
		m_current();
	}
	
	explicit reverse_iterator(iterator_type it)
	{
		m_current(it);
	}

	template<class U>
	reverse_iterator(const reverse_iterator<U>& other)
	{
		//ENABLE_IF
		m_current(other.base());
	}

	/*   OPERATOR OVERLOAD = */

	template<class U>
	reverse_iterator&	operator=(const reverse_iterator<U>& other)
	{
		m_current = other.base();
		return (*this);
	}

	/*   ITERATOR ACCESS  */
	iterator_type	base() const
	{
		return (m_current);
	}

	/*   ELEMENT POINTER ACCESS  */
	reference operator*(void) const
	{
		It	tmp(m_current);
		--tmp;
		reference	r = *tmp;
		return (r);
	}

	pointer operator->(void) const
	{
		It	tmp(m_current);
		--tmp;
		return (tmp.operator->());
	}

	/*   ELEMENT INDEX ACCESS  */
	value_type	&operator[](difference_type off) const
	{
		return (this->m_current[-off - 1]);
	}

	/*   INCREMENT/DECREMENT/ARITHMETIC OPERATORS  */
	reverse_iterator&	operator++(void)
	{
		--m_current;
		return (*this);
	}

	reverse_iterator&	operator--(void)
	{
		++m_current;
		return (*this);
	}

	reverse_iterator&	operator++(int)
	{
		reverse_iterator	tmp(*this);
		--(*this);
		return (tmp);
	}

	reverse_iterator&	operator--(int)
	{
		reverse_iterator	tmp(*this);
		++(*this);
		return (tmp);
	}

	reverse_iterator&	operator+(difference_type n) const
	{
		return (*this += n);
	}

	reverse_iterator&	operator-(difference_type n) const
	{
		return (*this -= n);
	}

	reverse_iterator&	operator+=(difference_type off)
	{
		this->m_current -= off;
		return (*this);
	}

	reverse_iterator&	operator-=(difference_type off)
	{
		this->m_current += off;
		return (*this);
	}

private:

	It	m_current;
};

	/*   NON-MEMBER FUNCTIONS  */ // ENABLE_IF ??
template<class It1, class It2>
bool	operator==(const ft::reverse_iterator<It1> lhs, const ft::reverse_iterator<It2> rhs)
{
	return (lhs.base() == rhs.base());
}

template<class It1, class It2>
bool	operator!=(const ft::reverse_iterator<It1> lhs, const ft::reverse_iterator<It2> rhs)
{
	return (lhs.base() != rhs.base());
}

template<class It1, class It2>
bool	operator>(const ft::reverse_iterator<It1> lhs, const ft::reverse_iterator<It2> rhs)
{
	return (lhs.base() < rhs.base());
}

template<class It1, class It2>
bool	operator<(const ft::reverse_iterator<It1> lhs, const ft::reverse_iterator<It2> rhs)
{
	return (lhs.base() > rhs.base());
}

template<class It1, class It2>
bool	operator>=(const ft::reverse_iterator<It1> lhs, const ft::reverse_iterator<It2> rhs)
{
	return (lhs.base() <= rhs.base());
}

template<class It1, class It2>
bool	operator<=(const ft::reverse_iterator<It1> lhs, const ft::reverse_iterator<It2> rhs)
{
	return (lhs.base() >= rhs.base());
}

template<class It>
reverse_iterator<It>	operator+(typename reverse_iterator<It>::difference_type off, const reverse_iterator<It>& it)
{
	return (it += off);
}

template<class It>
typename reverse_iterator<It>::difference_type	operator-
	(const reverse_iterator<It> lhs, const reverse_iterator<It>& rhs)
{
	return (rhs.base() - lhs.base());
}

}

#endif
