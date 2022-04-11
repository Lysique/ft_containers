/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 09:29:40 by tamighi           #+#    #+#             */
/*   Updated: 2022/04/09 10:24:55 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "containers/stack.hpp"
#include <stack>
#include "containers/pair.hpp"
#include "containers/iterator_traits.hpp"
#include "containers/reverse_iterator.hpp"
#include "containers/is_integral.hpp"
#include "containers/equal.hpp"
#include "containers/enable_if.hpp"
#include <sys/time.h>

int	main(void)
{
	using namespace ft;
	std::cout << "----------------Stack----------------\n\n";
	ft::stack<int>	s;
	ft::stack<int>	s2;

	s.push(3);
	s.push(5);
	std::cout << s.top() << std::endl;
	s.pop();
	std::cout << s.top() << std::endl;
	s2 = s;
	std::cout << s2.top() << std::endl;
}
