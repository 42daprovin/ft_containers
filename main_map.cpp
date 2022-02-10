#include "map.hpp"


int		main()
{
	ft::map<int, char>		mymap;
	std::pair<int, char>	p(1, 'a');

	mymap.insert(p);
}
