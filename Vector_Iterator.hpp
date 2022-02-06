#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

# include <cstddef>
# include <iterator>

template < typename T >
class Iterator
{
	public:
		typedef	std::random_access_iterator_tag		iterator_category;
		typedef	T									value_type;
		typedef	ptrdiff_t							difference_type;
		typedef	T*									pointer;
		typedef	T&									reference;

	public:
		Iterator() : _pointer(nullptr) {}
		Iterator(T * item) : _pointer(item) {}
		~Iterator() {}

		Iterator<T> &	operator=(const Iterator<T> & iter);

		Iterator<T>		operator+(int n);
		Iterator<T>		operator-(int n);

		bool	operator==(const Iterator<T> & iter) const;
		bool	operator!=(const Iterator<T> & iter) const;
		bool	operator>=(const Iterator<T> & iter) const;
		bool	operator<=(const Iterator<T> & iter) const;
		bool	operator<(const Iterator<T> & iter) const;
		bool	operator>(const Iterator<T> & iter) const;

		Iterator<T> &	operator++();
		Iterator<T>		operator++(int);
		Iterator<T>	&	operator--();
		Iterator<T>		operator--(int);

		T &		operator[](int	n);
		T &		operator*();

	private:
		T		* _pointer;

};

template < typename T >
Iterator<T> &	Iterator<T>::operator=(const Iterator<T> & iter)
{
	this->_pointer = iter._pointer;
	return (*this);
}

template < typename T >
Iterator<T>		Iterator<T>::operator+(int n)
{
	Iterator<T>		tmp(this->_pointer + n);	
	return tmp;
}

template < typename T >
Iterator<T>		Iterator<T>::operator-(int n)
{
	Iterator<T>		tmp(this->_pointer - n);	
	return tmp;
}

template < typename T >
bool	Iterator<T>::operator==(const Iterator<T> & iter) const
{
	return	this->_pointer == iter._pointer;
}

template < typename T >
bool	Iterator<T>::operator!=(const Iterator<T> & iter) const
{
	return	this->_pointer != iter._pointer;
}

template < typename T >
bool	Iterator<T>::operator>=(const Iterator<T> & iter) const
{
	return	this->_pointer >= iter._pointer;
}

template < typename T >
bool	Iterator<T>::operator<=(const Iterator<T> & iter) const
{
	return	this->_pointer <= iter._pointer;
}

template < typename T >
bool	Iterator<T>::operator<(const Iterator<T> & iter) const
{
	return	this->_pointer < iter._pointer;
}

template < typename T >
bool	Iterator<T>::operator>(const Iterator<T> & iter) const
{
	return	this->_pointer > iter._pointer;
}

template < typename T >
Iterator<T> &	Iterator<T>::operator++()
{
	this->_pointer++;
	return *this;
}

template < typename T >
Iterator<T>		Iterator<T>::operator++(int)
{
	Iterator<T>		tmp = *this;
	this->_pointer++;
	return tmp;
}

template < typename T >
Iterator<T> &	Iterator<T>::operator--()
{
	this->_pointer--;
	return *this;
}

template < typename T >
Iterator<T>		Iterator<T>::operator--(int)
{
	Iterator<T>		tmp = *this;
	this->_pointer--;
	return tmp;
}

template < typename T >
T &		Iterator<T>::operator[](int	n)
{
	return *(this->_pointer + n);
}

template < typename T >
T &		Iterator<T>::operator*()
{
	return *this->_pointer;
}
#endif
