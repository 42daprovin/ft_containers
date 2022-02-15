#ifndef ALGORITHM
# define ALGORITHM

namespace ft{

	template < class InputIterator1, class InputIterator2 >
		bool	lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
		{
			while (first1 != last1)			
			{
				if (first2 == last2 || *first2 < *first1)
					return false ;
				else if (*first1 < *first2)
					return true ;
				++first1;
				++first2;
			}
			return (first2 != last2);
		}

	template < class InputIterator1, class InputIterator2, class Compare>
		bool	lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp)
		{
			while (first1 != last1)
			{
				if (first2 == last2 || comp(*first2, *first1))
					return false ;
				else if (comp(*first1, *first2))
					return true ;
				++first1;
				++first2;
			}
			return (first2 != last2);
		}

	template < class T1, class T2 >
		class pair
		{
			public:
				typedef	T1		first_type;
				typedef T2		second_type;

			public:

				pair()
				{
					first = first_type();
					second = second_type();
				}

				template< class U, class V> pair(const pair<U, V> & pr) : first(pr.first), second(pr.second) {}

				pair(const first_type & a, const second_type & b) : first(a), second(b) {}

				pair &	operator=(const pair & pr)
				{
					first = pr.first;
					second = pr.second;
					return *this;
				}

			public:
				first_type		first;
				second_type		second;
		};

	template < class T1, class T2>
		pair<T1, T2> make_pair(T1 x, T2 y)
		{
			return (pair<T1, T2>(x, y));
		}


}

#endif
