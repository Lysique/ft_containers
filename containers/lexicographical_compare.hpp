/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexicographical_compare.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:58:51 by tamighi           #+#    #+#             */
/*   Updated: 2022/04/05 12:09:29 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LEXICOGRAPHICAL_COMPARE_HPP
# define FT_LEXICOGRAPHICAL_COMPARE_HPP

namespace ft
{

template<class Init1, class Init2>
bool lexicographical_compare(Init1 first1, Init1 last1,
							Init2 first2, Init2 last2)
{
	for (; first1 != last1 && first2 != last2; ++first1, ++first2)
	{
		if (*first1 < *first2)
			return (true);
		if (*first2 < *first1)
			return (false);
	}
	return (first1 == last1 && first2 != last2);
}

template<class Init1, class Init2, class Compare>
bool lexicographical_compare(Init1 first1, Init1 last1,
							Init2 first2, Init2 last2,
							Compare comp)
{
	for (; first1 != last1 && first2 != last2; ++first1, ++first2)
	{
		if (comp(*first1, *first2))
			return (true);
		if (comp(*first2, *first1))
			return (false);
	}
	return (first1 == last1 && first2 != last2);
}

}

#endif
