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

	template < class T>
		const ft::node<T> * most_left(const ft::node<T> * _node)
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
		const ft::node<T> *	most_right(const ft::node<T> * _node)
		{
			if (_node->right != NULL)
				return most_right(_node->right);
			else
				return _node;
		}

	template < class T >
		class const_m_iterator
		{
			public:
				typedef std::bidirectional_iterator_tag			iterator_category;
				typedef T										value_type;
				typedef ptrdiff_t								difference_type;
				typedef const T*										pointer;
				typedef const T&										reference;

			public:
				const_m_iterator() : _data(NULL) {}
				const_m_iterator(const ft::node<T>  * item) { _data = item ; }
				~const_m_iterator() {}

				const_m_iterator<T> &		operator=(const const_m_iterator<T> & iter) {
					this->_data = iter._data;
					return (*this);
				}

				const_m_iterator<T> &		operator++();
				const_m_iterator<T>		operator++(int);
				const_m_iterator<T> &		operator--();
				const_m_iterator<T>		operator--(int);

				reference	operator*() { return this->_data->data; }
				pointer		operator->() { return &(operator*()); }

				const ft::node<value_type> *		base() const { return _data; }

			private:
				const ft::node<value_type> *	_data;
				
		};

	template < class T >
		class m_iterator
		{
			public:
				typedef std::bidirectional_iterator_tag			iterator_category;
				typedef T										value_type;
				typedef ptrdiff_t								difference_type;
				typedef T*										pointer;
				typedef T&										reference;
				typedef ft::const_m_iterator<T>					const_iterator;

			public:
				m_iterator() : _data(NULL) {}
				m_iterator(ft::node<T> * item) { this->_data = item; }
				~m_iterator() {}

				m_iterator<T> &		operator=(const m_iterator<T> & iter);

				m_iterator<T> &		operator++();
				m_iterator<T>		operator++(int);
				m_iterator<T> &		operator--();
				m_iterator<T>		operator--(int);

				reference	operator*();
				pointer		operator->() { return &(operator*()); }

				ft::node<value_type> *		base() const { return _data; }

				operator  const_iterator() const
				{
					const_iterator tmp(_data);
					return tmp;
				}

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
				this->_data = most_right(tmp)->right; //creo que no hace falta, nunca entramos aqui;
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
				/* this->_data = most_left(tmp)->left; */
				this->_data = tmp;		//seria devolver el centinel, no hay muchas pruebas al respecto;
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

	template < class T >
		const_m_iterator<T> &		const_m_iterator<T>::operator++()
		{
			const ft::node<T>*	tmp = this->_data;	

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
				this->_data = most_right(tmp)->right; //creo que no hace falta, nunca entramos aqui;
				return *this;
			}
		}

	template < class T >
		const_m_iterator<T>	const_m_iterator<T>::operator++(int)
		{
			const_m_iterator<T>	tmp = *this;	
			++*this;
			return tmp;
		}

	template < class T >
		const_m_iterator<T> &		const_m_iterator<T>::operator--()
		{
			const ft::node<T>*	tmp = this->_data;	
			const_m_iterator<T>	it;

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
				/* this->_data = most_left(tmp)->left; */
				this->_data = tmp;		//seria devolver el centinel, no hay muchas pruebas al respecto;
				return *this;
			}
		}

	template < class T >
		const_m_iterator<T>	const_m_iterator<T>::operator--(int)
		{
			const_m_iterator<T>	tmp = *this;	
			--*this;
			return tmp;
		}

//..............................Relational Operators.......................................

	template < class T >
		bool	operator!=(const m_iterator<T> & lhs, const m_iterator<T> & rhs)
		{
			return lhs.base() != rhs.base();
		}
	template < class T, class S>
		bool	operator!=(const m_iterator<T> & lhs, const const_m_iterator<S> & rhs)
		{
			return lhs.base() != rhs.base();
		}
	template < class T >
		bool	operator==(const m_iterator<T> & lhs, const m_iterator<T> & rhs)
		{
			return lhs.base() == rhs.base();
		}
	template < class T, class S>
		bool	operator==(const m_iterator<T> & lhs, const const_m_iterator<S> & rhs)
		{
			return lhs.base() == rhs.base();
		}

	template < class T >
		bool	operator!=(const const_m_iterator<T> & lhs, const const_m_iterator<T> & rhs)
		{
			return lhs.base() != rhs.base();
		}
	template < class T, class S>
		bool	operator!=(const const_m_iterator<T> & lhs, const m_iterator<S> & rhs)
		{
			return lhs.base() != rhs.base();
		}
	template < class T >
		bool	operator==(const const_m_iterator<T> & lhs, const const_m_iterator<T> & rhs)
		{
			return lhs.base() == rhs.base();
		}
	template < class T, class S>
		bool	operator==(const const_m_iterator<T> & lhs, const m_iterator<S> & rhs)
		{
			return lhs.base() == rhs.base();
		}

}

#endif
