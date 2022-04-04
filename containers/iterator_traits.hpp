/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 10:30:41 by tamighi           #+#    #+#             */
/*   Updated: 2022/04/04 15:56:06 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ITERATOR_TRAITS_HPP
# define FT_ITERATOR_TRAITS_HPP

#include <iostream>

namespace ft
{

template<class It>
struct iterator_traits
{
	typedef typename It::difference_type	difference_type;
	typedef typename It::value_type			value_type;
	typedef typename It::pointer			pointer;
	typedef typename It::reference			reference;
	typedef typename It::iterator_category	iterator_category;
};

template<class T>
struct iterator_traits<T*>
{
	typedef ptrdiff_t						difference_type;
	typedef T								value_type;
	typedef T*								pointer;
	typedef T&								reference;
	typedef std::random_access_iterator_tag	iterator_category;
};

template<class T>
struct iterator_traits<const T*>
{
	typedef ptrdiff_t						difference_type;
	typedef T								value_type;
	typedef const T*						pointer;
	typedef const T&						reference;
	typedef std::random_access_iterator_tag	iterator_category;
};

}

#endif
