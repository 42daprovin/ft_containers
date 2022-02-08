#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

template < class Iterator >
class reverse_iterator
{
	public:
		typedef	Iterator						iterator_type;
		typedef Iterator::iterator_category		iterator_category;	
		typedef	Iterator::value_type			value_type;
		typedef	Iterator::difference_type		difference_type;
		typedef	Iterator::pointer				pointer;
		typedef Iterator::reference				reference;

	public:

		reverse_iterator();
		explicit reverse_iterator(iterator_type it) : _it(it) {};
		template < class Iter>
			reverse_iterator(const reverse_iterator<Iter> & rev_it);
		~reverse_iterator() {};
		
		iterator_type	base() const;
		
		reference	operator*();
		reference	operator[](difference_type n) const;

		reverse_iterator	operator+(difference_type n) const;
		reverse_iterator	operator-(difference_type n) const;

		reverse_iterator &	operator++();
		reverse_iterator	operator++(int);
		reverse_iterator &	operator--();
		reverse_iterator	operator--(int);
		reverse_iterator &	operator+=(difference_type n);
		reverse_iterator &	operator-=(difference_type n);
		
		pointer		operator->() const;
			

	private:
		Iterator	_it;
};

template < class Iterator >
bool	operator==(const reverse_iterator<Iterator> & lhs, const reverse_iterator<Iterator> & rhs)
{}

template < class Iterator >
bool	operator!=(const reverse_iterator<Iterator> & lhs, const reverse_iterator<Iterator> & rhs)
{}

template < class Iterator >
bool	operator<=(const reverse_iterator<Iterator> & lhs, const reverse_iterator<Iterator> & rhs)
{}

template < class Iterator >
bool	operator>=(const reverse_iterator<Iterator> & lhs, const reverse_iterator<Iterator> & rhs)
{}

template < class Iterator >
bool	operator<(const reverse_iterator<Iterator> & lhs, const reverse_iterator<Iterator> & rhs)
{}

template < class Iterator >
bool	operator>(const reverse_iterator<Iterator> & lhs, const reverse_iterator<Iterator> & rhs)
{}

#endif
