/* ************************************************************************** */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamighi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 10:30:27 by tamighi           #+#    #+#             */
/*   Updated: 2022/04/14 14:49:08 by tamighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MAP_HPP
#define FT_MAP_HPP

#include "pair.hpp"
#include "reverse_iterator.hpp"
#include "equal.hpp"
#include "lexicographical_compare.hpp"
#include "iterator_traits.hpp"

namespace ft
{

template<class T>
struct node
{
	typedef T					value_type;
	typedef std::allocator<T>	allocator_type;

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

template<class T>
class map_const_iterator
{
	/*   TYPE MEMBERS  */

public:

	typedef T										value_type;
	typedef const T*								pointer;
	typedef const T&								reference;
	typedef ptrdiff_t								difference_type;
	typedef std::random_access_iterator_tag			iterator_category;

private:
	typedef node<T>			node_type;
	typedef node_type*		node_pointer;
	typedef node_type&		node_reference;
	typedef const node_type*	node_const_pointer;

	/*   FUNCTIONS MEMBERS  */

public:

	/*   CONSTRUCTORS / DESTRUCTOR  */
	map_const_iterator(void)
		: m_ptr(0)
	{
	}

	explicit map_const_iterator(node_pointer ptr)
		: m_ptr(ptr)
	{
	}

	~map_const_iterator(void)
	{
	}

	/*   REFERENCES OPERATOR  */
	reference	operator*(void) const
	{
		return (*m_ptr->val);
	}

	pointer	operator->(void) const
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

	map_const_iterator	operator++(int)
	{
		node_pointer	tmp = m_ptr;
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

	map_const_iterator	operator--(int)
	{
		node_pointer	tmp = m_ptr;
		--*this;
		return (map_const_iterator(tmp));
	}

	/*   OPERATOR=  */
	map_const_iterator	operator=(node_pointer ptr)
	{
		this->m_ptr = ptr;
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

	node_pointer	m_ptr;
};

template<class T>
class map_iterator : public map_const_iterator<T>
{

public:

	typedef T										value_type;
	typedef T*										pointer;
	typedef ptrdiff_t								difference_type;
	typedef T&										reference;
	typedef std::random_access_iterator_tag			iterator_category;
	
	typedef node<T>		node_type;
	typedef node_type*	node_pointer;

public:

	map_iterator(void)
	{
		this->m_ptr = 0;
	}

	explicit map_iterator(node_pointer ptr)
		: map_const_iterator<T>(ptr)
	{
	}

	/*   REFERENCES OPERATOR  */
	reference	operator*(void)
	{
		return (*this->m_ptr->val);
	}

	pointer	operator->(void) const
	{
		return (this->m_ptr->val);
	}

	/*   INCREMENT / DECREMENT  */
	map_iterator&	operator++(void)
	{
		if (this->m_ptr->right->is_leaf == false)
		{
			this->m_ptr = this->m_ptr->right;
			while (this->m_ptr->left->is_leaf == false)
				this->m_ptr = this->m_ptr->left;
		}
		else
		{
			while (this->m_ptr->parent->right == this->m_ptr)
				this->m_ptr = this->m_ptr->parent;
			this->m_ptr = this->m_ptr->parent;
		}
		return (*this);
	}

	map_iterator	operator++(int)
	{
		node_pointer	tmp = this->m_ptr;
		++*this;
		return (map_iterator(tmp));
	}

	map_iterator&	operator--(void)
	{
		if (this->m_ptr->left->is_leaf == false)
		{
			this->m_ptr = this->m_ptr->left;
			while (this->m_ptr->right->is_leaf == false)
				this->m_ptr = this->m_ptr->right;
		}
		else
		{
			while (this->m_ptr->parent->left == this->m_ptr)
				this->m_ptr = this->m_ptr->parent;
			this->m_ptr = this->m_ptr->parent;
		}
		return (*this);
	}

	map_iterator	operator--(int)
	{
		node_pointer	tmp = this->m_ptr;
		--*this;
		return (map_iterator(tmp));
	}

};


template<class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
class map
{
	/*   MEMBER TYPES  */

public:
	class value_compare;

	typedef Key										key_type;
	typedef T										mapped_type;

	typedef ft::pair<const Key, T>					value_type;
	typedef size_t									size_type;
	typedef ptrdiff_t								difference_type;
	typedef Compare									key_compare;
	typedef std::random_access_iterator_tag			iterator_category;
	typedef Alloc									allocator_type;
	typedef value_type&								reference;
	typedef const value_type&						const_reference;
	typedef typename Alloc::pointer					pointer;
	typedef typename Alloc::const_pointer			const_pointer;

	typedef	map_iterator<value_type>				iterator;
	typedef map_const_iterator<value_type>			const_iterator;
	typedef ft::reverse_iterator<iterator>			reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

private:
	typedef node<value_type>		node_type;
	typedef node_type*			node_pointer;
	typedef std::allocator<node_type>	node_allocator_type;

	/*   MEMBER FUNCTIONS  */
public:

	/*   CONSTRUCTORS / DESTRUCTOR  */
	map(const allocator_type& alloc = allocator_type())
		: m_node_alloc(), m_alloc(alloc), m_size(0), m_comp(),
		m_leaf(priv_newNode()), m_end(priv_newNode()), m_begin(m_end), m_root(m_end)
	{
		m_leaf->is_leaf = true;
		m_end->right = m_leaf;
		m_end->left = m_leaf;
	}

	explicit map(const key_compare& comp, const allocator_type& alloc = allocator_type())
		: m_node_alloc(), m_alloc(alloc), m_size(0), m_comp(comp),
		m_leaf(priv_newNode()), m_end(priv_newNode()), m_begin(m_end), m_root(m_end)
	{
		m_leaf->is_leaf = true;
		m_end->right = m_leaf;
		m_end->left = m_leaf;
	}

	template<class Init>
	map(Init first, Init last, const key_compare& comp = key_compare(),
		const allocator_type& alloc = allocator_type())
		: m_node_alloc(), m_alloc(alloc), m_size(0), m_comp(comp),
		m_leaf(priv_newNode()), m_end(priv_newNode()), m_begin(m_end), m_root(m_end)
	{
		m_leaf->is_leaf = true;
		m_end->right = m_leaf;
		m_end->left = m_leaf;
		insert(first, last);
	}

	map(const map& other)
		: m_node_alloc(), m_alloc(), m_size(0), m_comp(),
		m_leaf(priv_newNode()), m_end(priv_newNode()), m_begin(m_end), m_root(m_end)
	{
		m_leaf->is_leaf = true;
		m_end->right = m_leaf;
		m_end->left = m_leaf;
		*this = other;
	}

	~map(void)
	{
		//priv_print_tree(m_root, "", true);
		priv_tree_destroy(m_root);
		m_node_alloc.deallocate(m_leaf, 1);
		m_node_alloc.deallocate(m_end, 1);
	}

	/*   OPERATOR= / GET_ALLOC  */
	map&	operator=(const map& other)
	{
		erase(begin(), end());
		insert(other.begin(), other.end());
		return (*this);
	}

	allocator_type	get_allocator(void) const
	{
		return (m_alloc);
	}

	/*   ELEMENT ACCESS  */
	mapped_type&	at(const key_type& k)
	{
		node_pointer	n = priv_search_key(k);
		if (n == m_leaf || n == m_end)
			throw OutOfRangeException();
		return (n->val->second);
	}

	const mapped_type&	at(const key_type& k) const
	{
		node_pointer	n = priv_search_key(k);
		if (n == m_leaf || n == m_end)
			throw OutOfRangeException();
		return (n->val->second);
	}

	mapped_type&	operator[](const key_type& k)
	{
		node_pointer				n = priv_search_key(k);
		if (n == m_leaf || n == m_end)
		{
			insert(ft::make_pair<Key, T>(k, T()));
			n = priv_search_key(k);
		}
		return (n->val->second);
	}

	/*   ITERATORS  */
	iterator	begin(void)
	{
		return (iterator(m_begin));
	}
	
	const_iterator	begin(void) const
	{
		return (const_iterator(m_begin));
	}

	reverse_iterator	rbegin(void)
	{
		return (reverse_iterator(iterator(m_end)));
	}

	const_reverse_iterator	rbegin(void) const
	{
		return (const_reverse_iterator(const_iterator(m_end)));
	}

	iterator	end(void)
	{
		return (iterator(m_end));
	}

	const_iterator	end(void) const
	{
		return (const_iterator(m_end));
	}

	reverse_iterator	rend(void)
	{
		return (reverse_iterator(iterator(m_begin)));
	}

	const_reverse_iterator	rend(void) const
	{
		return (const_reverse_iterator(const_iterator(m_begin)));
	}

	/*   CAPACITY  */
	bool	empty(void) const
	{
		return (m_size == 0);
	}

	size_type	size(void) const
	{
		return (m_size);
	}

	size_type	max_size(void) const
	{
		return (m_node_alloc.max_size());
	}

	/*   MODIFIERS  */
	void	clear(void)
	{
		priv_tree_destroy(m_root);
		m_size = 0;
	}

	ft::pair<iterator, bool>	insert(const value_type& value)
	{
		node_pointer	new_node = priv_newNode(value);
		if (m_size == 0)
		{
			new_node->right = m_end;
			m_root = new_node;
			m_begin = new_node;
			m_end->parent = new_node;
			m_root->color = 0;
			++m_size;
			return (ft::make_pair<iterator, bool>(iterator(new_node), true));
		}
		ft::pair<iterator, bool>	mp = priv_insert(new_node, m_root);
		if (mp.second == true)
		{
			++m_size;
			priv_insert_balance(new_node);
		}
		return (mp);
	}

	iterator	insert(iterator hint, const value_type& value)
	{
		node_pointer	new_node = priv_newNode(value);
		if (m_size == 0)
		{
			new_node->right = m_end;
			m_root = new_node;
			m_begin = new_node;
			m_end->parent = new_node;
			m_root->color = 0;
			++m_size;
			return (iterator(new_node));
		}
		ft::pair<iterator, bool>	mp;
		if (hint == end())
			--hint;
		mp = priv_insert_hint(new_node, priv_search_key(hint->first));
		if (mp.second == true)
		{
			++m_size;
			priv_insert_balance(new_node);
		}
		return (mp.first);
	}

	template<class Init>
	void	insert(Init first, Init last)
	{
		for (; first != last; ++first)
			insert(*first);
	}

	void	erase(iterator pos)
	{
		priv_remove(priv_search_key(pos->first));
	}

	void	erase(iterator first, iterator last)
	{
		for (iterator tmp = first; first != last;)
		{
			++tmp;
			erase(iterator(priv_search_key(first->first)));
			first = tmp;
		}
	}

	size_type	erase(const Key& k)
	{
		node_pointer	n = priv_search_key(k);
		if (n != m_leaf && n != m_end)
		{
			priv_remove(n);
			return (1);
		}
		return (0);
	}

	void	swap(map& other)
	{
		map					m;
		node_pointer		leaf = m.m_leaf;
		node_pointer		end = m.m_end;
		node_allocator_type	node_alloc = m.m_node_alloc;

		priv_give_member(*this, m);
		priv_give_member(other, *this);
		priv_give_member(m, other);
		m.m_root = leaf;
		m.m_end = end;
		m.m_leaf = leaf;
		m.m_node_alloc = node_alloc;
	}

	/*   LOOKUP  */
	size_type	count(const Key& k) const
	{
		node_pointer	n = priv_search_key(k);
		if (n == m_leaf || n == m_end)
		   return (0);
		return (1);
	}	

	iterator	find(const Key& k)
	{
		node_pointer	n = priv_search_key(k);
		if (n == m_leaf || n == m_end)
			return (iterator(m_end));
		return (iterator(n));
	}

	const_iterator	find(const Key& k) const
	{
		node_pointer	n = priv_search_key(k);
		if (n == m_leaf || n == m_end)
			return (iterator(m_end));
		return (iterator(n));
	}

	ft::pair<iterator, iterator>	equal_range(const Key& k)
	{
		return (ft::make_pair<iterator, iterator>(lower_bound(k), upper_bound(k)));
	}

	ft::pair<const_iterator, const_iterator>	equal_range(const Key& k) const
	{
		return (ft::make_pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k)));
	}

	iterator	lower_bound(const Key& k)
	{
		iterator it = begin();
		for (; it != end() && m_comp(it->first, k); ++it)
			;
		return (it);
	}

	const_iterator	lower_bound(const Key& k) const
	{
		const_iterator it = begin();
		for (; it != end() && m_comp(it->first, k); ++it)
			;
		return (it);
	}

	iterator	upper_bound(const Key& k)
	{
		iterator it = begin();
		for (; it != end() && !m_comp(k, it->first); ++it)
			;
		return (it);
	}

	const_iterator	upper_bound(const Key& k) const
	{
		const_iterator it = begin();
		for (; it != end() && !m_comp(k, it->first); ++it)
			;
		return (it);
	}

	/*   OBSERVERS  */
	key_compare	key_comp(void) const
	{
		return (m_comp);
	}

	value_compare	value_comp(void) const
	{
		return (value_compare(m_comp));
	}

private:

	/*   SEARCH  */
	node_pointer	priv_search_key(const key_type& k) const
	{
		node_pointer	ptr = m_root;
		while (ptr != m_leaf && ptr != m_end)
		{
			if (m_comp(k, ptr->val->first))
				ptr = ptr->left;
			else if (m_comp(ptr->val->first, k))
				ptr = ptr->right;
			else
				break;
		}
		return (ptr);
	}

	node_pointer	priv_min(node_pointer p)
	{
		while (p->left != m_leaf)
			p = p->left;
		return (p);
	}

	node_pointer	priv_max(node_pointer p)
	{
		while (p->right != m_leaf)
			p = p->right;
		return (p);
	}

	/*   INSERTION  */
	ft::pair<iterator, bool>	priv_insert_hint(node_pointer new_node, node_pointer hint)
	{
		if (hint == m_root)
			return (priv_insert(new_node, m_root));
		else if (m_comp(new_node->val->first, hint->val->first) && hint == hint->parent->left)
			return (priv_insert(new_node, hint));
		else if (m_comp(hint->val->first, new_node->val->first) && hint == hint->parent->right)
			return (priv_insert(new_node, hint));
		else
			return (priv_insert_hint(new_node, hint->parent));
	}

	ft::pair<iterator, bool>	priv_insert(node_pointer new_node, node_pointer it)
	{
		if (m_comp(new_node->val->first, it->val->first))
		{
			if (it->left->is_leaf)
			{
				it->left = new_node;
				new_node->parent = it;
				if (it == m_begin)
					m_begin = new_node;
				return (ft::make_pair<iterator, bool>(iterator(new_node), true));
			}
			return (priv_insert(new_node, it->left));
		}
		else if (m_comp(it->val->first, new_node->val->first))
		{
			if (it->right->is_leaf || it->right == m_end)
			{
				it->right = new_node;
				new_node->parent = it;
				if (it == m_end->parent)
				{
					m_end->parent = new_node;
					new_node->right = m_end;
				}
				return (ft::make_pair<iterator, bool>(iterator(new_node), true));
			}
			return (priv_insert(new_node, it->right));
		}
		else
		{
			m_node_alloc.destroy(new_node);
			m_node_alloc.deallocate(new_node, 1);
			return (ft::make_pair<iterator, bool>(iterator(it), false));
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

	/*   DELETION  */
	void	priv_remove(node_pointer z)
	{
		bool			original_color = z->color;
		node_pointer	y = z;
		node_pointer	x;

		if (z->left == m_leaf)
		{
			x = z->right;
			priv_transplant(z, z->right);
		}
		else if (z->right == m_leaf || z->right == m_end)
		{
			x = z->left;
			priv_transplant(z, z->left);
		}
		else
		{
			y = priv_min(z->right);
			original_color = y->color;
			x = y->right;
			if (y->parent == z)
				x->parent = y;
			else 
			{
				priv_transplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}
			priv_transplant(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}
		if (z == m_begin)
			m_begin = priv_min(m_root);
		if (z == m_end->parent)
		{
			m_end->parent = priv_max(m_root);
			priv_max(m_root)->right = m_end;
		}
		m_node_alloc.destroy(z);
		m_node_alloc.deallocate(z, 1);
		m_size--;
		if (original_color == 0)
			priv_remove_balance(x);
	}

	void	priv_remove_balance(node_pointer x)
	{
		node_pointer	s;

		while (x != m_root && x->color == 0)
		{
			if (x == x->parent->left)
			{
				s = x->parent->right;
				if (s->color == 1)
				{
					s->color = 0;
					x->parent->color = 1;
					priv_left_rotate(x->parent);
					s = x->parent->right;
				}
				if (s->left->color == 0 && s->right->color == 0)
				{
					s->color = 1;
					x = x->parent;
				}
				else
				{
					if (s->right->color == 0)
					{
						s->left->color = 0;
						s->color = 1;
						priv_right_rotate(s);
						s = x->parent->right;
					}
					s->color = x->parent->color;
					x->parent->color = 0;
					s->right->color = 0;
					priv_left_rotate(x->parent);
					x = m_root;
				}
			}
			else
			{
				s = x->parent->left;
				if (s->color == 1)
				{
					s->color = 0;
					x->parent->color = 1;
					priv_right_rotate(x->parent);
					s = x->parent->left;
				}
				if (s->right->color == 0 && s->right->color == 0)
				{
					s->color = 1;
					x = x->parent;
				}
				else
				{
					if (s->left->color == 0)
					{
						s->right->color = 0;
						s->color = 1;
						priv_left_rotate(s);
						s = x->parent->left;
					}
					s->color = x->parent->color;
					x->parent->color = 0;
					s->left->color = 0;
					priv_right_rotate(x->parent);
					x = m_root;
				}
			}
		}
		x->color = 0;
	}

	/*   ROTATIONS  */
	void	priv_left_rotate(node_pointer n)
	{
		node_pointer r = n->right;
	
		n->right = r->left;
		if (r->left->is_leaf == false)
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

	void	priv_transplant(node_pointer u, node_pointer v)
	{
		if (u->parent == NULL)
			m_root = v;
		else if (u == u->parent->left)
			u->parent->left = v;
		else
			u->parent->right = v;
		v->parent = u->parent;
	}

	/*   DESTROY  */
	void	priv_tree_destroy(node_pointer ptr)
	{
		if (ptr->is_leaf == false && ptr != m_end)
		{
			priv_tree_destroy(ptr->right);
			priv_tree_destroy(ptr->left);
			m_node_alloc.destroy(ptr);
			m_node_alloc.deallocate(ptr, 1);
		}
		m_root = m_end;
		m_begin = m_end;
	}

	void	priv_give_member(map& from, map& other)
	{
		other.m_node_alloc = from.m_node_alloc;
		other.m_alloc = from.m_alloc;
		other.m_size = from.m_size;
		other.m_comp = from.m_comp;
		other.m_leaf = from.m_leaf;
		other.m_end = from.m_end;
		other.m_begin = from.m_begin;
		other.m_root = from.m_root;
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

	node_pointer	priv_newNode(const value_type& val)
	{
		node_pointer	new_node = m_node_alloc.allocate(1);
		m_node_alloc.construct(new_node, val);
		new_node->left = m_leaf;
		new_node->right = m_leaf;
		return (new_node);
	}

	node_pointer	priv_newNode(void)
	{
		node_pointer	new_node = m_node_alloc.allocate(1);
		m_node_alloc.construct(new_node);
		return (new_node);
	}

	/*   MEMBER ATTRIBUTES  */

private:

	node_allocator_type			m_node_alloc;
	allocator_type				m_alloc;
	size_type					m_size;
	key_compare					m_comp;

	node_pointer				m_leaf;
	node_pointer				m_end;
	node_pointer				m_begin;
	node_pointer				m_root;

	/*   CLASS  */

private:

	class	OutOfRangeException : public std::out_of_range
	{
	public :
		OutOfRangeException()
			: std::out_of_range("Ft::map : Index out of bounds") {}
	};

public:

	class value_compare
	{

		friend class map;

	public:
		bool	operator()(const value_type& lhs, const value_type& rhs)
		{
			return (comp(lhs.first, rhs.first));
		}

	protected:
		value_compare(Compare c)
			: comp(c)
		{
		}

		Compare comp;
	};
};

	/*   NON_MEMBER FUNCTIONS  */
template<class Key, class T, class Compare, class Alloc>
bool	operator==(const map<Key, T, Compare, Alloc>& lhs,
					const map<Key, T, Compare, Alloc>& rhs)
{
	return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template<class Key, class T, class Compare, class Alloc>
bool	operator!=(const map<Key, T, Compare, Alloc>& lhs,
					const map<Key, T, Compare, Alloc>& rhs)
{
	return (!(lhs == rhs));
}

template<class Key, class T, class Compare, class Alloc>
bool	operator<(const map<Key, T, Compare, Alloc>& lhs,
					const map<Key, T, Compare, Alloc>& rhs)
{
	return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template<class Key, class T, class Compare, class Alloc>
bool	operator>(const map<Key, T, Compare, Alloc>& lhs,
					const map<Key, T, Compare, Alloc>& rhs)
{
	return (lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
}

template<class Key, class T, class Compare, class Alloc>
bool	operator>=(const map<Key, T, Compare, Alloc>& lhs,
					const map<Key, T, Compare, Alloc>& rhs)
{
	return (!(lhs < rhs));
}

template<class Key, class T, class Compare, class Alloc>
bool	operator<=(const map<Key, T, Compare, Alloc>& lhs,
					const map<Key, T, Compare, Alloc>& rhs)
{
	return (!(lhs > rhs));
}

template<class Key, class T, class Compare, class Alloc>
void	swap(const map<Key, T, Compare, Alloc>& lhs,
			const map<Key, T, Compare, Alloc>& rhs)
{
	lhs.swap(rhs);
}

}
 #endif
