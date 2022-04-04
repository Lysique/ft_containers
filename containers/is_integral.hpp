/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 12:21:50 by tamighi           #+#    #+#             */
/*   Updated: 2022/04/04 13:05:18 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IS_INTEGRAL_HPP
# define FT_IS_INTEGRAL_HPP

namespace ft
{

template<class T, T v>
struct integral_constant
{
	typedef T					value_type;
	typedef integral_constant	type;

	static value_type			value = v;

	operator value_type() const
	{
		return (value);
	}
};

template <bool val>
bool const integral_constant<bool, val>::value;

typedef integral_constant<bool, true>	true_type;
typedef integral_constant<bool, false>	false_type;

template<class T>
struct is_integral : public ft::integral_constant
{
	typedef bool								value_type;
	typedef ft::integral_constant<bool, value>	type;
	static bool									value = ft::integral_constant<T>;
};

}

#endif
