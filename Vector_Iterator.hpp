#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

# include <cstddef>
# include <iterator>

namespace ft{

	template < typename T >
		class iterator
		{
			public:
				typedef	std::random_access_iterator_tag		iterator_category;
				typedef	T									value_type;
				typedef	int									difference_type;
				typedef	T*									pointer;
				typedef	T&									reference;
				typedef iterator<const T>					const_iterator;

			public:
				iterator() : _pointer(NULL) {}
				iterator(T * item) : _pointer(item) {}
				~iterator() {}

				iterator<T> &	operator=(const iterator<T> & iter);
				iterator<T>		operator+(int n) const;
				iterator<T>		operator-(int n) const;

				iterator<T> &	operator++();
				iterator<T>		operator++(int);
				iterator<T>	&	operator--();
				iterator<T>		operator--(int);

				iterator<T> &	operator+=(difference_type n);
				iterator<T> &	operator-=(difference_type n);

				T &		operator[](int	n) const;
				T &		operator*();
				pointer	operator->() { return &(operator*()); }
				

				pointer		base() const { return _pointer; }

				operator const_iterator() const 
				{
					const_iterator	tmp( _pointer);
					return tmp;
				}

			private:
				T		* _pointer;

		};

	/* template < typename T > class const_iterator : public iterator<const T> {}; */


	template < typename T >
		iterator<T> &	iterator<T>::operator=(const iterator<T> & iter)
		{
			this->_pointer = iter._pointer;
			return (*this);
		}

//.................................Member + & - .................................

	template < typename T >
		iterator<T>		iterator<T>::operator+(int n) const
		{
			iterator<T>		tmp(this->_pointer + n);	
			return tmp;
		}

	template < typename T >
		iterator<T>		iterator<T>::operator-(int n) const
		{
			iterator<T>		tmp(this->_pointer - n);	
			return tmp;
		}

//.............................Advance & Retrocede...............................

	template < typename T >
		iterator<T> &		iterator<T>::operator+=(iterator<T>::difference_type n)
		{
			_pointer = _pointer + n;
			return *this;
		}

	template < typename T >
		iterator<T> &		iterator<T>::operator-=(iterator<T>::difference_type n)
		{
			_pointer = _pointer - n;
			return *this;
		}

//.............................relational operators..............................

	template < typename T >
		bool	operator==(const iterator<T> & lhs, const iterator<T> & rhs)
		{
			return	lhs.base() == rhs.base();
		}
	template < typename T, typename S>
		bool	operator==(const iterator<T> & lhs, const iterator<S> & rhs)
		{
			return lhs.base() == rhs.base();
		}

	template < typename T >
		bool	operator!=(const iterator<T> & lhs, const iterator<T> & rhs)
		{
			return	lhs.base() != rhs.base();
		}
	template < typename T, typename S>
		bool	operator!=(const iterator<T> & lhs, const iterator<S> & rhs)
		{
			return lhs.base() != rhs.base();
		}

	template < typename T >
		bool	operator<=(const iterator<T> & lhs, const iterator<T> & rhs)
		{
			return	lhs.base() <= rhs.base();
		}
	template < typename T, typename S>
		bool	operator<=(const iterator<T> & lhs, const iterator<S> & rhs)
		{
			return lhs.base() <= rhs.base();
		}
	
	template < typename T >
		bool	operator>=(const iterator<T> & lhs, const iterator<T> & rhs)
		{
			return	lhs.base() >= rhs.base();
		}
	template < typename T, typename S>
		bool	operator>=(const iterator<T> & lhs, const iterator<S> & rhs)
		{
			return lhs.base() >= rhs.base();
		}
	
	template < typename T >
		bool	operator<(const iterator<T> & lhs, const iterator<T> & rhs) 
		{
			return	lhs.base() < rhs.base();
		}
	template < typename T, typename S>
		bool	operator<(const iterator<T> & lhs, const iterator<S> & rhs) 
		{
			return lhs.base() < rhs.base();
		}
	
	template < typename T >
		bool	operator>(const iterator<T> & lhs, const iterator<T> & rhs)
		{
			return	lhs.base() > rhs.base();
		}
	template < typename T, typename S>
		bool	operator>(const iterator<T> & lhs, const iterator<S> & rhs)
		{
			return lhs.base() > rhs.base();
		}
//..........................Increase & Decrease....................................

	template < typename T >
		iterator<T> &	iterator<T>::operator++()
		{
			this->_pointer++;
			return *this;
		}

	template < typename T >
		iterator<T>		iterator<T>::operator++(int)
		{
			iterator<T>		tmp = *this;
			this->_pointer++;
			return tmp;
		}

	template < typename T >
		iterator<T> &	iterator<T>::operator--()
		{
			this->_pointer--;
			return *this;
		}

	template < typename T >
		iterator<T>		iterator<T>::operator--(int)
		{
			iterator<T>		tmp = *this;
			this->_pointer--;
			return tmp;
		}
//.......................Access..............................

	template < typename T >
		T &		iterator<T>::operator[](int	n) const
		{
			return *(this->_pointer + n);
		}

	template < typename T >
		T &		iterator<T>::operator*()
		{
			return *this->_pointer;
		}
//...................... non-member + & - ................

	template < typename T >
		iterator<T>		operator+(int n, const iterator<T> & it)
		{
			return (it + n);
		}

	template < typename T >
		iterator<T>		operator-(int n, const iterator<T> & it)
		{
			return (it - n);
		}
	
	template < typename T >
		int		operator+(const iterator<T> & lhs, const iterator<T> & rhs)
		{
			return	lhs.base() + rhs.base();
		}
	template < typename T , typename S >
		int		operator+(const iterator<T> & lhs, const iterator<S> & rhs)
		{
			return	lhs.base() + rhs.base();
		}

	template < typename T >
		int		operator-(const iterator<T> & lhs, const iterator<T> & rhs)
		{
			return	lhs.base() - rhs.base();
		}
	template < typename T , typename S >
		int		operator-(const iterator<T> & lhs, const iterator<S> & rhs)
		{
			return	lhs.base() - rhs.base();
		}
}

#endif
