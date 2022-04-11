/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 11:05:11 by tamighi           #+#    #+#             */
/*   Updated: 2022/04/09 14:00:13 by tamighi          ###   ########.fr       */
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
#include <sys/time.h>

class MyClass
{
public:
	MyClass(void)
	{
		std::cout << "Constructed\n";
		x = 0;
	}
	MyClass(const MyClass &other)
	{
		std::cout << "Copied " << other.x << std::endl;
		x = other.x;
	}
	MyClass(int n)
	{
		std::cout << "Int copied\n";
		x = n;
	}
	~MyClass(void)
	{
		std::cout << "Destructed\n";
	}
	MyClass	&operator=(const MyClass &assign)
	{
		std::cout << "Assigned " << assign.x << std::endl;
		x = assign.x;
		return (*this);
	}
	MyClass	&operator=(int n)
	{
		std::cout << "Int assigned\n";
		x = n;
		return (*this);
	}
	int	x;
};

std::ostream	&operator<<(std::ostream &ost, MyClass &mc)
{
	ost << mc.x;
	return (ost);
}

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
}
