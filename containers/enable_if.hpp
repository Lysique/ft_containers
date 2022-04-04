/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 10:58:03 by tamighi           #+#    #+#             */
/*   Updated: 2022/04/04 11:04:56 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ENABLE_IF_HPP
# define FT_ENABLE_IF_HPP

namespace ft
{

template<bool B, class T = void>
struct enable_if
{
};

template<class T>
struct enable_if<true, T>
{
	typedef T	type;
};
	
}

#endif
