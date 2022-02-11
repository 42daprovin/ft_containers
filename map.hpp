#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include <utility>
# include <functional>
# include <iostream>
# include "map_iterator.hpp"
# include "iterator_traits.hpp"
# include "reverse_iterator.hpp"

namespace ft {

	template < class Key , class T , class Compare = std::less<Key> , class Alloc = std::allocator<std::pair<const Key, T> > >
		class map
		{
			public:

				typedef Key													key_type;
				typedef T													mapped_type;
				typedef typename std::pair<const Key, T>					value_type;
				typedef Compare												key_compare;
				typedef Alloc												allocator_type;
				typedef	typename allocator_type::reference					reference;
				typedef typename allocator_type::const_reference			const_reference;
				typedef typename allocator_type::pointer					pointer;
				typedef typename allocator_type::const_pointer				const_pointer;
				typedef	class ft::m_iterator<value_type>					iterator;
				typedef class ft::m_iterator<const value_type>				const_iterator;
				typedef typename iterator_traits<iterator>::difference_type	difference_type;
				typedef	ft::reverse_iterator<iterator>						reverse_iterator;
				typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;
				typedef size_t												size_type;
				
			private:
				typedef typename ft::node<value_type>					node_type;
				typedef	typename allocator_type::template rebind<node_type>::other	node_allocator_type; //use: node_allocator_type(_alloc).allocate/destroy/construct......

			public:

				explicit map(const key_compare & comp = key_compare(), const allocator_type & alloc = allocator_type()) : _alloc(alloc), _comp(comp), _node(NULL), _size(0)
			{ 
				_hipo_end = node_allocator_type(_alloc).allocate(1);
				node_allocator_type(_alloc).construct(_hipo_end, std::make_pair(key_type(), mapped_type())); 
			}

				template < class InputIterator >
					map(InputIterator first, InputIterator last, const key_compare & comp = key_compare(), const allocator_type & alloc = allocator_type()) : _alloc(alloc), _comp(comp), _size(0)
				{
				}

				map (const map & x)
				{
				}

//........................................Capacity.....................................................

				size_type	size(void) const { return _size ; }
				size_type	max_size(void) const { return node_allocator_type(_alloc).max_size() ; }
				bool		empty(void) const { return _size == 0 ; }

//.........................................Modifiers...................................................

				std::pair<iterator, bool>	insert(const value_type & val)
				{
					node_type *	tmp;
					std::pair<iterator, bool>	ret;

					tmp = node_allocator_type(_alloc).allocate(1);
					node_allocator_type(_alloc).construct(tmp, val);

					if (_node == NULL)
					{
						_node = tmp;
						_node->parent = _hipo_end;
						_hipo_end->left = _node;
						_size++;
						return std::make_pair(iterator(_node), false) ;
					}
					ret = insert_node(tmp, _node);
					if (ret.second)
						_size++;
					return ret;
				}

				/* std::pair<iterator, bool>	insert(iterator position, const value_type & val) */
				/* { */
				/* 	iterator	tmp = position; */
				/* 	++tmp; */

				/* 	if (tmp == NULL) */

				/* 	if (_comp(position->first, )) */
				/* } */

//.........................................Iterators................................................

				iterator	begin(void)
				{
					ft::node<value_type> * n = most_left(_node);
					iterator	it(n);
					return it;
				}

				const_iterator	begin(void) const
				{
					ft::node<value_type> * n = most_left(_node);
					iterator	it(n);
					return it;
				}

				iterator	end(void)
				{
					ft::node<value_type> * n = most_right(_node);
					iterator	it(n);
					++it;
					return it;
				}

				const_iterator	end(void) const
				{
					ft::node<value_type> * n = most_right(_node);
					iterator	it(n);
					++it;
					return it;
				}

				reverse_iterator	rbegin(void)
				{
					ft::node<value_type> * n = most_left(_node);
					reverse_iterator	it(n);
					return it;
				}
				
				const_reverse_iterator	rbegin(void) const
				{
					ft::node<value_type> * n = most_left(_node);
					reverse_iterator	it(n);
					return it;
				}
				
				reverse_iterator	rend(void)
				{
					ft::node<value_type> * n = most_right(_node);
					iterator	it(n);
					++it;
					return it;
				}

				const_reverse_iterator	rend(void) const
				{
					ft::node<value_type> * n = most_right(_node);
					iterator	it(n);
					++it;
					return it;
				}

//....................................Element Access................................................

				mapped_type &	operator[](const key_type & k)
				{
					return  (*((this->insert(std::make_pair(k,mapped_type()))).first)).second ;
				}

//....................................Insert aux-function...........................................

			private:

				std::pair<iterator, bool>	insert_node(node_type * in_node, node_type * cmp_node)
				{
					if (in_node->data.first == cmp_node->data.first)
						return std::make_pair(iterator(cmp_node), false) ;
					if (_comp(in_node->data.first, cmp_node->data.first))	
					{
						if (cmp_node->left)
							return insert_node(in_node, cmp_node->left);
						else
						{
							cmp_node->left = in_node;
							in_node->parent = cmp_node;
							return std::make_pair(iterator(in_node), true) ;
						}
					}
					else
					{
						if (cmp_node->right)
							return insert_node(in_node, cmp_node->right);
						else
						{
							cmp_node->right = in_node;
							in_node->parent = cmp_node;
							return std::make_pair(iterator(in_node), true) ;
						}
					}
				}

			private:

				Alloc		_alloc;
				Compare		_comp;
				node_type *	_node;	
				node_type * _hipo_end;
				size_t		_size;

		};
	
}

#endif
