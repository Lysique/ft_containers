/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equal.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:06:33 by tamighi           #+#    #+#             */
/*   Updated: 2022/04/04 13:15:07 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EQUAL_HPP
# define FT_EQUAL_HPP

namespace ft
{

template<class It1, class It2>
bool	equal(It1 first1, It1 last1, It2 first2)
{
	for (; first1 != last1; ++first1, ++first2)
		if (*first1 != *first2)
			return (false);
	return (true);
}

template<class It1, class It2, class BinaryPredicate>
bool	equal(It1 first1, It1 last1, It2 first2, BinaryPredicate bp)
{
	for (; first1 != last1; ++first1, ++first2)
		if (!bp(first1, first2))
			return (false);
	return (true);
}

}

#endif
