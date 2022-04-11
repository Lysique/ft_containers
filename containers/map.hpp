/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 11:05:49 by tamighi           #+#    #+#             */
/*   Updated: 2022/04/11 11:07:38 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MAP_HPP
#define FT_MAP_HPP

#include "pair.hpp"

namespace ft
{

template<class T>
class map_iterator : public const_map_iterator<T>
{

public:
	map_iterator(void)
		: map_const_iterator()
	{
	}
}

template<class T>
class vector_const_iterator
{

public:
	map_const_iterator(void)
		: m_ptr(0);

	T*	m_ptr;
}


template<class Key, class T, class Compare = std::less<Key>, class Alloc = allocator<ft::pair<const Key, T> >
class map
{

	/*   MEMBER TYPES  */
public:

	typedef Key										key_type;
	typedef T										mapped_type;
	typedef ft::pair<const Key, T>					value_type;
	typedef size_t									size_type;
	typedef ptrdiff_t								difference_type;
	typedef Compare									compare_type;
	typedef Alloc									allocator_type;
	typedef value_type&								reference;
	typedef const value_type&						const_reference;
	typedef Alloc::pointer							pointer;
	typedef Alloc::const_pointer					const_pointer;
	typedef	map_iterator<T>							iterator;
	typedef map_const_iterator<T>					const_iterator;
	typedef ft::reverse_iterator<iterator>			reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

	/*   MEMBER FUNCTIONS  */
public:

	/*   CONSTRUCTORS  */
	map(const allocator_type& alloc = allocator_type())
		: m_alloc(alloc)
	{
		m_null = newNode(0, 0);
		m_root = m_null;
	}

	explicit map(const compare_type& comp, const allocator_type& alloc = allocator_type())
		: m_alloc(alloc)
	{
		(void)comp;
	}

	template<class Init>
	map(Init first, Init last, const compare_type& comp = compare_type(),
		const allocator_type& alloc = allocator_type())
		: m_alloc(alloc)
	{
		(void)first;
		(void)last;
		(void)comp;
	}

	map(const map& other)
	{
		(void)other;
	}

	/*   DESTRUCTOR  */
	~map(void)
	{
	}

	/*   MODIFIERS  */

	std::pair<iterator, bool>	insert(const value_type& value)
	{
		if (m_root == m_null)
	}

private:

	node*	newNode(const value_type& val, node* parent)
	{
		node*	new_node = new node(val, parent);
		return (new_node);
	}

	/*   MEMBER ATTRIBUTES  */
private:

	struct node
	{
		node(const value_type& value, node* par, bool col)
			: color(col), val(value), parent(par), left(NULL), right(NULL)
		{
		}
		node(node* par, bool col)
			: color(col), val(), parent(par), left(NULL), right(NULL)
		{
		}
		bool		color;
		value_type	val;
		node		*parent;
		node		*left;
		node		*right;
	}

	node				m_root;
	node				m_null;
	size_type			m_size;
	allocator_type		m_alloc;
};

}

#endif
