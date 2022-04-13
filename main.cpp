/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 11:05:11 by tamighi           #+#    #+#             */
/*   Updated: 2022/04/13 15:45:20 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "containers/map.hpp"
#include <map>
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
		std::cout << it->first << " ";
	std::cout << std::endl;
}

int	main(void)
{
	{
		using namespace std;

		map<std::string, MyClass>	m;
		map<std::string, MyClass>::iterator	it;
		std::pair<map<std::string, MyClass>::iterator, bool>	te;
		m.insert(std::make_pair<std::string, MyClass>("opiou", 6));
		m.insert(std::make_pair<std::string, MyClass>("pou", 6));
		m.insert(std::make_pair<std::string, MyClass>("Ola", 5));
		m.insert(std::make_pair<std::string, MyClass>("Ela", 6));
		m.insert(std::make_pair<std::string, MyClass>("ila", 6));
		te = m.insert(std::make_pair<std::string, MyClass>("lili", 6));
		std::cout << te.second << std::endl;
		te = m.insert(std::make_pair<std::string, MyClass>("lili", 3));
		std::cout << te.second << std::endl;
		print_cont(m);
		//std::cout << m.max_size() << std::endl;
		//std::cout << m.get_allocator().max_size() << std::endl;
	}
	/*
	{
		using namespace ft;

		map<int, int>	m;
		m.insert(ft::make_pair<int, int>(0, 6));
		m.insert(ft::make_pair<int, int>(1, 6));
		m.insert(ft::make_pair<int, int>(2, 6));
		m.insert(ft::make_pair<int, int>(3, 5));
		m.insert(ft::make_pair<int, int>(4, 6));
		m.insert(ft::make_pair<int, int>(5, 6));
		m.insert(ft::make_pair<int, int>(6, 6));
		m.insert(ft::make_pair<int, int>(8, 6));
		m.insert(ft::make_pair<int, int>(9, 6));
		//print_cont(m);
		//std::cout << m.max_size() << std::endl;
		//std::cout << m.get_allocator().max_size() << std::endl;
	}
	*/
}
