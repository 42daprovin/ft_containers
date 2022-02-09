#include "vector.hpp"

int		main()
{	
	ft::vector<int>		v;
	ft::vector<int>		w;
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

	ft::vector<int>::iterator	first = v.begin();
	ft::vector<int>::iterator	end = v.end();

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

	ft::vector<int>::iterator	pos = v.begin() + 2;

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

	ft::vector<int>		test_v(v);

	ft::vector<int>::iterator	pos_2 = (test_v.begin());

	test_v.insert(pos_2, 42);

	for (size_t i = 0; i < test_v.size(); i++)
	{
		std::cout << test_v[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "vec's capacity: " << test_v.capacity() << std::endl;
	std::cout << "vec's size: " << test_v.size() << std::endl;
	{
		ft::vector<int> myvector (3,100);
		ft::vector<int>::iterator it;

		it = myvector.begin();
		it = myvector.insert ( it , 200 );

		myvector.insert (it,2,300);

		// "it" no longer valid, get a new one:
		it = myvector.begin();

		ft::vector<int> anothervector (2,400);
		myvector.insert (it+2,anothervector.begin(),anothervector.end());

		int myarray [] = { 501,502,503 };
		myvector.insert (myvector.begin(), myarray, myarray+3);

		std::cout << "myvector contains:";
		for (it=myvector.begin(); it<myvector.end(); it++)
			std::cout << ' ' << *it;
		std::cout << '\n';
	}
	{
		ft::vector<int> myvector;

		// set some values (from 1 to 10)
		for (int i=1; i<=10; i++) myvector.push_back(i);

		// erase the 6th element
		myvector.erase (myvector.begin()+5);

		// erase the first 3 elements:
		myvector.erase (myvector.begin(),myvector.begin()+3);

		std::cout << "myvector contains:";
		for (unsigned i=0; i<myvector.size(); ++i)
			std::cout << ' ' << myvector[i];
		std::cout << '\n';
	}
	{
		ft::vector<int> foo (3,100);   // three ints with a value of 100
		ft::vector<int> bar (5,200);   // five ints with a value of 200

		foo.swap(bar);

		std::cout << "foo contains:";
		for (unsigned i=0; i<foo.size(); i++)
			std::cout << ' ' << foo[i];
		std::cout << '\n';

		std::cout << "bar contains:";
		for (unsigned i=0; i<bar.size(); i++)
			std::cout << ' ' << bar[i];
		std::cout << '\n';

		return 0;
	}
	return 0;
}
