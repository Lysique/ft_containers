/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 11:05:49 by tamighi           #+#    #+#             */
/*   Updated: 2022/04/12 13:24:29 by tamighi          ###   ########.fr       */
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
	typedef typename ft::iterator_traits<Pointer>::value_type			value_type;
	typedef typename ft::iterator_traits<Pointer>::difference_type		difference_type;
	typedef typename ft::iterator_traits<Pointer>::iterator_category	iterator_category;
	typedef typename ft::iterator_traits<Pointer>::reference			reference;

	typedef typename value_type::value_type								value_pair;
	typedef value_pair*													pointer_pair;
	typedef value_pair&													reference_pair;

public:

	map_const_iterator(void)
		: m_ptr(0)
	{
	}

	explicit map_const_iterator(Pointer ptr)
		: m_ptr(ptr)
	{
	}

	~map_const_iterator(void)
	{
	}

	/*   REFERENCES OPERATOR  */
	value_pair	operator*(void)
	{
		return (m_ptr->val);
	}

	const pointer_pair	operator->(void) const
	{
		return (&(m_ptr->val));
	}
	
	/*   INCREMENT/DECREMENT  */

	map_const_iterator&	operator++(void)
	{
		if (m_ptr->right)
		{
			m_ptr = m_ptr->right;
			while (m_ptr->left != NULL)
				m_ptr = m_ptr->left;
		}
		else
		{
			while (m_ptr->parent->right == m_ptr)
				m_ptr = m_ptr->parent;
			m_ptr = m_ptr->parent;
		}
		return (*this);
	}

	map_const_iterator&	operator++(int)
	{
		pointer	tmp = m_ptr;
		++*this;
		return (map_const_iterator(tmp));
	}

	map_const_iterator&	operator--(void)
	{
		if (m_ptr->left)
		{
			m_ptr = m_ptr->left;
			while (m_ptr->right != NULL)
				m_ptr = m_ptr->right;
		}
		else
		{
			while (m_ptr->parent->left == m_ptr)
				m_ptr = m_ptr->parent;
			m_ptr = m_ptr->parent;
		}
		return (*this);
	}

	map_const_iterator&	operator--(int)
	{
		pointer	tmp = m_ptr;
		--*this;
		return (map_const_iterator(tmp));
	}

	/*   OPERATOR=  */
	map_const_iterator&	operator=(const map_const_iterator& other)
	{
		this->m_ptr = other.m_ptr;
		return (*this);
	}

	/*   COMPARISON OPERATORS  */
	bool	operator==(const map_const_iterator& r) const
	{
		return (this->m_ptr == r.m_ptr);
	}

	bool	operator!=(const map_const_iterator& r) const
	{
		return (this->m_ptr != r.m_ptr);
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
		: color(1), val(value), parent(NULL), left(NULL), right(NULL)
	{
	}

	bool				color;
	const value_type&	val;
	mapNode				*parent;
	mapNode				*left;
	mapNode				*right;
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
		: m_node_alloc(), m_alloc(alloc), m_size(0), m_comp()
		  , m_nil(priv_newNode()), m_begin(m_nil), m_last(m_nil), m_root(m_nil)
	{
	}

	explicit map(const compare_type& comp, const allocator_type& alloc = allocator_type())
		: m_node_alloc(), m_alloc(alloc), m_size(0), m_comp(comp)
		  , m_nil(priv_newNode()), m_begin(m_nil), m_last(m_nil), m_root(m_nil)
	{
	}

	template<class Init>
	map(Init first, Init last, const compare_type& comp = compare_type(),
		const allocator_type& alloc = allocator_type())
		: m_node_alloc(), m_alloc(alloc), m_size(0), m_comp(comp)
		  , m_nil(priv_newNode()), m_begin(m_nil), m_last(m_nil), m_root(m_nil)
	{
		(void)first;
		(void)last;
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
		(void)k;
		return (m_root->value);
	}
	/*   ITERATORS  */
	iterator	begin(void)
	{
		return (iterator(m_begin));
	}

	iterator	end(void)
	{
		return (iterator(m_nil));
	}

	/*   MODIFIERS  */

	ft::pair<iterator, bool>	insert(const value_type& value)
	{
		nodePtr	new_node = this->priv_newNode(value);
		if (m_root == m_nil)
		{
			new_node->color = 0;
			m_root = new_node;
			m_begin = new_node;
			m_last = new_node;
			m_last->right = m_nil;
			return (ft::make_pair<iterator, bool>(iterator(new_node), true));
		}
		ft::pair<iterator, bool>	mp = this->priv_insert(new_node, m_root);
		if (mp.second == true)
			this->priv_balance(new_node);
		return (mp);
	}

private:

	void	priv_balance(nodePtr n)
	{
		return ;
		while (n->parent->color == 1)
		{
			nodePtr	gp = n->parent->parent;
			if (n->parent == gp->left)
			{
				if (gp->right->color == 1)
				{
					gp->left->color = 0;
					gp->right->color = 0;
					gp->color = 1;
					n = gp;
				}
				else if (n == n->parent->right)
				{
					n = n->parent;
					//priv_left_rotate(n); // idk for order
				}
				else
				{
					n->parent->color = 0;
					gp->color = 1;
					//priv_right_rotate(gp);
				}
			}
			else
			{
				if (gp->left->color == 1)
				{
					gp->color = 0;
					gp->right->color = 1;
					gp->left->color = 1;
					n = gp;
				}
				else if (n->parent->left == n)
				{
					n = n->parent;
					//priv_right_rotate(n);
				}
				n->parent->color = 0;
				gp->color = 1;
				m_root->color = 0;
			}
		}
		if (n->parent->color == 0)
			return ;
	}

	ft::pair<iterator, bool>	priv_insert(nodePtr new_node, nodePtr it)
	{
		if (new_node->val.first == it->val.first)
		{
			this->m_node_alloc.deallocate(new_node, 1);
			return (ft::make_pair<iterator, bool>(iterator(it), false));
		}
		else if (m_comp(new_node->val.first, it->val.first))
		{
			if (it->left == NULL)
			{
				it->left = new_node;
				new_node->parent = it;
				if (this->m_comp(new_node->val.first, this->m_begin->val.first))
					this->m_begin = new_node;
				return (ft::make_pair<iterator, bool>(iterator(new_node), true));
			}
			else
				return (this->priv_insert(new_node, it->left));
		}
		else
		{
			if (it->right == NULL || it->right == m_nil)
			{
				it->right = new_node;
				new_node->parent = it;
				if (m_comp(this->m_last->val.first, new_node->val.first))
				{
					this->m_last = new_node;
					new_node->right = m_nil;
				}
				return (ft::make_pair<iterator, bool>(iterator(new_node), true));
			}
			else
				return (this->priv_insert(new_node, it->right));
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

	node*	priv_newNode(void)
	{
		node*	new_node = m_node_alloc.allocate(1);
		new_node->left = NULL;
		new_node->right = NULL;
		return (new_node);
	}

	/*   MEMBER ATTRIBUTES  */
private:

	node_allocator_type	m_node_alloc;
	allocator_type		m_alloc;
	size_type			m_size;
	compare_type		m_comp;

	nodePtr				m_nil;
	nodePtr				m_begin;
	nodePtr				m_last;
	nodePtr				m_root;

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
