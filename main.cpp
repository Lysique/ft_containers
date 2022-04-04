/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 13:13:12 by tamighi           #+#    #+#             */
/*   Updated: 2022/04/04 11:05:07 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "containers/vector.hpp"
#include <vector>
//#include "containers/pair.hpp"
//#include "containers/make_pair.hpp"
#include "containers/iterator_traits.hpp"
//#include "containers/reverse_iterator.hpp"
//#include "containers/is_integral.hpp"
//#include "containers/equal.hpp"
#include "containers/enable_if.hpp"

class test
{
public:
	test()
	{
		std::cout << "Class created\n";
		x = 0;
	}
	test(const test& t)
	{
		std::cout << "Copy created\n";
		x = t.x;
	}
	~test()
	{
		std::cout << "Class destructed\n";
	}
	test&	operator=(int i)
	{
		std::cout << "Int assign\n";
		x = i;
		return (*this);
	}
	test&	operator=(const test& t)
	{
		std::cout << "Copy assign\n";
		x = t.x;
		return (*this);
	}
	int	x;
};

std::ostream	&operator<<(std::ostream &ostr, test const &test)
{
	ostr << test.x;
	return (ostr);
}

int	main(void)
{
	using namespace ft;
	try
	{
		std::cout << "-----Operator= / Copy Constructor-----\n\n";
		test	t;
		t = 2;
		test	t2;
		t2 = 4;
		vector<test>		vec2(3, t);
		vector<test>		vec(vec2);
		vector<test>		vec3(4, t2);
		vec2 = vec3;
		std::cout << "\nSize :\n";
		std::cout << "vec : " << vec.size() << std::endl;
		std::cout << "\nCapacity :\n";
		std::cout << "vec : " << vec.capacity() << std::endl;
		std::cout << "\nMaxsize :\n";
		std::cout << "vec : " << vec.max_size() << std::endl;
		std::cout << std::endl;
		std::cout << "Vec iteration :\n";
		for (vector<test>::iterator it = vec.begin(); it != vec.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;
		std::cout << "Vec3 iteration :\n";
		for (vector<test>::iterator it = vec3.begin(); it != vec3.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
}

int	main2(void)
{
	using namespace ft;
	try
	{
		std::cout << "---------------------Std Vector------------------\n\n";
		std::cout << "-----Default Constructor-----\n\n";
		vector<test>	vec;
		std::cout << "\nSize :\n";
		std::cout << "vec : " << vec.size() << std::endl;
		std::cout << "\nCapacity :\n";
		std::cout << "vec : " << vec.capacity() << std::endl;
		std::cout << "\nMaxsize :\n";
		std::cout << "vec : " << vec.max_size() << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	try
	{
		std::cout << "-----Size Constructor-----\n\n";
		vector<test>	vec(2);
		std::cout << "\nSize :\n";
		std::cout << "vec : " << vec.size() << std::endl;
		std::cout << "\nCapacity :\n";
		std::cout << "vec : " << vec.capacity() << std::endl;
		std::cout << "\nMaxsize :\n";
		std::cout << "vec : " << vec.max_size() << std::endl;
		std::cout << std::endl;
		for (vector<test>::iterator it = vec.begin(); it != vec.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	try
	{
		std::cout << "-----Argument Constructor-----\n\n";
		test	t;
		t = 2;
		vector<test>	vec(3, t);
		std::cout << "\nSize :\n";
		std::cout << "vec : " << vec.size() << std::endl;
		std::cout << "\nCapacity :\n";
		std::cout << "vec : " << vec.capacity() << std::endl;
		std::cout << "\nMaxsize :\n";
		std::cout << "vec : " << vec.max_size() << std::endl;
		std::cout << std::endl;
		std::cout << "Vec iteration :\n";
		for (vector<test>::iterator it = vec.begin(); it != vec.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	try
	{
		std::cout << "-----Range Constructor-----\n\n";
		test	t;
		t = 2;
		std::vector<test>	vec2(3, t);
		vector<test>		vec(vec2.begin(), vec2.end());
		std::cout << "\nSize :\n";
		std::cout << "vec : " << vec.size() << std::endl;
		std::cout << "\nCapacity :\n";
		std::cout << "vec : " << vec.capacity() << std::endl;
		std::cout << "\nMaxsize :\n";
		std::cout << "vec : " << vec.max_size() << std::endl;
		std::cout << std::endl;
		std::cout << "Vec iteration :\n";
		for (vector<test>::iterator it = vec.begin(); it != vec.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	try
	{
		std::cout << "-----Operator= / Copy Constructor-----\n\n";
		test	t;
		t = 2;
		test	t2;
		t2 = 4;
		vector<test>		vec2(3, t);
		vector<test>		vec(vec2);
		vector<test>		vec3(4, t2);
		std::cout << "\nSize :\n";
		std::cout << "vec : " << vec.size() << std::endl;
		std::cout << "\nCapacity :\n";
		std::cout << "vec : " << vec.capacity() << std::endl;
		std::cout << "\nMaxsize :\n";
		std::cout << "vec : " << vec.max_size() << std::endl;
		std::cout << std::endl;
		std::cout << "Vec iteration :\n";
		for (vector<test>::iterator it = vec.begin(); it != vec.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;
		std::cout << "Vec3 iteration :\n";
		for (vector<test>::iterator it = vec3.begin(); it != vec3.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return (0);
}
