#include "Vector.hpp"

int		main()
{	
	Vector<int>		v;
	Vector<int>		w;
	std::cout << "vec's size: " << v.size() << std::endl;
	std::cout << "vec's capacity: " << v.capacity() << std::endl;
	std::cout << "vec's max size: " << v.max_size() << std::endl;

	v.reserve(100);
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

	v.resize(5);

	std::cout << "v.front: " << v.front() << std::endl;
	std::cout << "v.back: " << v.back() << std::endl;

	Vector<int>::iterator	first = v.begin();
	Vector<int>::iterator	end = v.end();

	w.assign(first, end);
	v.assign(7, 100);
	
	std::cout << "w[3]: " << w[3] << std::endl;
	std::cout << "w.at(3): " << w.at(3) << std::endl;

	try
	{
		w.at(9000);
	}
	catch (const std::out_of_range& oor)
	{
   		 std::cerr << "Out of Range error: " << oor.what() << '\n';
  	}

	v = w;

	Vector<int>::iterator	pos = v.begin() + 2;

	v.insert(pos, 3, 78);

	for (size_t i = 0; i < v.size(); i++)
	{
		std::cout << v[i] << " ";
	}
	std::cout << std::endl;
	std::cout << "vec's size: " << v.size() << std::endl;

	for (size_t i = 0; i < w.size(); i++)
	{
		std::cout << w[i] << " ";
	}
	std::cout << std::endl;
	std::cout << "vec's size: " << w.size() << std::endl;

	Vector<int>		test_v(v);

	Vector<int>::iterator	pos_2 = (test_v.begin());

	test_v.insert(pos_2, 42);

	for (size_t i = 0; i < test_v.size(); i++)
	{
		std::cout << test_v[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "vec's capacity: " << test_v.capacity() << std::endl;
	std::cout << "vec's size: " << test_v.size() << std::endl;

	
	return 0;
}
