/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 11:05:11 by tamighi           #+#    #+#             */
/*   Updated: 2022/04/18 11:47:10 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "containers/map.hpp"
#include "containers/vector.hpp"
#include "containers/stack.hpp"
#include "containers/set.hpp"
#include <map>
#include <vector>
#include <stack>
#include <set>
#include <sys/time.h>

using namespace NAMESPACE;

template<class T>
void	print_cont(vector<T>& cont)
{
	std::cout << "Size : "<< cont.size() << ", capacity : " << cont.capacity() << std::endl;
	std::cout << "Iteration :\n";
	for (typename vector<T>::iterator it = cont.begin(); it != cont.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
}

template<class T, class Mapped>
void	print_cont(map<T, Mapped>& cont)
{
	std::cout << "Size : "<< cont.size() << std::endl;
	std::cout << "Iteration :\n";
	for (typename map<T, Mapped>::iterator it = cont.begin(); it != cont.end(); ++it)
		std::cout << it->first << " = " << it->second << ", ";
	std::cout << std::endl;
}

template<class T>
void	print_cont(set<T>& cont)
{
	std::cout << "Size : "<< cont.size() << std::endl;
	std::cout << "Iteration :\n";
	for (typename set<T>::iterator it = cont.begin(); it != cont.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
}

template<class T>
void	print_cont(stack<T>& cont)
{
	std::cout << "Size : "<< cont.size() << ", top : "<< cont.top() << std::endl;
	std::cout << std::endl;
}

int	main(void)
{
	std::cout << "---------------------Vector------------------\n\n";
	vector<int>		vec;
	vector<int>		vec2;
	struct timeval now;
	time_t		msec;
	time_t	msec2;
	print_cont(vec);
	std::cout << "\n--------Resize 10--------\n";
	vec.resize(10);
	print_cont(vec);
	std::cout << "\n--------Assign 4, 8--------\n";
	vec.assign(4, 8);
	print_cont(vec);
	std::cout << "\n--------Assign prev vector to new vector--------\n";
	vec2.assign(vec.begin(), vec.end());
	print_cont(vec);
	std::cout << "\n--------3x pop back--------\n";
	vec.pop_back();
	vec.pop_back();
	vec.pop_back();
	print_cont(vec);
	std::cout << "\n--------Push back x 1 000 000--------\n";
	gettimeofday(&now, 0);
	msec = now.tv_sec * 1000 + now.tv_usec / 1000;
	for (int i = 0; i < 1000000; ++i)
		vec.push_back(i);
	gettimeofday(&now, 0);
	msec2 = now.tv_sec * 1000 + now.tv_usec / 1000;
	std::cout << "Time taken : " << msec2 - msec << std::endl;
	std::cout << "Size : "<< vec.size() << ", Capacity : " << vec.capacity() << std::endl;
	std::cout << "\n--------Erase from begin + 3 to end - 1--------\n";
	vec.erase(vec.begin() + 3, vec.end() - 1);
	print_cont(vec);
	std::cout << "\n--------Insert at begining (3, 2)--------\n";
	vec.insert(vec.begin(), 3, 2);
	print_cont(vec);
	std::cout << "\n--------Clear--------\n";
	vec.clear();
	print_cont(vec);
	std::cout << "\n--------Operator= -------\n";
	vec = vec2;
	print_cont(vec);
	std::cout << "\n---------------------Stack------------------\n\n";
	stack<int>	st;
	std::cout << "\n--------Push 5 and 6--------\n";
	st.push(5);	
	st.push(6);	
	print_cont(st);
	std::cout << "\n--------Pop--------\n";
	st.pop();
	print_cont(st);
	std::cout << "\n---------------------Map------------------\n\n";
	map<std::string, int>	mp;
	map<std::string, int>::iterator	it;
	std::cout << "\n--------Insert by index--------\n";
	mp["Hello"] = 1;
	mp["Bouya"] = 3;
	print_cont(mp);
	std::cout << "\n--------Insert with map::insert--------\n";
	mp.insert(make_pair<std::string, int>("Carrot", 10));
	print_cont(mp);
	std::string	str = "mp ";
	std::cout << "\n--------Insert 100000 element-------\n";
	gettimeofday(&now, 0);
	msec = now.tv_sec * 1000 + now.tv_usec / 1000;
	for (int i = 0; i < 100000; ++i)
		mp[str + std::to_string(i)] = i;
	gettimeofday(&now, 0);
	msec2 = now.tv_sec * 1000 + now.tv_usec / 1000;
	std::cout << "Time taken : " << msec2 - msec << std::endl;
	std::cout << "\n--------Erase from beg + 10 to end-------\n";
	it = mp.begin();
	for (int i = 0; i < 10; ++i)
		++it;
	gettimeofday(&now, 0);
	msec = now.tv_sec * 1000 + now.tv_usec / 1000;
	mp.erase(it, mp.end());
	gettimeofday(&now, 0);
	msec2 = now.tv_sec * 1000 + now.tv_usec / 1000;
	std::cout << "Time taken : " << msec2 - msec << std::endl;
	print_cont(mp);
	std::cout << "\n---------------------Set------------------\n\n";
	set<int>	s;
	set<int>::iterator	it2;
	std::cout << "\n--------Insert with set::insert--------\n";
	s.insert(5);
	print_cont(s);
	std::cout << "\n--------Insert 100000 element-------\n";
	gettimeofday(&now, 0);
	msec = now.tv_sec * 1000 + now.tv_usec / 1000;
	for (int i = 0; i < 100000; ++i)
		s.insert(i);
	gettimeofday(&now, 0);
	msec2 = now.tv_sec * 1000 + now.tv_usec / 1000;
	std::cout << "Time taken : " << msec2 - msec << std::endl;
	std::cout << "\n--------Erase from beg + 10 to end-------\n";
	it2 = s.begin();
	for (int i = 0; i < 10; ++i)
		++it2;
	gettimeofday(&now, 0);
	msec = now.tv_sec * 1000 + now.tv_usec / 1000;
	s.erase(it2, s.end());
	gettimeofday(&now, 0);
	msec2 = now.tv_sec * 1000 + now.tv_usec / 1000;
	std::cout << "Time taken : " << msec2 - msec << std::endl;
	print_cont(s);
	return (0);
}
