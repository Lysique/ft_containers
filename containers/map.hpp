/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 11:05:49 by tamighi           #+#    #+#             */
/*   Updated: 2022/04/11 15:52:48 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MAP_HPP
#define FT_MAP_HPP

#include "pair.hpp"
#include "reverse_iterator.hpp"

namespace ft
{

template<class Pointer>
class map_const_iterator
{
	typedef typename ft::iterator_traits<Pointer>::pointer				pointer;
	typedef typename ft::iterator_traits<Pointer>::value_type			node;
	typedef typename node::value_type									value_type;
	typedef typename ft::iterator_traits<Pointer>::difference_type		difference_type;
	typedef typename ft::iterator_traits<Pointer>::iterator_category	iterator_category;
	typedef typename ft::iterator_traits<Pointer>::reference			reference;

public:

	map_const_iterator(void)
		: m_ptr(0)
	{
	}

	explicit map_const_iterator(Pointer ptr)
		: m_ptr(ptr)
	{
	}

	/*   REFERENCES OPERATOR  */
	value_type	operator*(void)
	{
		return (m_ptr->val);
	}

	/*   OPERATOR=  */
	map_const_iterator&	operator=(const map_const_iterator& other)
	{
		this->m_ptr = other.m_ptr;
		return (*this);
	}

	~map_const_iterator(void)
	{
	}

protected:

	Pointer	m_ptr;
};

template<class Pointer>
class map_iterator : public map_const_iterator<Pointer>
{
public:

	map_iterator(void)
	{
		this->m_ptr = 0;
	}

	map_iterator(Pointer ptr)
	{
		this->m_ptr = ptr;
	}
};

template<class Key, class T>
struct mapNode
{
	typedef ft::pair<Key, T>	value_type;

	mapNode(const value_type& value)
		: color(0), val(value), parent(NULL), left(NULL), right(NULL)
	{
	}

	bool		color;
	value_type	val;
	mapNode		*parent;
	mapNode		*left;
	mapNode		*right;
};

template<class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
class map
{
	/*   MEMBER TYPES  */
private:

	typedef mapNode<Key, T>			node;
	typedef node*					nodePtr;
	typedef std::allocator<node>	node_allocator_type;

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
	typedef typename Alloc::pointer					pointer;
	typedef typename Alloc::const_pointer			const_pointer;
	typedef	map_iterator<nodePtr>					iterator;
	typedef map_const_iterator<const nodePtr>		const_iterator;
	typedef ft::reverse_iterator<iterator>			reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

	/*   MEMBER FUNCTIONS  */
public:

	/*   CONSTRUCTORS  */
	map(const allocator_type& alloc = allocator_type())
		: m_node_alloc(), m_alloc(alloc), m_size(0), m_root(NULL), m_comp()
	{
	}

	explicit map(const compare_type& comp, const allocator_type& alloc = allocator_type())
		: m_node_alloc(), m_alloc(alloc), m_size(0), m_root(NULL), m_comp()
	{
		(void)comp;
	}

	template<class Init>
	map(Init first, Init last, const compare_type& comp = compare_type(),
		const allocator_type& alloc = allocator_type())
		: m_node_alloc(), m_alloc(alloc), m_size(0), m_root(NULL), m_comp()
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

	/*   ACCESSOR  */
	T&	operator[](const Key& k)
	{
		return (priv_search(k));
	}
	/*   ITERATORS  */
	iterator	begin(void)
	{
		return (iterator(m_root));
	}

	/*   MODIFIERS  */

	ft::pair<iterator, bool>	insert(const value_type& value)
	{
		nodePtr	newNode = priv_newNode(value);
		if (m_root == NULL)
			m_root = newNode;
		else
			this->priv_insert(newNode, m_root);
		return (ft::make_pair<iterator, bool>(iterator(newNode), true));
	}

private:

	T&	priv_search(const Key& k)
	{
		nodePtr	it = m_root;
	
		while (it)
		{
			if (it->val.first == k)
				return (it);
			else if (comp(it->val.first, k))
				it = it->left;
			else
				it = it->right;
		}
		return (it);
	}

	void	priv_insert(nodePtr new_node, nodePtr it)
	{
		if (m_comp(new_node->val.first, it->val.first))
		{
			if (it->left == NULL)
			{
				it->left = new_node;
				new_node->parent = it;
			}
			else
				priv_insert(new_node, it->left);
		}
		else
		{
			if (it->right == NULL)
			{
				it->right = new_node;
				new_node->parent = it;
			}
			else
				priv_insert(new_node, it->right);
		}
	}

	node*	priv_newNode(const value_type& val)
	{
		node*	new_node = m_node_alloc.allocate(1);
		m_node_alloc.construct(new_node, node(val));
		new_node->left = NULL;
		new_node->right = NULL;
		return (new_node);
	}

	/*   MEMBER ATTRIBUTES  */
private:

	node_allocator_type	m_node_alloc;
	allocator_type		m_alloc;
	size_type			m_size;
	nodePtr				m_root;
	compare_type		m_comp;

	/*   CLASS  */
public:

	class value_compare
	{

	protected:
		value_compare(Compare c)
			: comp(c)
		{
		}

	private:
		Compare comp;
	};
};

}

#endif
