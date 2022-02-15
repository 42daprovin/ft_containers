#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include <utility>
# include <functional>
# include <iostream>
# include "map_iterator.hpp"
# include "iterator_traits.hpp"
# include "reverse_iterator.hpp"
# include "algorithm.hpp"

namespace ft {

	template < class Key , class T , class Compare = std::less<Key> , class Alloc = std::allocator<ft::pair<const Key, T> > >
		class map
		{
			public:

				typedef Key													key_type;
				typedef T													mapped_type;
				typedef typename ft::pair<const Key, T>					value_type;
				typedef Compare												key_compare;
				typedef Alloc												allocator_type;
				typedef	typename allocator_type::reference					reference;
				typedef typename allocator_type::const_reference			const_reference;
				typedef typename allocator_type::pointer					pointer;
				typedef typename allocator_type::const_pointer				const_pointer;
				typedef	class ft::m_iterator<value_type>					iterator;
				typedef class ft::const_m_iterator<value_type>				const_iterator;
				typedef typename iterator_traits<iterator>::difference_type	difference_type;
				typedef	ft::reverse_iterator<iterator>						reverse_iterator;
				typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;
				typedef size_t												size_type;

				class value_compare
				{
					friend class map;

					protected:
						Compare	comp;
						value_compare (Compare c) : comp(c) {}

					public:
						typedef bool	result_type;
						typedef value_type	first_argument_type;
						typedef value_type	second_argument_type;

						bool	operator()(const value_type & x, const value_type & y)
						{
							return comp(x.first, y.first);
						}

				};
				
			private:
				typedef typename ft::node<value_type>					node_type;
				typedef	typename allocator_type::template rebind<node_type>::other	node_allocator_type; //use: node_allocator_type(_alloc).allocate/destroy/construct......

			public:

//......................................Constructors.................................................

				explicit map(const key_compare & comp = key_compare(), const allocator_type & alloc = allocator_type()) : _alloc(alloc), _comp(comp), _node(NULL), _size(0)
			{ 
				_hipo_end = node_allocator_type(_alloc).allocate(1);
				node_allocator_type(_alloc).construct(_hipo_end, ft::make_pair(key_type(), mapped_type())); 
			}

				template < class InputIterator >
					map(InputIterator first, InputIterator last, const key_compare & comp = key_compare(), const allocator_type & alloc = allocator_type()) : _alloc(alloc), _comp(comp), _size(0)
				{
				}

				map (const map & x)
				{
				}

				~map(void)
				{
					clear();
					node_allocator_type(_alloc).destroy(_hipo_end);
					node_allocator_type(_alloc).deallocate(_hipo_end, 1);
				}

//........................................Operator =..................................................

				map &	operator=(const map & x)
				{
					int				x_size = x.size();
					const_iterator		first = x.begin();

					clear();
					for (size_t i = 0 ; i < (x_size / 2) ; i++)
						++first;
					insert(*first);
					insert(x.begin(), x.end());

					return *this;
				}

//........................................Capacity.....................................................

				size_type	size(void) const { return _size ; }
				size_type	max_size(void) const { return node_allocator_type(_alloc).max_size() ; }
				bool		empty(void) const { return _size == 0 ; }

//.........................................Modifiers...................................................

				void	erase(iterator position)
				{
					node_type *		tmp;
					node_type *		next;

					if (position == end())
						return ;
					
					if (position.base()->right == NULL && position.base()->left == NULL) //if node has no child
					{
						if (_comp(position->first, position.base()->parent->data.first) || position.base() == _node)
							position.base()->parent->left = NULL;
						else
							position.base()->parent->right = NULL;

						if (position.base() == _node)
							_node = NULL;

						tmp = position.base();
						node_allocator_type(_alloc).destroy(tmp);
						node_allocator_type(_alloc).deallocate(tmp, 1);
						tmp = NULL;
						_size--;
					}
					else if (position.base()->right == NULL) //if node has only left child
					{
						next = position.base()->left;

						if (_comp(position->first, position.base()->parent->data.first) || position.base() == _node)
							position.base()->parent->left = next;
						else
							position.base()->parent->right = next;

						if (position.base() == _node)
							_node = next;

						next->parent = position.base()->parent;

						tmp = position.base();
						node_allocator_type(_alloc).destroy(tmp);
						node_allocator_type(_alloc).deallocate(tmp, 1);
						tmp = NULL;
						_size--;
					}
					else if (position.base()->left == NULL) //if node has only right child
					{
						next = position.base()->right;

						if (_comp(position->first, position.base()->parent->data.first) || position.base() == _node)
							position.base()->parent->left = next;
						else
							position.base()->parent->right = next;

						if (position.base() == _node)
							_node = next;

						next->parent = position.base()->parent;

						tmp = position.base();
						node_allocator_type(_alloc).destroy(tmp);
						node_allocator_type(_alloc).deallocate(tmp, 1);
						tmp = NULL;
						_size--;
					}
					else //if node has two childs
					{
						next = ft::most_left(position.base()->right); //next = to the smallest element at his right

						if (_comp(position->first, position.base()->parent->data.first) || position.base() == _node)
							position.base()->parent->left = next;
						else
							position.base()->parent->right = next;

						next->parent->left = next->right;
						if (next->right)
							next->right->parent = next->parent;

						next->parent = position.base()->parent;

						next->right = position.base()->right;
						position.base()->right->parent = next;

						next->left = position.base()->left;
						position.base()->left->parent = next;

						if (position.base() == _node)
							_node = next;

						tmp = position.base();
						node_allocator_type(_alloc).destroy(tmp);
						node_allocator_type(_alloc).deallocate(tmp, 1);
						tmp = NULL;
						_size--;
					}
				}

				size_type	erase(const key_type & k)
				{
					iterator	pos = find(k);

					if (pos == end())
						return 0;
					else
						erase(pos);
					return 1;
				}

				void	erase(iterator first, iterator last)
				{
					while (first != last)
						erase(first++);
				}

				ft::pair<iterator, bool>	insert(const value_type & val)
				{
					node_type *	tmp;
					ft::pair<iterator, bool>	ret;

					tmp = node_allocator_type(_alloc).allocate(1);
					node_allocator_type(_alloc).construct(tmp, val);

					if (_node == NULL)
					{
						_node = tmp;
						_node->parent = _hipo_end;
						_hipo_end->left = _node;
						_size++;
						return ft::make_pair(iterator(_node), false) ;
					}
					ret = insert_node(tmp, _node);
					if (ret.second)
						_size++;
					return ret;
				}

				iterator		insert(iterator position, const value_type & val)
				{
					iterator	tmp = position;
					++tmp;

					if (tmp.base() == _hipo_end)
						return insert(val).first;
					else if (position->first < val.first && val.first < tmp->first)
					{
						node_type * in_node;

						in_node = node_allocator_type(_alloc).allocate(1);
						node_allocator_type(_alloc).construct(in_node, val);
						_size++;
						return insert_node(in_node, position.base()).first;	
					}
					else
						return insert(val).first;

				}

				template < class InputIterator>
					void		insert(InputIterator first, InputIterator last)
					{
						for ( ; first != last; ++first)
							insert(*first);
					}

				void	clear()
				{
					if (_node == NULL)
						return ;
					node_type * tmp = NULL;
					_node = ft::most_left(_node);

					while (_node != _hipo_end)
					{
						if (_node->right == NULL)
						{
							tmp = _node;
							_node = _node->parent;
							if (_node->right == tmp)
								_node->right = NULL;
							if (_node->left == tmp)
								_node->left = NULL;
							node_allocator_type(_alloc).destroy(tmp);
							node_allocator_type(_alloc).deallocate(tmp, 1);
							tmp = NULL;
						}
						else
							_node = ft::most_left(_node->right);
					}
					_node = NULL;
					_size = 0;
				}

//........................................Operations...............................................

				iterator	find(const key_type & k)
				{
					iterator	first = begin();
					iterator	last = end();

					for ( ; first != last ; ++first)
					{
						if (first->first == k)
							return first;
					}
					return last;
				}

				const_iterator	find(const key_type & k) const
				{
					iterator	first = begin();
					iterator	last = end();

					for ( ; first != last ; ++first)
					{
						if (first->first == k)
							return first;
					}
					return last;
				}

//.........................................Observers................................................

				key_compare		key_comp() const { return _comp ; }

//.........................................Iterators................................................

				iterator	begin(void)
				{
					ft::node<value_type> * n = most_left(_node);
					iterator	it(n);
					return it;
				}

				const_iterator	begin(void) const
				{
					const ft::node<value_type> * n = most_left(_node);
					const_iterator	it(n);
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
					const ft::node<value_type> * n = most_right(_node);
					const_iterator	it(n);
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
					return  (*((this->insert(ft::make_pair(k,mapped_type()))).first)).second ;
				}

//....................................Insert aux-function...........................................

			private:

				ft::pair<iterator, bool>	insert_node(node_type * in_node, node_type * cmp_node)
				{
					if (in_node->data.first == cmp_node->data.first)
					{
						node_allocator_type(_alloc).destroy(in_node);
						node_allocator_type(_alloc).deallocate(in_node, 1);
						return ft::make_pair(iterator(cmp_node), false) ;
					}
					if (_comp(in_node->data.first, cmp_node->data.first))	
					{
						if (cmp_node->left)
							return insert_node(in_node, cmp_node->left);
						else
						{
							cmp_node->left = in_node;
							in_node->parent = cmp_node;
							return ft::make_pair(iterator(in_node), true) ;
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
							return ft::make_pair(iterator(in_node), true) ;
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
