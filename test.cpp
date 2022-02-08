#include "Vector_Iterator.hpp"
#include "is_integral.hpp"
#include <iostream>

int		main()
{
	std::cout << std::boolalpha;	
	std::cout << ft::is_integral<int>::value << std::endl;
	std::cout << ft::is_integral<char>::value << std::endl;
}
