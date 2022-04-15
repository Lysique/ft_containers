/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 13:13:12 by tamighi           #+#    #+#             */
/*   Updated: 2022/04/15 12:24:55 by tamighi          ###   ########.fr       */
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

template<class Cont>
void	printSize(Cont &cont)
{
	std::cout << "Size : " << cont.size() << ", capacity : " << cont.capacity() << std::endl;
	(void)cont;
}

#define TESTED_TYPE int
#define TESTED_NAMESPACE ft
int	main(void)
{
	TESTED_NAMESPACE::vector<TESTED_TYPE> vct(7);
    TESTED_NAMESPACE::vector<TESTED_TYPE> vct_two(4);
    TESTED_NAMESPACE::vector<TESTED_TYPE> vct_three;
    TESTED_NAMESPACE::vector<TESTED_TYPE> vct_four;

    for (unsigned long int i = 0; i < vct.size(); ++i)
        vct[i] = (vct.size() - i) * 3;
    for (unsigned long int i = 0; i < vct_two.size(); ++i)
        vct_two[i] = (vct_two.size() - i) * 5;

    vct_three.assign(vct.begin(), vct.end());
    vct.assign(vct_two.begin(), vct_two.end());
    vct_two.assign(2, 42);
    vct_four.assign(4, 21);

    std::cout << "\t### After assign(): ###" << std::endl;


    vct_four.assign(6, 84);

    std::cout << "\t### assign() on enough capacity and low size: ###" << std::endl;

    printSize(vct);
	print_cont(vct);
	vct.erase(vct.begin(), vct.end());
    printSize(vct);
	print_cont(vct);
    vct.insert(vct.begin(), 5, 53);
    //vct.assign(5, 53);
    printSize(vct);
	print_cont(vct);
    vct_two.assign(vct_three.begin(), vct_three.begin() + 3);


    return (0);
	/*
	using namespace ft;	
	try
	{
		std::cout << "---------------------Vector------------------\n\n";
		std::cout << "-----Default Constructor-----\n\n";
		vector<int>	vec;
		std::cout << "Size : "<< vec.size() << ", Capacity : " << 
			vec.capacity() << ", MaxSize : " << vec.max_size() << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	try
	{
		std::cout << "-----Size Constructor-----\n\n";
		vector<int>	vec(2);
		std::cout << "Size : "<< vec.size() << ", Capacity : " << vec.capacity() << std::endl;
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
		std::cout << "Size : "<< vec.size() << ", Capacity : " << vec.capacity() << std::endl;
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
		std::cout << "Size : "<< vec.size() << ", Capacity : " << vec.capacity() << std::endl;
		print_cont(vec);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	try
	{
		std::cout << "-----Operator= / Copy Constructor-----\n\n";
		int	t = 2;
		int	t2 = 4;
		vector<int>		vec2(3, t);
		vector<int>		vec3(4, t2);
		vector<int>		vec(vec2);
		std::cout << "Size : "<< vec.size() << ", Capacity : " << vec.capacity() << std::endl;
		std::cout << "Vec iteration :\n";
		print_cont(vec);
		vec = vec3;
		std::cout << "Vec iteration :\n";
		print_cont(vec);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	try
	{
		std::cout << "-----Functions-----\n\n";
		std::cout << "Reserve :\n";
		vector<int>	vec;
		std::cout << "Size : "<< vec.size() << ", Capacity : " << vec.capacity() << std::endl;
		vec.reserve(3);
		std::cout << "Size : "<< vec.size() << ", Capacity : " << vec.capacity() << std::endl;
		std::cout << "Resize :\n";
		vec.resize(5, 10);
		std::cout << "Size : "<< vec.size() << ", Capacity : " << vec.capacity() << std::endl;
		print_cont(vec);
		std::cout << "Assign :\n";
		vec.assign(4, 8); 
		std::cout << "Size : "<< vec.size() << ", Capacity : " << vec.capacity() << std::endl;
		print_cont(vec);
		std::cout << "Pop back :\n";
		vec.pop_back();
		std::cout << "Size : "<< vec.size() << ", Capacity : " << vec.capacity() << std::endl;
		print_cont(vec);
		std::cout << "Push back :\n";
		{
			struct timeval now;
			gettimeofday(&now, 0);
			time_t msec = now.tv_sec * 1000 + now.tv_usec / 1000;
			for (int i = 0; i < 10000000; ++i)
				vec.push_back(i);
			gettimeofday(&now, 0);
			time_t msec2 = now.tv_sec * 1000 + now.tv_usec / 1000;
			std::cout << "Time taken : " << msec2 - msec << std::endl;
			std::cout << "Size : "<< vec.size() << ", Capacity : " << vec.capacity() << std::endl;
		}
		std::cout << "Assign :\n";
		vec.assign(5, 7);
		std::cout << "Size : "<< vec.size() << ", Capacity : " << vec.capacity() << std::endl;
		print_cont(vec);
		std::cout << "Insert :\n";
		vec.insert(vec.begin() + 2, 3, 2);
		std::cout << "Size : "<< vec.size() << ", Capacity : " << vec.capacity() << std::endl;
		print_cont(vec);
		vec.insert(vec.begin() + 2, vec.begin(), vec.end());
		std::cout << "Size : "<< vec.size() << ", Capacity : " << vec.capacity() << std::endl;
		print_cont(vec);
		std::cout << "Erase :\n";
		vec.erase(vec.begin(), vec.end() - 3);
		std::cout << "Size : "<< vec.size() << ", Capacity : " << vec.capacity() << std::endl;
		print_cont(vec);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return (0);
	*/
}
