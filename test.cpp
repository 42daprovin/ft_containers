#include "Vector_Iterator.hpp"
#include <iostream>

int		main()
{
	int		a = 3;
	Iterator<int>	iter(&a);
	Iterator<int>	test;

	test = iter;

	std::cout << (iter == test) << std::endl;
	std::cout << (iter != test) << std::endl;

}
