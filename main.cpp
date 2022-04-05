/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 13:13:12 by tamighi           #+#    #+#             */
/*   Updated: 2022/04/05 12:29:19 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "containers/vector.hpp"
#include <vector>
#include "containers/pair.hpp"
#include "containers/iterator_traits.hpp"
#include "containers/reverse_iterator.hpp"
#include "containers/is_integral.hpp"
#include "containers/equal.hpp"
#include "containers/enable_if.hpp"

template<class Cont>
void	print_cont(Cont &cont)
{
	for (typename Cont::iterator it = cont.begin(); it != cont.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
}

int	main(void)
{
	using namespace ft;
	try
	{
		std::cout << "---------------------Std Vector------------------\n\n";
		std::cout << "-----Default Constructor-----\n\n";
		vector<int>	vec;
		std::cout << "\nSize :\n";
		std::cout << "vec : " << vec.size() << std::endl;
		std::cout << "Capacity :\n";
		std::cout << "vec : " << vec.capacity() << std::endl;
		std::cout << "Maxsize :\n";
		std::cout << "vec : " << vec.max_size() << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	try
	{
		std::cout << "-----Size Constructor-----\n\n";
		vector<int>	vec(2);
		std::cout << "Size :\n";
		std::cout << "vec : " << vec.size() << std::endl;
		std::cout << "Capacity :\n";
		std::cout << "vec : " << vec.capacity() << std::endl;
		std::cout << std::endl;
		print_cont(vec);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	try
	{
		std::cout << "-----Argument Constructor-----\n\n";
		int	t;
		t = 2;
		vector<int>	vec(3, t);
		std::cout << "Size :\n";
		std::cout << "vec : " << vec.size() << std::endl;
		std::cout << "Capacity :\n";
		std::cout << "vec : " << vec.capacity() << std::endl;
		std::cout << std::endl;
		print_cont(vec);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	try
	{
		std::cout << "-----Range Constructor-----\n\n";
		int	t;
		t = 2;
		std::vector<int>	vec2(3, t);
		vector<int>		vec(vec2.begin(), vec2.end());
		std::cout << "Size :\n";
		std::cout << "vec : " << vec.size() << std::endl;
		std::cout << "Capacity :\n";
		std::cout << "vec : " << vec.capacity() << std::endl;
		std::cout << std::endl;
		print_cont(vec);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	try
	{
		std::cout << "-----Operator= / Copy Constructor-----\n\n";
		int	t;
		t = 2;
		int	t2;
		t2 = 4;
		vector<int>		vec2(3, t);
		vector<int>		vec(vec2);
		vector<int>		vec3(4, t2);
		std::cout << "Size :\n";
		std::cout << "vec : " << vec.size() << std::endl;
		std::cout << "Capacity :\n";
		std::cout << "vec : " << vec.capacity() << std::endl;
		std::cout << "Vec iteration :\n";
		print_cont(vec);
		std::cout << "Vec3 iteration :\n";
		print_cont(vec2);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return (0);
}
