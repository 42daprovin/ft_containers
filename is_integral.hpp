#ifndef IS_INTEGRAL_HPP
# define IS_INTEGRAL_HPP

namespace ft{

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

}

#endif
