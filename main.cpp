/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 13:13:12 by tamighi           #+#    #+#             */
/*   Updated: 2022/03/28 09:15:38 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "containers/vector.hpp"
#include <vector>

int	main(void)
{
	{
		ft::vector<int>	vec;
		ft::vector<int>	vec2(5);
		ft::vector<int>::iterator	it;
		ft::vector<int>::iterator	it2;
	}
	{
		std::vector<int> vec;
		std::vector<int> vec2(5);
		std::vector<int>::iterator	it;

		vec2.push_back(1);
		it = vec2.begin();
	}
}
