/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 12:21:50 by tamighi           #+#    #+#             */
/*   Updated: 2022/04/04 15:35:51 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IS_INTEGRAL_HPP
# define FT_IS_INTEGRAL_HPP

namespace ft
{

template<class T, T v>
struct integral_constant
{
	typedef T						value_type;
	static const value_type			value = v;
	typedef integral_constant<T, v>	type;

	operator value_type() const
	{
		return (value);
	}
};

template<bool val>
struct integral_constant<bool, val>
{
	typedef bool							value_type;
	static const value_type					value = val;
	typedef integral_constant<bool, val>	type;

	operator value_type() const
	{
		return (value);
	}
};

typedef integral_constant<bool, true>	true_type;
typedef integral_constant<bool, false>	false_type;

template <class T> 
struct is_integral : false_type {};
template <class T>
struct is_integral<const T> : is_integral<T> {};
template <class T>
struct is_integral<volatile const T> : is_integral<T> {};
template <class T>
struct is_integral<volatile T> : is_integral<T> {};

template<>
struct is_integral<bool> : true_type {};

template<>
struct is_integral<char> : true_type {};

template<>
struct is_integral<char16_t> : true_type {};

template<>
struct is_integral<char32_t> : true_type {};

template<>
struct is_integral<wchar_t> : true_type {};

template<>
struct is_integral<short> : true_type {};

template<>
struct is_integral<int> : true_type {};

template<>
struct is_integral<long> : true_type {};

}

#endif
