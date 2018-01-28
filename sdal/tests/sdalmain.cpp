#include <iostream>
#include <stdexcept>
#include "List.h"
#include "SDAL.h"

using namespace std;
using namespace cop3530;


//======this is the function parameter passed for contains()====
template <typename E>
bool compare_int(const E& element, const E& value);
//==============================================================

int main(){
	cout << "testing iterators" << endl;
	SDAL<char> sdit(5);
	sdit.push_back('A');
	sdit.push_back('C');
	sdit.insert('B', 1);
	sdit.insert('D', 3);
	sdit.print(cout);
	
	const SDAL<char> csdit(sdit);
	//csdit.pop_back(); /*Uncomment this to throw compile error, cannot modify const list*/
	
	cout << "\nmake iterator callded sditer1" << endl;
	SDAL<char>::iterator sditer1 = sdit.begin();
	cout << "*sditer1: " << *sditer1 << endl;
	cout << "preincrement sditer1" << endl;
	++sditer1;
	cout << "*sditer1: " << *sditer1 << endl;
	cout << "postincrement sditer1" << endl;
	sditer1++;
	cout << "*sditer1: " << *sditer1 << endl;
	
	cout << "\nmake another iterator called sditer2" << endl;
	SDAL<char>::iterator sditer2 = sdit.begin();
	cout << "*sditer2: " << *sditer2 << endl;
	int sdintbool = sditer1 != sditer2;
	cout << "Does sditer1 != sditer2?: " << sdintbool << endl;
	cout << "make sditer1 = sditer2" << endl;
	sditer1 = sditer2;
	cout << "*sditer1: " << *sditer1 << endl;
	sdintbool = sditer1 == sditer2;
	cout << "Does sditer1 == sditer2?: " << sdintbool << endl;
	
	cout << "\nmake iterator callded sditerbeg point to beginning" << endl;
	SDAL<char>::iterator sditerbeg = sdit.begin();
	cout << "\nmake iterator callded sditerend point to end" << endl;
	SDAL<char>::iterator sditerend = sdit.end();
	
	cout << "\n test copy constructor" << endl;
	SDAL<char>::iterator copy_sditerbeg(sditerbeg);
	sdintbool = copy_sditerbeg == sditerbeg;
	cout << "Does sditerbeg == copy_sditerbeg?: " << sdintbool << endl;
	cout << "\nlooping from sditerbeg to sditerend" << endl;
	
	for(; sditerbeg != sditerend; ++sditerbeg){
		cout << *sditerbeg << " ";
	}
	cout << endl;
	cout << "\ntesting const iterators" << endl;
	cout << "making a const list copy of sdit" << endl;
	const SDAL<char> const_sdit(sdit);
	cout << "making const iterators const_sditerbeg & const_sditerend" << endl;
	SDAL<char>::const_iterator const_sditerbeg = const_sdit.begin();
	SDAL<char>::const_iterator const_sditerend = const_sdit.end();
	cout << "*const_sditerbeg: " << *const_sditerbeg << endl;
	cout << "preincrementing const_sditerbeg" << endl;
	++const_sditerbeg;
	cout << "*const_sditerbeg: " << *const_sditerbeg << endl;
	cout << "making cc_sditerbeg based off of const_sditerbeg" << endl;
	SDAL<char>::const_iterator cc_sditerbeg(const_sditerbeg);
	cout << "*cc_sditerbeg: " << *cc_sditerbeg << endl;
	cout << "*const_sditerbeg: " << *const_sditerbeg << endl;
	cout << "post incrementing cc_sditerbeg" << endl;
	cc_sditerbeg++;
	cout << "*cc_sditerbeg: " << *cc_sditerbeg << endl;
	cout << "*const_sditerbeg: " << *const_sditerbeg << endl;
	cout << "making const_sditerbeg = cc_sditerbeg " << endl;
	const_sditerbeg=cc_sditerbeg;
	cout << "*cc_sditerbeg: " << *cc_sditerbeg << endl;
	cout << "*const_sditerbeg: " << *const_sditerbeg << endl;
	
	cout << "\ntesting enhanced for loop on const list with const iterators" << endl;
	for(auto w : const_sdit){
		cout << w <<  "~";
	}
	cout << endl;
	cout << "\ntesting iterator copy constructor" << endl;
	SDAL<char>::iterator sditersrc = sdit.begin();
	++sditersrc;
	cout << "making new iterator called copy_sditersrc based off of sditersrc" << endl;
	cout << "*sditersrc: " << *sditersrc << endl;
	SDAL<char>::iterator copy_sditersrc(sditersrc);
	cout << "*copy_sditersrc: " << *copy_sditersrc << endl;
	cout << "++copy_sditersrc" << endl;
	++copy_sditersrc;
	cout << "*copy_sditersrc: " << *copy_sditersrc << endl;
	
	cout << "\ntesting iterator assignment" << endl;
	cout << "making sditersrc = copy_sditersrc" << endl;
	sditersrc=copy_sditersrc;
	cout << "*copy_sditersrc: " << *copy_sditersrc << endl;
	cout << "*sditersrc: " << *sditersrc << endl;
	
	
	cout << "\ntesting enhanced for loop on non const SDAL iterators" << endl;
	for(auto w : sdit){
		cout << w << "~";
	}
	cout << endl;
	
	cout << "\ntesting copy constructor" << endl;
	cout << "\ncreate default sdal list called sddef" << endl;
	SDAL<char> sddef;
	sddef.push_back('U');
	sddef.push_back('T');
	sddef.insert('L', 1);
	cout << "print sddef: ";
	sddef.print(cout);
	
	cout << "\ncreate a new sdal list called copy_sddef using copy constructor based off sddef" << endl;
	SDAL<char> copy_sddef(sddef);
	cout << "print copy_sddef: " ;
	copy_sddef.print(cout);
	cout << "edit copy_sddef" << endl;
	cout << "pop_front: " << copy_sddef.pop_front() << endl;
	cout << "print copy_sddef: " ;
	copy_sddef.print(cout);
	
	cout << "\ntesting copy assignment on sddef & copy_sddef" << endl;
	cout << "print copy_sddef: " ;
	copy_sddef.print(cout);
	cout << "print sddef: " ;
	sddef.print(cout);
	cout << "\ngoing to make sddef = copy_sddef" << endl;
	sddef = copy_sddef;
	cout << "print copy_sddef: " ;
	copy_sddef.print(cout);
	cout << "print sddef: " ;
	sddef.print(cout);
	
	cout << "\ntesting move constructor" << endl;
	cout << "make new list m_sddef that takes the contents from sddef" << endl;
	SDAL<char> m_sddef(std::move(sddef));
	cout << "print sddef: " ;
	sddef.print(cout);
	cout << "print m_sddef: " ;
	m_sddef.print(cout);
	
	cout << "\ntesting move assignment" << endl;
	cout << "print sddef: " ;
	sddef.print(cout);
	cout << "print copy_sddef: " ;
	copy_sddef.print(cout);
	cout << "make sddef = copy_sddef" << endl;
	sddef = std::move(copy_sddef);
	cout << "print sddef: " ;
	sddef.print(cout);
	cout << "print copy_sddef: " ;
	copy_sddef.print(cout);
	
	
	cout << endl;cout << endl;
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	
	cout << "testing push_front() on list of size 5" << endl;
	SDAL<int> sdpf(5);
	cout << "push_front(11)" << endl;
	sdpf.push_front(11);
	sdpf.print(cout);
	cout << "length: " << sdpf.length() << endl;
	
	
	cout << "push_front() numbers 10,9,8, and 7" << endl;
	sdpf.push_front(10);sdpf.push_front(9);sdpf.push_front(8);sdpf.push_front(7);
	sdpf.print(cout);
	cout << "length: " << sdpf.length() << endl;
	
	cout << "push_front(20)" << endl;
	sdpf.push_front(20);
	sdpf.print(cout);

	cout << "\n";
	cout << "\n";

	cout << "testing push_front on default size SDAL (size of 50)" << endl;
	SDAL<int> dsdpf;
	cout << "push_front 1-49" << endl;
	for(int i = 0; i <= 48; i++){
		dsdpf.push_front(i+1);
	}
	dsdpf.print(cout);
	cout << "length: " << dsdpf.length() << endl;
	cout << "push_front(50)" << endl;
	dsdpf.push_front(50);
	dsdpf.print(cout);
	cout << "length: " << dsdpf.length() << endl;
	cout << "array should resize to 150% of original size (50) after push_front(51)" << endl;
	cout << "push_front(51)" << endl;
	dsdpf.push_front(51);
	dsdpf.print(cout);
	cout << "length: " << dsdpf.length() << endl;
	
	cout << "\n";
	cout << "\n";

	cout << "testing push_back() on list of size 4" << endl;
	SDAL<int> sdpb(4);
	cout << "push back 8" << endl;
	sdpb.push_back(8);
	sdpb.print(cout);
	cout << "length is: " << sdpb.length() << endl;
	cout << "\npush_back 1, 3, 12" << endl;
	sdpb.push_back(1);sdpb.push_back(3);sdpb.push_back(12);
	sdpb.print(cout);
	cout << "length is: " << sdpb.length() << endl;
	cout << "\npush_back 14" << endl;
	sdpb.push_back(14);
	sdpb.print(cout);
	cout << "length is: " << sdpb.length() << endl;
	cout << "\npush_front 11" << endl;
	sdpb.push_front(11);
	sdpb.print(cout);
	cout << "length is: " << sdpb.length() << endl;
	cout << "\npush_front 55" << endl;
	sdpb.push_front(55);
	sdpb.print(cout);
	cout << "length is: " << sdpb.length() << endl;
	cout << "\ninserting at end of list" << endl;
	cout << "insert 20 at position 7" << endl;
	sdpb.insert(20, 7);
	sdpb.print(cout);
	cout << "length is: " << sdpb.length() << endl;
	cout << "\ninsert 88 at position 4" << endl;
	sdpb.insert(88, 4);
	sdpb.print(cout);
	cout << "length is: " << sdpb.length() << endl;
	cout << "\ninsert 72 at position 0" << endl;
	sdpb.insert(72, 0);	
	sdpb.print(cout);
	cout << "length is: " << sdpb.length() << endl;
	
	
	cout << "\n";
	cout << "\n";

	cout << "testing replace" << endl;
	SDAL<int> sdrep(5);
	sdrep.push_back(44);sdrep.push_front(32);sdrep.push_back(4);sdrep.push_back(87);sdrep.push_front(30);
	sdrep.print(cout);
	cout << "length is: " << sdrep.length() << endl;
	cout << "replace element at position 2 with 11: " << sdrep.replace(11,2) << endl;
	sdrep.print(cout);
	cout << "length is: " << sdrep.length() << endl;
	cout << "replace element at position 0 with 3: " << sdrep.replace(3,0) << endl;
	sdrep.print(cout);
	cout << "length is: " << sdrep.length() << endl;
	cout << "replace element at position 4 with 100: " << sdrep.replace(100,4) << endl;
	sdrep.print(cout);
	cout << "length is: " << sdrep.length() << endl;
	cout << "trying to replace element at position 67 with 20" << endl;
	try{
		sdrep.replace(20, 67);
	}
	catch(runtime_error){
		cout << "error: position exceeds list length" << endl;
	}
	
	cout << "\n";
	cout << "\n";
	
	
	cout << "testing pop_back and resizing condition to make list smaller" << endl;
	SDAL<int> sdpopb;
	cout << "\npush back 100 elements and make the max size now 112" << endl;
	for(int i = 1; i <= 100; i++){
		sdpopb.push_back(i);
	}
	sdpopb.print(cout);
	cout << "length is: " << sdpopb.length() << endl;
	cout << "\npopback 44 times (leave 56 elements in list)" << endl;
	for(int i = 1; i <= 44; i++){
		sdpopb.pop_back();
	}
	sdpopb.print(cout);
	cout << "length is: " << sdpopb.length() << endl;
	cout << "\nmax size is 112 and the list will shrink in size" << endl;
	cout << "if max size is >= twice the starting capacity (50) and if list is filled to less than half of max size" << endl;
	cout << "max size is 112 and half of 112 is 56, so once the 56 element is popped" << endl;
	cout << "the list should resize to 75% of maxsize which is 84" << endl;
	cout << "\npop_back(): " << sdpopb.pop_back() << endl;
	sdpopb.print(cout);
	cout << "length is: " << sdpopb.length() << endl;
	
	cout << "\npop_back(): " << sdpopb.pop_back() << endl;
	sdpopb.print(cout);
	cout << "length is: " << sdpopb.length() << endl;
	cout << "\npop_front(): " << sdpopb.pop_front() << endl;
	sdpopb.print(cout);
	cout << "length is: " << sdpopb.length() << endl;
	
	cout << "\n";
	cout << "\n";
	
	cout << "testing pop_front and resizing condition to make list smaller (same as above but w/ pop_front)" << endl;
	SDAL<int> sdpoppf;
	
	cout << "\npush back 100 elements and make the max size now 112" << endl;
	for(int i = 1; i <= 100; i++){
		sdpoppf.push_back(i);
	}
	sdpoppf.print(cout);
	cout << "length is: " << sdpoppf.length() << endl;
	cout << "\npopfront 44 times (leave 56 elements in list as half of 112 is 56)" << endl;
	for(int i = 1; i <= 44; i++){
		sdpoppf.pop_front();
	}
	sdpoppf.print(cout);
	cout << "length is: " << sdpoppf.length() << endl;
	cout << "\npop_front once more to resize list" << endl;
	cout << "pop_front(): " << sdpoppf.pop_front() << endl;
	sdpoppf.print(cout);
	cout << "length is: " << sdpoppf.length() << endl;
	cout << "pop_front(): " << sdpoppf.pop_front() << endl;
	sdpoppf.print(cout);
	cout << "length is: " << sdpoppf.length() << endl;
	cout << "pop_back(): " << sdpoppf.pop_back() << endl;
	sdpoppf.print(cout);
	cout << "length is: " << sdpoppf.length() << endl;
	
	cout << "\ntesting remove" << endl;
	cout << "remove element at position 4: " << sdpoppf.remove(4) << endl;
	sdpoppf.print(cout);
	cout << "length is: " << sdpoppf.length() << endl;
	
	
	cout << "\n";
	cout << "\n";
	
	cout << "testing remove and resizing condition to make list smaller (same as above but w/ remove)" << endl;
	SDAL<int> sdremc;
	cout << "\npush back 100 elements and make the max size now 112" << endl;
	for(int i = 1; i <= 100; i++){
		sdremc.push_back(i);
	}
	sdremc.print(cout);
	cout << "length is: " << sdremc.length() << endl;
	cout << "\nremove 44 times (leave 56 elements in list) \nremove element at i (i = 0-43)" << endl;
	for(int i = 0; i <= 43; i++){
		sdremc.remove(i);
	}
	sdremc.print(cout);
	cout << "length is: " << sdremc.length() << endl;
	cout << "\nremove once more at i = 1 to make array resize" << endl;
	cout << "remove(1): " << sdremc.remove(1) << endl;
	sdremc.print(cout);
	cout << "length is: " << sdremc.length() << endl;

	cout << "\n";
	cout << "\n";

	cout << "testing remove" << endl;
	SDAL<int> sdrem(5);
	sdrem.push_front(5);sdrem.push_front(4);sdrem.push_front(3);sdrem.push_front(2);sdrem.push_front(1);
	sdrem.print(cout);
	cout << "remove(0): " <<sdrem.remove(0) << endl;
	sdrem.print(cout);
	cout << "remove(3): " << sdrem.remove(3) << endl;
	sdrem.print(cout);
	cout << "remove(1): " << sdrem.remove(1) << endl;
	sdrem.print(cout);
	cout << "adding more elements" << endl;
	sdrem.push_front(11);sdrem.push_front(7);sdrem.push_front(98);
	sdrem.print(cout);
	cout << "remove(2): " << sdrem.remove(2) << endl;
	sdrem.print(cout);


	cout << "\n";
	cout << "\n";

	cout << "testing item_at on previous list" << endl;
	cout << "item_at(3): " << sdrem.item_at(3) << endl;
	cout << "item_at(1): " << sdrem.item_at(1) << endl;
	cout << "item_at(0): " << sdrem.item_at(0) << endl;
	cout << "trying item_at(23)" << endl;
	try{
		cout << "item_at(23): " << sdrem.item_at(23) << endl;
	}
	catch(runtime_error){
		cout << "error: position exceeds list length" << endl;
	}

	cout << "\n";
	cout << "\n";
	
	cout << "testing peek_front and peek_back" << endl;
	SDAL<int> sdpkb(5);
	cout << "try peek_front and peek_back on empty list" << endl;
	try{
		sdpkb.peek_front();
	}
	catch(runtime_error){
		cout << "error: empty list, nothing to peek" << endl;
	}
	try{
		sdpkb.peek_back();
	}
	catch(runtime_error){
		cout << "error: empty list, nothing to peek" << endl;
	}
	sdpkb.push_back(3);
	sdpkb.print(cout);
	cout << "peek_front(): " << sdpkb.peek_front() << endl;
	cout << "peek_back(): " << sdpkb.peek_back() << endl;
	sdpkb.push_back(4);sdpkb.push_back(31);sdpkb.push_back(9);
	sdpkb.print(cout);
	cout << "peek_front(): " << sdpkb.peek_front() << endl;
	cout << "peek_back(): " << sdpkb.peek_back() << endl;

	cout << "\n";
	cout << "\n";

	cout << "testing contents" << endl;
	int * sdcont = sdpkb.contents();
	for(int i = 0; i<4; i++){
	cout << sdcont[i] << "_";
	}
	cout <<  endl;
	delete[] sdcont;
	cout << "push_front(100) to same list and test contents again" << endl;
	sdpkb.push_front(100);
	int * sdcont2 = sdpkb.contents();
	for(int i = 0; i<=sdpkb.length()-1; i++){
		cout << sdcont2[i] << "_";
	}
	delete[] sdcont2;
	cout << endl;
	
	cout << "\n";
	cout << "\n";

	cout << "testing contains" << endl;
	cout << "contains 4: " << sdpkb.contains(4, &compare_int) << endl;
	cout << "contains 99: " << sdpkb.contains(99, &compare_int) << endl;
	cout << "contains 9: " << sdpkb.contains(9, &compare_int) << endl;
	cout << "contains 3: " << sdpkb.contains(3, &compare_int) << endl;

	cout << "\n";
	cout << "\n";

	cout << "testing clear" << endl;
	sdpkb.print(cout);
	cout << "length is: " << sdpkb.length() << endl;
	sdpkb.clear();
	cout << "call clear()\nprinting list" << endl;
	sdpkb.print(cout);
	cout << "length is: " << sdpkb.length() << endl;
	
	cout << "\n";
	cout << "\n";
	
	
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