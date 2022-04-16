/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 09:32:12 by tamighi           #+#    #+#             */
/*   Updated: 2022/04/16 15:41:15 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STACK_HPP
# define FT_STACK_HPP

#include "vector.hpp"

namespace ft
{

template<class T, class Container = ft::vector<T> >
class stack
{

	/*   MEMBER TYPES  */

public:

	typedef Container							container_type;
	typedef typename Container::value_type		value_type;
	typedef typename Container::size_type		size_type;
	typedef typename Container::reference		reference;
	typedef typename Container::const_reference	const_reference;

	/*   FUNCTIONS  */

public:

	/*   CONSTRUCTORS  */
	stack(void)
		: c()
	{
	}

	explicit stack(const container_type& cont)
		: c(cont)
	{
	}

	stack (const stack& other)
	{
		*this = other;
	}

	/*   DESTRUCTOR  */
	~stack(void)
	{
	}

	/*   OPERATOR=  */
	stack&	operator=(const stack& other)
	{
		this->c = other.c;
		return (*this);
	}
	
	/*   ELEMENT ACCESS  */
	reference	top(void)
	{
		return (this->c.back());
	}

	const_reference	top(void) const
	{
		return (this->c.back());
	}

	/*   CAPACITY  */
	bool	empty(void) const
	{
		return (this->c.empty());
	}

	size_type	size(void) const
	{
		return (this->c.size());
	}

	/*   MODIFIERS  */
	void	push(const value_type& val)
	{
		this->c.push_back(val);
	}

	void	pop(void)
	{
		this->c.pop_back();
	}

	/*   RELATIONAL OPERATORS */
	bool	operator==(const stack& rhs) const
	{
		return (this->c == rhs.c);
	}

	bool	operator!=(const stack& rhs) const
	{
		return (this->c != rhs.c);
	}

	bool	operator>=(const stack& rhs) const
	{
		return (this->c >= rhs.c);
	}

	bool	operator<=(const stack& rhs) const
	{
		return (this->c <= rhs.c);
	}

	bool	operator>(const stack& rhs) const
	{
		return (this->c > rhs.c);
	}

	bool	operator<(const stack& rhs) const
	{
		return (this->c < rhs.c);
	}

	/*   MEMBER OBJECTS  */	

protected:

	container_type	c;
};

}

#endif
