#include <iostream>
#include <stdexcept>
#include "List.h"
#include "SSLL.h"

using namespace std;
using namespace cop3530;


//======this is the function parameter passed for contains()====
template <typename E>
bool compare_int(const E& element, const E& value);
//==============================================================

int main(){
	//===============================================================================================
	//========================Simple singly linked list (SSLL)=======================================
	//start iterator tests
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	cout << "testing iterators" << endl;
	SSLL<char> list;
	cout << "test iterators on this list" << endl;
	list.push_back('H');list.push_back('I');list.push_back('J');list.push_back('K');
	list.print(cout);
	cout << endl;
	SSLL<char> const const_list = list;			
	const_list.print(cout);						//discards qualifiers error
	//const_list.push_front('A'); /*Uncomment this to throw compile error, cannot modify const list*/
	
	
	cout << "make iter1 point to begin" << endl;
	SSLL<char>::iterator iter1 = list.begin();
	cout << "*iter1: " << *iter1 << endl;
	cout << "preincrement iter1" << endl;
	++iter1;
	cout << "*iter1: " << *iter1 << endl;
	cout << "make iter2 based off of iter1" << endl;
	SSLL<char>::iterator iter2(iter1);
	cout << "*iter2: " << *iter2 << endl;
	cout << endl;
	cout << "postincrement iter1" << endl;
	iter1++;
	cout << "*iter1: " << *iter1 << endl;
	cout << "*iter2: " << *iter2 << endl;
	cout << endl;
	
	
	cout << "set iter1 = iter2" << endl;
	iter1 = iter2;
	cout << "*iter1: " << *iter1 << endl;
	cout << "*iter2: " << *iter2 << endl;
	cout << endl;
	
	cout << "comparison test" << endl;
	bool test = iter1==(iter2);
	cout << "is iter1==iter2? " << test << endl;
	test = iter1!=(iter2);
	cout << "is iter1!=iter2? " << test << endl;
	cout << endl;
	
	cout << "constructing iter3 using iter1" << endl;
	SSLL<char>::iterator iter3(iter1);
	cout << "*iter3: " << *iter3 << endl;
	cout << endl;
	
	cout << "enhanced for loop using iterators" << endl;
	for( char& w : list){
		cout << w << "~";
	}
	
	cout << endl;
	
	cout << "\nmaking constant copy of list called c_list" << endl;
	const SSLL<char> c_list(list);
	cout << "making constant iterator c_iter1" << endl;
	SSLL<char>::const_iterator c_iter1 = c_list.begin();
	cout << "*c_iter1: " << *c_iter1 << endl;
	cout << "++c_iter1" << endl;
	++c_iter1;
	cout << "*c_iter1: " << *c_iter1 << endl;
	cout << "making constant iterator c_iter2 based off of c_iter1" << endl;
	SSLL<char>::const_iterator c_iter2(c_iter1);
	cout << "*c_iter1: " << *c_iter1 << endl;
	cout << "*c_iter2: " << *c_iter2 << endl;
	cout << "c_iter2++" << endl;
	c_iter2++;
	cout << "*c_iter2: " << *c_iter2 << endl;
	cout << "making c_iter1=c_iter2" << endl;
	c_iter1=c_iter2;
	cout << "*c_iter1: " << *c_iter1 << endl;
	cout << "*c_iter2: " << *c_iter2 << endl;
	
	cout << "\ntesting enhanced for loop on const list" << endl;
	for(auto w : c_list){
		cout << w << "~";
	}
	cout << endl;
	

	
	
	cout << "testing copy constructors" << endl;
	SSLL<char> ssit;
	cout << "\nmaking ssit list object and push_back A and B" << endl;
	ssit.push_back('A');
	ssit.push_back('B');
	ssit.push_back('C');
	cout << "print ssit: ";
	ssit.print(cout);
	
	SSLL<char> copyssit(ssit);
	cout << "\nmaking  a copy of ssit called copyssit list object" << endl;
	cout << "print copyssit: ";
	copyssit.print(cout);
	cout << "editing copyssit object" << endl;
	copyssit.push_front('Z');
	cout << "print copyssit: ";
	copyssit.print(cout);
	
	cout << "check that original was not modified" << endl;
	cout << "print ssit: ";
	ssit.print(cout);
	
	cout << "\ntesting copy assignment" << endl;
	cout << "making copyssit = ssit" << endl;
	copyssit = ssit;
	cout << "print copyssit: ";
	copyssit.print(cout);
	
	
	cout << "\ntesting move constructor on copyssit" << endl;
	copyssit.insert('X', 1);
	cout << "copyssit: ";
	copyssit.print(cout);
	SSLL<char> m_copyssit(std::move(copyssit));
	cout << "m_copyssit should have stolen the contents of copyssit" << endl;
	cout << "copyssit: ";
	copyssit.print(cout);
	cout << "m_copyssit: ";
	m_copyssit.print(cout);
	
	
	
	cout << "\ntesting move assignment on 2 lists: ssit & copyssit" << endl;
	cout << "edit copyssit" << endl;
	copyssit.insert('U', 0);
	cout << "copyssit: ";
	copyssit.print(cout);
	cout << "ssit: ";
	ssit.print(cout);
	cout << "\nmove copyssit's contents into ssit" << endl;
	cout << "ssit = copyssit" << endl;
	ssit = std::move(copyssit);
	cout << "ssit: ";
	ssit.print(cout);
	cout << "copyssit: ";
	copyssit.print(cout);
	
	cout << endl;cout << endl;
	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//end iterators test
	
	
	//github test
	SSLL<char> ght;
	ght.insert('A', 0);
	ght.print(cout);
	cout << "length(): " << ght.length() << endl;
	cout << endl;
	ght.insert('B', 1);
	ght.print(cout);
	cout << "length(): " << ght.length() << endl;
	cout << endl;
	ght.push_back('C');
	ght.print(cout);
	cout << "length(): " << ght.length() << endl;
	cout << endl;
	ght.push_front('D');
	ght.print(cout);
	cout << "length(): " << ght.length() << endl;
	cout << endl;
	cout << "test contains" << endl;
	cout << "does the list contain A?: " << ght.contains('A', &compare_int) << endl;
	cout << "does the list contain Z?: " << ght.contains('Z', &compare_int) << endl;
	
	
	cout << "testing push_back & display on chars" << endl;
	SSLL<char> c;
	cout << "inserting 'c' at position 0" << endl;
	c.insert('c', 0);
	c.print(cout);
	
	cout << "push front 'a'" << endl;
	c.push_front('a');
	c.print(cout);
	cout << "push back 'g'" << endl;
	c.push_back('g');
	c.print(cout);
	cout << "length: " << c.length() << endl;
	cout << "item_at(0): " << c.item_at(0) << endl;
	cout << "item_at(1): " << c.item_at(1) << endl;
	cout << "item_at(3): " << endl;
	try {
		c.item_at(3);
	}
	catch(runtime_error){
		cout << "error: position is outside of list"  << endl;
	}
	cout << "inserting 's' at position 2" << endl;
	c.insert('s', 2);
	c.print(cout);
	cout << "inserting 'o' at position 1" << endl;
	c.insert('o', 1);
	c.print(cout);
	cout << "inserting 'x' at position 5" << endl;
	c.insert('x', 5);
	c.print(cout);
	cout << "inserting 'y' at position 0" << endl;
	c.insert('y', 0);
	c.print(cout);
	cout << "length: " << c.length() << endl;
	
	cout << endl;cout << endl;

	SSLL<int> sspb;
	cout << "testing push_back on empty list: push_back(0)" << endl;
	sspb.push_back(0);
	sspb.print(cout);
	cout << "length: " << sspb.length() << endl;
	cout << "push_front 1-100" << endl;
	for(int i = 1; i <= 100; i++){
		sspb.push_front(i);
	}
	sspb.print(cout);
	cout << "length: " << sspb.length() << endl;
	cout << endl;cout << endl;
	
	SSLL<int> sspf;
	cout << "testing push_front on empty list: push_front(0)" << endl;
	sspf.push_front(0);
	sspf.print(cout);
	cout << "length: " << sspf.length() << endl;
	cout << "push_back 1-100" << endl;
	for(int i = 1; i <= 100; i++){
		sspf.push_back(i);
	}
	sspf.print(cout);
	cout << "length: " << sspf.length() << endl;
	cout << "inserting 33 at position 4" << endl;
	sspf.insert(33, 4);
	sspf.print(cout);
	cout << "length: " << sspf.length() << endl;
	
	cout << endl;cout << endl;
	
	SSLL<int> ssis;
	cout << "insert element i at position i (i = 0 - 66)" << endl;
	for(int i = 0; i <= 66; i++){
		ssis.insert(i, i);
	}
	ssis.print(cout);
	cout << "length: " << ssis.length() << endl;
	
	cout << "\nreplace element at position 10 with 22" << endl;
	cout << "replace(22, 10): " << ssis.replace(22, 10) << endl;
	ssis.print(cout);
	cout << "length: " << ssis.length() << endl;
	
	cout << "\nreplace element at position 34 with 2" << endl;
	cout << "replace(2, 34): " << ssis.replace(2, 34) << endl;
	ssis.print(cout);
	cout << "length: " << ssis.length() << endl;
	
	cout << "\nremoving element at position 66" << endl;
	cout << "remove(66): " << ssis.remove(66) << endl;
	ssis.print(cout);
	cout << "length: " << ssis.length() << endl;
	
	cout << "\nremoving element at position 20" << endl;
	cout << "remove(20): " << ssis.remove(20) << endl;
	ssis.print(cout);
	cout << "length: " << ssis.length() << endl;
	
	cout << "\nremoving element at position 0" << endl;
	cout << "remove(0): " << ssis.remove(0) << endl;
	ssis.print(cout);
	cout << "length: " << ssis.length() << endl;
	
	cout << "\nremoving element at position 0" << endl;
	cout << "remove(0): " << ssis.remove(0) << endl;
	ssis.print(cout);
	cout << "length: " << ssis.length() << endl;
	
	cout << "\npop back" << endl;
	cout << "pop_back(): " << ssis.pop_back() << endl;
	ssis.print(cout);
	cout << "length: " << ssis.length() << endl;
	
	cout << "\npop front" << endl;
	cout << "pop_front(): " << ssis.pop_front() << endl;
	ssis.print(cout);
	cout << "length: " << ssis.length() << endl;
	
	cout << "\npop front" << endl;
	cout << "pop_front(): " << ssis.pop_front() << endl;
	ssis.print(cout);
	cout << "length: " << ssis.length() << endl;
	
	cout << "\ntesting contains" << endl;
	cout << "Does the list contain 7: " << ssis.contains(7, &compare_int) << endl;
	cout << "Does the list contain 22: " << ssis.contains(22, &compare_int) << endl;
	cout << "Does the list contain 77: " << ssis.contains(77, &compare_int) << endl;
	
	cout << "\npeek_back(): " << ssis.peek_back() << endl;
	cout << "peek_front(): " << ssis.peek_front() << endl;
	
	cout << "\ntesting clear on previous list" << endl;
	ssis.clear();
	ssis.print(cout);
	cout << "length: " << ssis.length() << endl;
	
	cout << "\ntesting clear on previous list again" << endl;
	ssis.clear();
	ssis.print(cout);
	cout << "length: " << ssis.length() << endl;
	
	cout << endl;cout << endl;
	
	SSLL<int> ssrem;
	cout << "testing remove on list with one element" << endl;
	ssrem.push_back(5);
	ssrem.print(cout);
	cout << "remove element at position 0" << endl;
	cout << "remove(0): " << ssrem.remove(0) << endl;
	ssrem.print(cout);
	cout << "length: " << ssrem.length() << endl;
	cout << "\ntesting pop_back on list with one element" << endl;
	ssrem.push_back(4);
	ssrem.print(cout);
	cout << "pop_back(): " << ssrem.pop_back() << endl;
	ssrem.print(cout);
	cout << "length: " << ssrem.length() << endl;
	cout << "\ntesting pop_front on list with one element" << endl;
	ssrem.push_back(7);
	ssrem.print(cout);
	cout << "pop_front(): " << ssrem.pop_front() << endl;
	ssrem.print(cout);
	cout << "length: " << ssrem.length() << endl;
	
	cout << endl; cout << endl;
	
	SSLL<int> sscon;
	cout << "testing contents" << endl;
	cout << "push_back 0-50" << endl;
	for(int i = 0; i <= 50; i++){
		sscon.push_back(i);
	}
	sscon.print(cout);
	cout << "length: " << sscon.length() << endl;
	int * ssarr = sscon.contents();
	cout << "printing contents" << endl;
	for(int i = 0; i <= 50; i++){
		cout << ssarr[i] << "_";
	}
	delete[] ssarr;
	cout << endl;
	
	cout << "\nedit original list and make new contents array" << endl;
	cout << "push_front 11" << endl;
	sscon.push_front(11);
	cout << "make new contents and print" << endl;
	int * ssarr2 = sscon.contents();
	for(int i = 0; i <= sscon.length()-1; i++){
		cout << ssarr2[i] << "_";
	}
	delete[] ssarr2;
	cout << endl;cout << endl;
	return 0;
}





//======this is the function parameter passed for contains()====
template <typename E>
bool compare_int(const E& element, const E& value){
	//cout << "comparing " << element << "with " << value << endl;
	if(element == value){
		return true;
	}
	else
		return false;
}
//==============================================================