/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:40:23 by tamighi           #+#    #+#             */
/*   Updated: 2022/04/04 14:03:08 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PAIR_HPP
# define FT_PAIR_HPP

namespace ft
{

template<class T1, class T2>
struct pair
{
	typedef T1	first_type;
	typedef T2	second_type;

	/*   CONSTRUCTORS  */
	pair(void)
		: first(), second()
	{
		//ENABLE_IF_CONSTRUCTIBLE
	}

	pair(const pair& cpy)
		: first(cpy.first), second(cpy.second)
	{
	}

	pair(const first_type& ft, const second_type& sc)
		: first(ft), second(sc)
	{
		//ENABLE_IF
	}

	template<class U1, class U2>
	pair(const pair<U1, U2>& p)
		: first(p.first), second(p.second)
	{
		//ENABLE_IF
	}

	/*   OPERATOR =  */
	pair&	operator=(const pair& other)
	{
		//ENABLE_IF_ASSIGNABLE
		first = other.first;
		second = other.second;
		return (*this);
	}
	
	first_type	first;
	second_type	second;
};

	/*   NON-MEMBER FUNCTIONS  */
template<class T1, class T2>
ft::pair<T1, T2>	make_pair(T1 first, T2 second)
{
	return (ft::pair<T1, T2>(first, second));
}

template<class T1, class T2>
bool	operator==(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
{
	return (lhs.first == rhs.first && lhs.second == rhs.second);
}

template<class T1, class T2>
bool	operator!=(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
{
	return (!(lhs == rhs));
}

template<class T1, class T2>
bool	operator<(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
{
	return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
}

template<class T1, class T2>
bool	operator>(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
{
	return (!(lhs < rhs));
}

template<class T1, class T2>
bool	operator<=(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
{
	return (!(lhs > rhs));
}

template<class T1, class T2>
bool	operator>=(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
{
	return (!(lhs < rhs));
}

}

#endif
