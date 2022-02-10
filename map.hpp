#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include <utility>
# include <functional>

namespace ft {

	template < class T >
		struct node
		{
			typedef T									value_type;

			node() : father(NULL), left(NULL), right(NULL) {}
			node(value_type	& val) : data(val), parent(NULL), left(NULL), right(NULL) {}

			node<value_type> *	parent;
			node<value_type> *	left;
			node<value_type> *	right;
			value_type 			data;	
		};

	template < class Key , class T , class Compare = std::less<Key> , class Alloc = std::allocator<std::pair<const Key, T> > >
		class map
		{
			public:

				typedef Key											key_type;
				typedef T											mapped_type;
				typedef typename std::pair<const Key, T>			value_type;
				typedef Compare										key_compare;
				typedef Alloc										allocator_type;
				typedef	typename allocator_type::reference			reference;
				typedef typename allocator_type::const_reference	const_reference;
				typedef typename allocator_type::pointer			pointer;
				typedef typename allocator_type::const_pointer		const_pointer;
				
			private:
				typedef typename ft::node<value_type>					node_type;
				typedef	typename allocator_type::template rebind<node_type>::other	node_allocator_type; //use: node_allocator_type(_alloc).allocate/destroy/construct......

			public:

				explicit map(const key_compare & comp = key_compare(), const allocator_type & alloc = allocator_type()) : _alloc(alloc), _comp(comp), _node(NULL), _size(0) {}

				template < class InputIterator >
					map(InputIterator first, InputIterator last, const key_compare & comp = key_compare(), const allocator_type & alloc = allocator_type()) : _alloc(alloc), _comp(comp), _size(0)
				{
				}

				map (const map & x)
				{
				}

				bool	insert(const value_type & val) //return value must be pair<iterator, bool> with iterator pointing to inserted element or equivalent
				{
					node_type *	tmp;
					
					tmp = node_allocator_type(_alloc).allocate(1);
					node_allocator_type(_alloc).construct(tmp, node_type(val));
					return true; //recorremos recursive, si es less a izq si no drch, cuando null ta guchi
				}

			private:

				Alloc		_alloc;
				Compare		_comp;
				node_type *	_node;	
				size_t		_size;

		};
	
}

#endif
