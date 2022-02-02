#include "vector.hpp"

int		main()
{	
	Vector<int>		v;
	std::cout << "vec's size: " << v.size() << std::endl;
	std::cout << "vec's capacity: " << v.capacity() << std::endl;

	v.push_back(1);
	std::cout << "vec's size: " << v.size() << std::endl;
	std::cout << "vec's capacity: " << v.capacity() << std::endl;
	v.push_back(2);
	std::cout << "vec's size: " << v.size() << std::endl;
	std::cout << "vec's capacity: " << v.capacity() << std::endl;
	v.push_back(3);
	std::cout << "vec's size: " << v.size() << std::endl;
	std::cout << "vec's capacity: " << v.capacity() << std::endl;
	v.push_back(4);
	std::cout << "vec's size: " << v.size() << std::endl;
	std::cout << "vec's capacity: " << v.capacity() << std::endl;
	v.push_back(5);
	std::cout << "vec's size: " << v.size() << std::endl;
	std::cout << "vec's capacity: " << v.capacity() << std::endl;
	v.push_back(6);
	std::cout << "vec's size: " << v.size() << std::endl;
	std::cout << "vec's capacity: " << v.capacity() << std::endl;
	v.push_back(7);
	std::cout << "vec's size: " << v.size() << std::endl;
	std::cout << "vec's capacity: " << v.capacity() << std::endl;
	v.push_back(8);
	std::cout << "vec's size: " << v.size() << std::endl;
	std::cout << "vec's capacity: " << v.capacity() << std::endl;
	v.push_back(9);
	std::cout << "vec's size: " << v.size() << std::endl;
	std::cout << "vec's capacity: " << v.capacity() << std::endl;
	v.push_back(10);
	std::cout << "vec's size: " << v.size() << std::endl;
	std::cout << "vec's capacity: " << v.capacity() << std::endl;

	for (size_t i = 0; i < v.size(); i++)
	{
		std::cout << v[i] << " ";
	}
	std::cout << std::endl;
	return 0;
}
