#include "map.hpp"

int		main()
{
	ft::map<int, char>		mymap;
	std::pair<int, char>	p(1, 'a');
	std::pair<int, char>	p2(3, 'b');
	std::pair<int, char>	p3(0, 'c');
	std::pair<int, char>	p4(2, 'd');


	mymap.insert(p);
	std::cout << mymap.insert(p2).first->first << std::endl;
	std::cout << mymap.insert(p3).first->first << std::endl;
	std::cout << mymap.insert(p3).first->first << std::endl;
	mymap.insert(p4);

	ft::map<int, char>::iterator	first = mymap.begin();
	ft::map<int, char>::iterator	last = mymap.end();

	std::cout << first->first << std::endl;
	++first;
	std::cout << first->first << std::endl;
	++first;
	std::cout << first->first << std::endl;
	++first;
	std::cout << first->first << std::endl;
	++first;

	std::cout << mymap[3] << std::endl;
	/* std::cout << first->first << std::endl; */
	/* ++first; */
	std::cout << mymap.size() << std::endl;

	/* std::cout << most_left(mymap._node)->data.first << std::endl; */
	/* std::cout << mymap._node->data.first << std::endl; */
	/* std::cout << mymap._node->left->data.first << std::endl; */
	/* std::cout << mymap._node->right->data.first << std::endl; */
	/* std::cout << mymap._node->right->left->data.first << std::endl; */
}
