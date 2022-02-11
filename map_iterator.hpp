#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

# include <iostream>
# include <iterator>

namespace ft {

	template < class T >
		struct node
		{
			typedef T									value_type;

			node() : parent(NULL), left(NULL), right(NULL) {}
			node(const value_type & val) : parent(NULL), left(NULL), right(NULL), data(val) {}

			node<value_type> *	parent;
			node<value_type> *	left;
			node<value_type> *	right;
			value_type 			data;	
		};

	template < class T >
		ft::node<T> *	most_left(ft::node<T> * _node)
		{
			if (_node->left != NULL)	
				return most_left(_node->left);
			else
				return _node;
		}

	template < class T >
		ft::node<T> *	most_right(ft::node<T> * _node)
		{
			if (_node->right != NULL)
				return most_right(_node->right);
			else
				return _node;
		}


	template < class T >
		class m_iterator
		{
			public:
				typedef std::random_access_iterator_tag			iterator_category;
				typedef T										value_type;
				typedef ptrdiff_t								difference_type;
				typedef T*										pointer;
				typedef T&										reference;
				typedef m_iterator<const T>						const_iterator;
				/* typedef m_iterator< ft::node<const T> >			const_iterator; */

			public:
				m_iterator() : _data(NULL) {}
				m_iterator(ft::node<T> * item) : _data(item) {}
				~m_iterator() {}

				m_iterator<T> &		operator=(const m_iterator<T> & iter);

				m_iterator<T> &		operator++();
				m_iterator<T>		operator++(int);
				m_iterator<T> &		operator--();
				m_iterator<T>		operator--(int);

				/* ft::node<value_type> &	operator[](int n) const; */	
				reference	operator*();
				pointer		operator->() { return &(operator*()); }

			private:
				ft::node<value_type> *	_data;
				
		};

//..................................Access.......................................

	template < class T >
		typename m_iterator<T>::reference	m_iterator<T>::operator*()
		{
			return this->_data->data; //nombres caca cambiar
		}

//................................. Operator = ..................................

	template < class T >
		m_iterator<T> &		m_iterator<T>::operator=(const m_iterator<T> & iter)
		{
			this->_data = iter._data;
			return (*this);
		}

//............................... Operator ++ & -- ..............................

	template < class T >
		m_iterator<T> &		m_iterator<T>::operator++()
		{
			ft::node<T>*	tmp = this->_data;	

			if (tmp->right != NULL)
			{
				this->_data = most_left(tmp->right);
				return *this;
			}
			while (tmp->parent != NULL && tmp->parent->right == tmp)
				tmp = tmp->parent;

			if (tmp->parent != NULL)
			{
				this->_data = tmp->parent;
				return *this;
			}
			else
			{
				this->_data = most_right(tmp)->right;
				return *this;
			}
		}

	template < class T >
		m_iterator<T>	m_iterator<T>::operator++(int)
		{
			m_iterator<T>	tmp = *this;	
			++*this;
			return tmp;
		}

	template < class T >
		m_iterator<T> &		m_iterator<T>::operator--()
		{
			ft::node<T>*	tmp = this->_data;	
			m_iterator<T>	it;

			if (tmp->left != NULL)
			{
				this->_data = most_right(tmp->left);
				return *this;
			}
			while (tmp->parent != NULL && tmp->parent->left == tmp)
				tmp = tmp->parent;

			if (tmp->parent != NULL)
			{
				this->_data = tmp->parent;
				return *this;
			}
			else
			{
				this->_data = most_left(tmp)->left;
				return *this;
			}
		}

	template < class T >
		m_iterator<T>	m_iterator<T>::operator--(int)
		{
			m_iterator<T>	tmp = *this;	
			--*this;
			return tmp;
		}

//.........................Relational Operators.......................................

	/* template < class T > */
	/* 	bool	operator!=(const m_iterator<T> & lhs, const m_iterator<T> & rhs) */
	/* 	{ */
	/* 		return (lhs->first != rhs->first); */
	/* 	} */
	/* template < class T, class S> */
	/* 	bool	operator!=(const m_iterator<T> & lhs, const m_iterator<S> & rhs) */
	/* 	{ */
	/* 		return lhs->first != rhs->first; */
	/* 	} */

}

#endif
