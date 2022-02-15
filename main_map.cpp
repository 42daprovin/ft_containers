#include "map.hpp"
#include "algorithm.hpp"
#include <map>

int		main()
{
	ft::map<int, char>		mymap;
	ft::pair<int, char>	p(1, 'a');
	ft::pair<int, char>	p2(3, 'b');
	ft::pair<int, char>	p3(0, 'c');
	ft::pair<int, char>	p4(2, 'd');


	mymap.insert(p);
	std::cout << mymap.insert(p2).first->first << std::endl;
	std::cout << mymap.insert(p3).first->first << std::endl;
	std::cout << mymap.insert(p3).first->first << std::endl;
	std::cout << std::endl << std::endl;
	mymap.insert(mymap.begin(), p4);

	ft::map<int, char>::iterator	first = mymap.begin();
	ft::map<int, char>::iterator	last = mymap.end();


	ft::map<int, char>		mymap_2;
	mymap_2 = mymap;

	ft::map<int, char>::iterator	first_2 = mymap_2.begin();
	ft::map<int, char>::iterator	last_2 = mymap_2.end();

	for ( ; first_2 != last_2 ; ++first_2 )
		std::cout << first_2->first << std::endl;

	++first;
	mymap.erase(first);

	first = mymap.begin();
	last = mymap.end();

	for ( ; first != last ; ++first )
		std::cout << first->first << std::endl;

	std::cout << "==========Erase==========" << std::endl << std::endl;
	{
		ft::map<char,int> mymap;
		ft::map<char,int>::iterator it;

		// insert some values:
		mymap['a']=10;
		mymap['b']=20;
		mymap['c']=30;
		mymap['d']=40;
		mymap['e']=50;
		mymap['f']=60;

		it=mymap.find('b');
		mymap.erase (it);                   // erasing by iterator

		mymap.erase ('c');                  // erasing by key

		it=mymap.find ('e');
		mymap.erase ( it, mymap.end() );    // erasing by range

		// show content:
		for (it=mymap.begin(); it!=mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
	}

	std::cout << "==========Upper_bound and Lower_bound==========" << std::endl << std::endl;
	{
		ft::map<char,int> mymap;
		ft::map<char,int>::iterator itlow,itup;

		mymap['a']=20;
		mymap['b']=40;
		mymap['c']=60;
		mymap['d']=80;
		mymap['e']=100;

		itlow = mymap.lower_bound ('b');  // itlow points to b
		itup = mymap.upper_bound ('d');   // itup points to e (not d!)

		mymap.erase(itlow,itup);        // erases [itlow,itup)

		// print content:
		for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
	}

	std::cout << "==============Equal_range============" << std::endl << std::endl;
	{
		ft::map<char,int> mymap;

		mymap['a']=10;
		mymap['b']=20;
		mymap['c']=30;

		ft::pair<ft::map<char,int>::iterator,ft::map<char,int>::iterator> ret;
		ret = mymap.equal_range('b');

		std::cout << "lower bound points to: ";
		std::cout << ret.first->first << " => " << ret.first->second << '\n';

		std::cout << "upper bound points to: ";
		std::cout << ret.second->first << " => " << ret.second->second << '\n';

	}


	/* std::cout << "begin: "<< first->first << std::endl; */
	/* std::cout << last->second << std::endl; */

	/* last = mymap.end(); */
	/* std::cout << last->first << std::endl; */
	/* std::cout << last->second << std::endl; */

	/* for ( ; first != last ; ++first ) */
	/* 	std::cout << first->first << std::endl; */

	/* mymap.clear(); */

	/* for ( ; last != first ; --last ) */
		/* std::cout << first->first << std::endl; */

	/* ++first; */
	/* std::cout << first->first << std::endl; */
	/* ++first; */
	/* std::cout << first->first << std::endl; */
	/* ++first; */
	/* std::cout << first->first << std::endl; */
	/* ++first; */

	/* std::cout << mymap[3] << std::endl; */
	/* std::cout << first->first << std::endl; */
	/* ++first; */
	/* std::cout << mymap.size() << std::endl; */

	/* std::cout << "antano print: " << std::endl; */
	/* std::cout << most_left(mymap._node)->data.first << std::endl; */
	/* std::cout << mymap._node->data.first << std::endl; */
	/* std::cout << mymap._node->left->data.first << std::endl; */
	/* std::cout << mymap._node->right->data.first << std::endl; */
	/* std::cout << mymap._node->right->left->data.first << std::endl; */

	/* std::map<int, char>		smap; */
	/* std::pair<int, char>	p(1, 'a'); */
	/* std::pair<int, char>	p2(3, 'b'); */
	/* std::pair<int, char>	p3(0, 'c'); */
	/* std::pair<int, char>	p4(2, 'd'); */

	/* smap.insert(p); */
	/* smap.insert(p2); */
	/* smap.insert(p3); */
	/* smap.insert(p4); */

	/* smap.clear(); */

	/* std::map<int, char>::iterator	en = smap.end(); */
	/* std::map<int, char>::iterator	bg = smap.begin(); */

	/* if (en == bg) */
	/* 	std::cout << "curioso" << std::endl; */
	
}
