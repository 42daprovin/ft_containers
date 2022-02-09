#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP


namespace ft{

	template < class Iterator >
		class reverse_iterator
		{
			public:
				typedef	Iterator						iterator_type;
				typedef typename Iterator::iterator_category		iterator_category;	
				typedef	typename Iterator::value_type			value_type;
				typedef	typename Iterator::difference_type		difference_type;
				typedef	typename Iterator::pointer				pointer;
				typedef typename Iterator::reference			reference;
				typedef reverse_iterator<const Iterator>		const_reverse_iterator;

			public:

				reverse_iterator();
				explicit reverse_iterator(iterator_type it) : _it(it) {}
				template < class Iter>
					reverse_iterator(const reverse_iterator<Iter> & rev_it) { this->_it = rev_it.base(); }
				~reverse_iterator() {}

				reverse_iterator &	operator=(const reverse_iterator & iter)
				{
					this->_it = iter.base();	
					return (*this);
				}

//.............................Getters.....................................

				iterator_type	base() const
				{
					return (_it);
				}
				reference	operator*()
				{
					return *(_it - 1);
				}
				reference	operator[](difference_type n) const
				{
					return (_it[- n - 1 ]);
				}
				pointer		operator->() const
				{
					return &(operator*());
				}

//..............................Add and Subs....................................

				reverse_iterator	operator+(difference_type n) const
				{
					reverse_iterator<Iterator>	tmp(_it - n);	
					return tmp;
				}
				reverse_iterator	operator-(difference_type n) const
				{
					reverse_iterator<Iterator>	tmp(_it + n);
					return tmp;
				}

//............................Increment and Decrease.............................

				reverse_iterator &	operator++()
				{
					_it--;
					return *this;
				}
				reverse_iterator	operator++(int)
				{
					reverse_iterator<Iterator>	tmp = *this;
					++(*this);
					return tmp;
				}
				reverse_iterator &	operator--()
				{
					_it++;
					return *this;
				}
				reverse_iterator	operator--(int)
				{
					reverse_iterator<Iterator>	tmp = *this;
					--(*this);
					return tmp;
				}

//..........................Advance and Retrocede.................................

				reverse_iterator &	operator+=(difference_type n)
				{
					_it = _it - n;
					return *this;
				}
				reverse_iterator &	operator-=(difference_type n)
				{
					_it = _it + n;	
					return *this;
				}



			private:
				Iterator	_it;
		};

	template < class Iterator >
		bool	operator==(const reverse_iterator<Iterator> & lhs, const reverse_iterator<Iterator> & rhs)
		{
			return (lhs.base() == rhs.base());
		}
	template < class Iterator, class S>
		bool	operator==(const reverse_iterator<Iterator> & lhs, const reverse_iterator<S> & rhs)
		{
			return (lhs.base() == rhs.base());
		}

	template < class Iterator >
		bool	operator!=(const reverse_iterator<Iterator> & lhs, const reverse_iterator<Iterator> & rhs)
		{
			return (lhs.base() != rhs.base());
		}
	template < class Iterator, class S>
		bool	operator!=(const reverse_iterator<Iterator> & lhs, const reverse_iterator<S> & rhs)
		{
			return (lhs.base() != rhs.base());
		}

	template < class Iterator >
		bool	operator<=(const reverse_iterator<Iterator> & lhs, const reverse_iterator<Iterator> & rhs)
		{
			return (lhs.base() >= rhs.base());
		}
	template < class Iterator, class S>
		bool	operator<=(const reverse_iterator<Iterator> & lhs, const reverse_iterator<S> & rhs)
		{
			return (lhs.base() >= rhs.base());
		}

	template < class Iterator >
		bool	operator>=(const reverse_iterator<Iterator> & lhs, const reverse_iterator<Iterator> & rhs)
		{
			return (lhs.base() <= rhs.base());
		}
	template < class Iterator, class S>
		bool	operator>=(const reverse_iterator<Iterator> & lhs, const reverse_iterator<S> & rhs)
		{
			return (lhs.base() <= rhs.base());
		}

	template < class Iterator >
		bool	operator<(const reverse_iterator<Iterator> & lhs, const reverse_iterator<Iterator> & rhs)
		{
			return (lhs.base() > rhs.base());
		}
	template < class Iterator, class S>
		bool	operator<(const reverse_iterator<Iterator> & lhs, const reverse_iterator<S> & rhs)
		{
			return (lhs.base() > rhs.base());
		}

	template < class Iterator >
		bool	operator>(const reverse_iterator<Iterator> & lhs, const reverse_iterator<Iterator> & rhs)
		{
			return (lhs.base() < rhs.base());
		}
	template < class Iterator, class S>
		bool	operator>(const reverse_iterator<Iterator> & lhs, const reverse_iterator<S> & rhs)
		{
			return (lhs.base() < rhs.base());
		}

//..................................................non-member + & - ...........................................................

	template < class Iterator >
		reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator> & rev_it)
		{
			return (rev_it + n);
		}

	template < class Iterator >
		reverse_iterator<Iterator> operator-(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator> & rev_it)
		{
			return (rev_it - n);
		}
	
	template < class Iterator>
		typename reverse_iterator<Iterator>::difference_type	operator+(const reverse_iterator<Iterator> lhs, const reverse_iterator<Iterator> rhs)
		{
			return (lhs.base() - rhs.base());
		}
	template < class Iterator, class S>
		typename reverse_iterator<Iterator>::difference_type	operator+(const reverse_iterator<Iterator> lhs, const reverse_iterator<S> rhs)
		{
			return (lhs.base() - rhs.base());
		}
	
	template < class Iterator>
		typename reverse_iterator<Iterator>::difference_type	operator-(const reverse_iterator<Iterator> lhs, const reverse_iterator<Iterator> rhs)
		{
			return (lhs.base() + rhs.base());
		}
	template < class Iterator, class S>
		typename reverse_iterator<Iterator>::difference_type	operator-(const reverse_iterator<Iterator> lhs, const reverse_iterator<S> rhs)
		{
			return (lhs.base() + rhs.base());
		}


}

#endif
