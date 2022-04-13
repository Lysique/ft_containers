/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 10:30:27 by tamighi           #+#    #+#             */
/*   Updated: 2022/04/13 15:45:23 by tamighi          ###   ########.fr       */
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
	/*   TYPE MEMBERS  */

public:
	typedef typename ft::iterator_traits<Pointer>::pointer				pointer;
	typedef typename ft::iterator_traits<Pointer>::value_type			value_type;
	typedef typename ft::iterator_traits<Pointer>::difference_type		difference_type;
	typedef typename ft::iterator_traits<Pointer>::iterator_category	iterator_category;
	typedef typename ft::iterator_traits<Pointer>::reference			reference;

private:
	typedef typename value_type::value_type								value_pair;
	typedef value_pair*													pointer_pair;
	typedef value_pair&													reference_pair;
	typedef const value_pair*											const_pointer_pair;

	/*   FUNCTIONS MEMBERS  */

public:

	/*   CONSTRUCTORS / DESTRUCTOR  */
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
		return (*m_ptr->val);
	}

	const_pointer_pair	operator->(void) const
	{
		return (m_ptr->val);
	}	

	/*   INCREMENT/DECREMENT  */
	map_const_iterator&	operator++(void)
	{
		if (m_ptr->right->is_leaf == false)
		{
			m_ptr = m_ptr->right;
			while (m_ptr->left->is_leaf == false)
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
		if (m_ptr->left->is_leaf == false)
		{
			m_ptr = m_ptr->left;
			while (m_ptr->right->is_leaf == false)
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


template<class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
class map
{
	/*   MEMBER TYPES  */

private:
	struct node;

	typedef node*					node_pointer;
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
	typedef	map_iterator<node_pointer>				iterator;
	typedef map_const_iterator<const node_pointer>	const_iterator;
	typedef ft::reverse_iterator<iterator>			reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

	/*   MEMBER FUNCTIONS  */
public:

	/*   CONSTRUCTORS / DESTRUCTOR  */
	map(const allocator_type& alloc = allocator_type())
		: m_node_alloc(), m_alloc(alloc), m_size(0), m_comp(),
		m_leaf(priv_newNode()), m_begin(m_leaf), m_end(priv_newNode()), m_root(m_leaf)
	{
		m_leaf->is_leaf = true;
		m_end->right = m_leaf;
		m_end->left = m_leaf;
	}

	explicit map(const compare_type& comp, const allocator_type& alloc = allocator_type())
		: m_node_alloc(), m_alloc(alloc), m_size(0), m_comp(comp),
		m_leaf(priv_newNode()), m_begin(m_leaf), m_end(priv_newNode()), m_root(m_leaf)
	{
		m_leaf->is_leaf = true;
		m_end->right = m_leaf;
		m_end->left = m_leaf;
	}

	template<class Init>
	map(Init first, Init last, const compare_type& comp = compare_type(),
		const allocator_type& alloc = allocator_type())
		: m_node_alloc(), m_alloc(alloc), m_size(0), m_comp(comp),
		m_leaf(priv_newNode()), m_begin(m_leaf), m_end(priv_newNode()), m_root(m_leaf)
	{
		m_leaf->is_leaf = true;
		m_end->right = m_leaf;
		m_end->left = m_leaf;
		(void)first;
		(void)last;
	}

	map(const map& other)
	{
		(void)other;
	}

	~map(void)
	{
		priv_print_tree(m_root, "", true);
		priv_tree_destroy(m_root);
		m_node_alloc.deallocate(m_leaf, 1);
		m_node_alloc.deallocate(m_end, 1);
	}

	/*   ITERATORS  */
	iterator	begin(void)
	{
		return (iterator(m_begin));
	}

	iterator	end(void)
	{
		return (iterator(m_end));
	}

	/*   MODIFIERS  */
	ft::pair<iterator, bool>	insert(const value_type& value)
	{
		node_pointer	new_node = priv_newNode(value);
		if (m_root == m_leaf)
		{
			new_node->right = m_end;
			m_end->parent = new_node;
			m_root = new_node;
			m_begin = new_node;
			m_root->color = 0;
			return (ft::make_pair<iterator, bool>(iterator(new_node), true));
		}
		ft::pair<iterator, bool>	mp = priv_insert(new_node, m_root);
		if (mp.second == true)
			priv_insert_balance(new_node);
		return (mp);
	}

private:
	ft::pair<iterator, bool>	priv_insert(node_pointer new_node, node_pointer it)
	{
		if (new_node->val->first == it->val->first)
		{
			m_node_alloc.destroy(new_node);
			m_node_alloc.deallocate(new_node, 1);
			return (ft::make_pair<iterator, bool>(iterator(it), false));
		}
		else if (m_comp(new_node->val->first, it->val->first))
		{
			if (it->left->is_leaf)
			{
				it->left = new_node;
				new_node->parent = it;
				if (m_comp(new_node->val->first, m_begin->val->first))
					m_begin = new_node;
				return (ft::make_pair<iterator, bool>(iterator(new_node), true));
			}
			return (priv_insert(new_node, it->left));
		}
		else
		{
			if (it->right->is_leaf || it->right == m_end)
			{
				it->right = new_node;
				new_node->parent = it;
				if (m_comp(m_end->parent->val->first, new_node->val->first))
				{
					m_end->parent = new_node;
					new_node->right = m_end;
				}
				return (ft::make_pair<iterator, bool>(iterator(new_node), true));
			}
			return (priv_insert(new_node, it->right));
		}
	}

	void	priv_insert_balance(node_pointer n)
	{
		while (n != m_root && n->parent->color == 1)
		{
			node_pointer	gp = n->parent->parent;
			if (n->parent == gp->left)
			{
				if (gp->right->color == 1)
				{
					gp->left->color = 0;
					gp->right->color = 0;
					gp->color = 1;
					n = gp;
				}
				else
				{
					if (n->parent->right == n)
					{
						n = n->parent;
						priv_left_rotate(n);
					}
					n->parent->color = 0;
					gp->color = 1;	
					priv_right_rotate(gp);
				}
			}
			else
			{
				if (gp->left->color == 1)
				{
					gp->color = 1;
					gp->right->color = 0;
					gp->left->color = 0;
					n = gp;
				}
				else
				{
					if (n->parent->left == n)
					{
						n = n->parent;
						priv_right_rotate(n);
					}
					n->parent->color = 0;
					gp->color = 1;
					priv_left_rotate(gp);
				}
			}
		}
		m_root->color = 0;
	}

	void	priv_left_rotate(node_pointer n)
	{
		node_pointer r = n->right;
	
		n->right = r->left;
		if (r->left->is_leaf == false && r->left != m_end)
			r->left->parent = n;
		r->parent = n->parent;
		if (n->parent == NULL)
			m_root = r;
		else if (n == n->parent->left)
			n->parent->left = r;
		else
			n->parent->right = r;
		r->left = n;
		n->parent = r;
	}

	void	priv_right_rotate(node_pointer n)
	{
		node_pointer l = n->left;
	
		n->left = l->right;
		if (l->right->is_leaf == false && l->right != m_end)
			l->right->parent = n;
		l->parent = n->parent;
		if (n->parent == NULL)
			m_root = l;
		else if (n == n->parent->right)
			n->parent->right = l;
		else
			n->parent->left = l;
		l->right = n;
		n->parent = l;
	}

	void	priv_tree_destroy(node_pointer ptr)
	{
		if (ptr->is_leaf == false && ptr != m_end)
		{
			priv_tree_destroy(ptr->right);
			priv_tree_destroy(ptr->left);
			m_node_alloc.destroy(ptr);
			m_node_alloc.deallocate(ptr, 1);
		}
	}

	void priv_print_tree(node_pointer root, std::string indent, bool last)
	{
		if (root != m_leaf && root != m_end)
		{
			std::cout<<indent;
			if (last)
			{
				std::cout<<"R----";
				indent += "     ";
			}
			else
			{
				std::cout<<"L----";
				indent += "|    ";
			}
			std::string sColor = root->color?"RED":"BLACK";
			std::cout<<root->val->first<<"("<<sColor<<")"<<std::endl;
			priv_print_tree(root->left, indent, false);
			priv_print_tree(root->right, indent, true);
		}
	}

	node*	priv_newNode(const value_type& val)
	{
		node*	new_node = m_node_alloc.allocate(1);
		m_node_alloc.construct(new_node, val);
		new_node->left = m_leaf;
		new_node->right = m_leaf;
		return (new_node);
	}

	node*	priv_newNode(void)
	{
		node*	new_node = m_node_alloc.allocate(1);
		m_node_alloc.construct(new_node);
		return (new_node);
	}

	/*   MEMBER ATTRIBUTES  */

private:

	node_allocator_type			m_node_alloc;
	allocator_type				m_alloc;
	size_type					m_size;
	compare_type				m_comp;

	node_pointer				m_leaf;
	node_pointer				m_begin;
	node_pointer				m_end;
	node_pointer				m_root;

	/*   CLASS  */

private:
	struct node
	{
		typedef value_type		value_type;
	
		node(const value_type& value)
			: color(1), is_leaf(false), parent(NULL), left(NULL), right(NULL), alloc()
		{
			val = alloc.allocate(1);
			alloc.construct(val, value);
		}
	
		node(void)
			: color(0), is_leaf(false), val(NULL), parent(NULL), left(NULL), right(NULL), alloc()
		{
		}

		~node(void)
		{
			alloc.destroy(val);
			alloc.deallocate(val, 1);
		}

		bool					color;
		bool					is_leaf;
		value_type				*val;
		node					*parent;
		node					*left;
		node					*right;
		allocator_type			alloc;
	};



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
