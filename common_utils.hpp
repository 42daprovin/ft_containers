#ifndef COMMON_UTILS_HPP
# define COMMON_UTILS_HPP

namespace ft{

//....................................Lexocigraphical_compare............................................

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

//...................................Equal.......................................................

	template < class InputIterator1, class InputIterator2 >
		bool	equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
		{
			while (first1 != last1)
			{
				if (!(*first1 == *first2))
					return false;
				++first1; ++first2;
			}
			return true;
		}

	template < class InputIterator1, class InputIterator2, class BinaryPredicate >
		bool	equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
		{
			while (first1 != last1)
			{
				if (!pred(*first1, *first2))
					return false;
				++first1; ++first2;
			}
			return true;
		}

//....................................Pair & make_pair..............................................

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

	template <class T1, class T2>
		bool operator==(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return lhs.first==rhs.first && lhs.second==rhs.second; }

	template <class T1, class T2>
		bool operator!=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return !(lhs==rhs); }

	template <class T1, class T2>
		bool operator<(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }

	template <class T1, class T2>
		bool operator<=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return !(rhs<lhs); }

	template <class T1, class T2>
		bool operator>(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return rhs<lhs; }

	template <class T1, class T2>
		bool operator>=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return !(lhs<rhs); }


//......................Enable_if......................................


	template < bool Cond, class T = void > struct enable_if {};
	template < class T > struct enable_if<true, T> { typedef T	type; };
	
//......................Is_Integral.....................................


	template < class T, T v >
		struct integral_constant
		{
			typedef integral_constant	type;
			typedef T					value_type;
			static const T 				value = v;
		};

	typedef integral_constant<bool, true> true_type;
	typedef integral_constant<bool, false> false_type;

	template <typename> struct is_integral_base : false_type {};
	template <> struct is_integral_base<bool> : true_type {};
	template <> struct is_integral_base<char> : true_type {};
	template <> struct is_integral_base<wchar_t> : true_type {};
	template <> struct is_integral_base<signed char> : true_type {};
	template <> struct is_integral_base<short int> : true_type {};
	template <> struct is_integral_base<int> : true_type {};
	template <> struct is_integral_base<long int> : true_type {};
	template <> struct is_integral_base<long long int> : true_type {};
	template <> struct is_integral_base<unsigned char> : true_type {};
	template <> struct is_integral_base<unsigned short int> : true_type {};
	template <> struct is_integral_base<unsigned int> : true_type {};
	template <> struct is_integral_base<unsigned long int> : true_type {};
	template <> struct is_integral_base<unsigned long long int> : true_type {};
	
	template < typename T > struct is_integral : is_integral_base<T> {};

//..........................Node...................................

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
			
			private:
				
				node<value_type> * useless;
			
		};

//..........................Utility Functions...........................
	
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

}

#endif
