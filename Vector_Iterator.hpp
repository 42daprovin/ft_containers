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
				/* typedef terator<const T>					const_iterator; */

			public:
				iterator() : _pointer(NULL) {}
				iterator(T * item) : _pointer(item) {}
				~iterator() {}

				iterator<T> &	operator=(const iterator<T> & iter);

				iterator<T>		operator+(int n);
				iterator<T>		operator-(int n);

				bool	operator==(const iterator<T> & iter) const;
				bool	operator!=(const iterator<T> & iter) const;
				bool	operator>=(const iterator<T> & iter) const;
				bool	operator<=(const iterator<T> & iter) const;
				bool	operator<(const iterator<T> & iter) const;
				bool	operator>(const iterator<T> & iter) const;

				iterator<T> &	operator++();
				iterator<T>		operator++(int);
				iterator<T>	&	operator--();
				iterator<T>		operator--(int);

				T &		operator[](int	n);
				T &		operator*();

			private:
				T		* _pointer;

		};

	template < typename T > class const_iterator : public iterator<const T> {};


	template < typename T >
		iterator<T> &	iterator<T>::operator=(const iterator<T> & iter)
		{
			this->_pointer = iter._pointer;
			return (*this);
		}

	template < typename T >
		iterator<T>		iterator<T>::operator+(int n)
		{
			iterator<T>		tmp(this->_pointer + n);	
			return tmp;
		}

	template < typename T >
		iterator<T>		iterator<T>::operator-(int n)
		{
			iterator<T>		tmp(this->_pointer - n);	
			return tmp;
		}

	template < typename T >
		bool	iterator<T>::operator==(const iterator<T> & iter) const
		{
			return	this->_pointer == iter._pointer;
		}

	template < typename T >
		bool	iterator<T>::operator!=(const iterator<T> & iter) const
		{
			return	this->_pointer != iter._pointer;
		}

	template < typename T >
		bool	iterator<T>::operator>=(const iterator<T> & iter) const
		{
			return	this->_pointer >= iter._pointer;
		}

	template < typename T >
		bool	iterator<T>::operator<=(const iterator<T> & iter) const
		{
			return	this->_pointer <= iter._pointer;
		}

	template < typename T >
		bool	iterator<T>::operator<(const iterator<T> & iter) const
		{
			return	this->_pointer < iter._pointer;
		}

	template < typename T >
		bool	iterator<T>::operator>(const iterator<T> & iter) const
		{
			return	this->_pointer > iter._pointer;
		}

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

	template < typename T >
		T &		iterator<T>::operator[](int	n)
		{
			return *(this->_pointer + n);
		}

	template < typename T >
		T &		iterator<T>::operator*()
		{
			return *this->_pointer;
		}

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
	//i need sumar dos iterators AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAaa

}

#endif
