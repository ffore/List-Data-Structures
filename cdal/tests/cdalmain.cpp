#include <iostream>
#include <stdexcept>
#include "List.h"
#include "CDAL.h"

using namespace std;
using namespace cop3530;


//======this is the function parameter passed for contains()====
template <typename E>
bool compare_int(const E& element, const E& value);
//==============================================================

int main(){
	cout << "testing iterators" << endl;
	CDAL<int> cditl;
	for(int i = 0; i<=99; i++){
		cditl.insert(i,i);
	}
	
	const CDAL<int> ccditl(cditl);
	//ccditl.pop_back(); /*Uncomment this to throw compile error, cannot modify const list*/
	
	cout << "printing cditl" << endl;
	cditl.test_print(cout);
	CDAL<int>::iterator cditer1 = cditl.begin();
	cout << "*cditer1: " << *cditer1 << endl;
	cout << "\npreincrement ++cditer1" << endl;
	++cditer1;
	cout << "*cditer1: " << *cditer1 << endl;
	
	cout << "\npostincrement cditer1++" << endl;
	cditer1++;
	cout << "*cditer1: " << *cditer1 << endl;
	
	cout << endl;cout << endl;
	
	cout << "testing copy constructor for iterators" << endl;
	cout << "making cditer1_copy based off of cditer1" << endl;
	CDAL<int>::iterator cditer1_copy(cditer1);
	cout << "*cditer1: " << *cditer1 << endl;
	cout << "*cditer1_copy: " << *cditer1_copy << endl;
	
	cout << "\ntesting assignment of 2 iterators" << endl;
	cout << "increment cditer1_copy" << endl;
	++cditer1_copy;
	cout << "*cditer1: " << *cditer1 << endl;
	cout << "*cditer1_copy: " << *cditer1_copy << endl;
	cout << "make cditer1_copy = cditer1" << endl;
	cditer1_copy=cditer1;
	cout << "*cditer1: " << *cditer1 << endl;
	cout << "*cditer1_copy: " << *cditer1_copy << endl;
	
	cout << endl;cout << endl;
	
	cout << "testing loop from iterator at beg != to iterator at end" << endl;
	CDAL<int>::iterator cditer2 = cditl.begin();
	CDAL<int>::iterator cditer3 = cditl.end();
	while(cditer2 != cditer3){
		cout << *cditer2 << " ";
		++cditer2;
	}
	
	cout << "\ntesting enhanced for loop on non const CDAL iterators" << endl;
	for(auto w : cditl){
		cout << w << "~";
	}
	
	cout << endl;
	
	cout << "\ntesting const iterators " << endl;
	const CDAL<int> con_cditl(cditl);
	CDAL<int>::const_iterator con_cditer2 = con_cditl.begin();
	++con_cditer2;
	CDAL<int>::const_iterator con_cditer3(con_cditer2);
	
	cout << "\nmade 2 const iterators: con_cditer2 & con_cditer3" << endl;
	cout << "*con_cditer2: " << *con_cditer2 << endl;
	cout << "*con_cditer3: " << *con_cditer3 << endl;
	
	if(con_cditer2 == con_cditer3){
		cout << "con_cditer2 == con_cditer3" << endl;
	}
	
	cout << "postincrement con_cditer2" << endl;
	con_cditer2++;
	if(con_cditer2 != con_cditer3){
		cout << "con_cditer2 != con_cditer3" << endl;
	}
	cout << "*con_cditer2: " << *con_cditer2 << endl;
	cout << "*con_cditer3: " << *con_cditer3 << endl;

	cout << "testing assignment of 2 iterators" << endl;
	cout << "con_cditer2 = con_cditer3" << endl;
	con_cditer2 = con_cditer3;
	cout << "*con_cditer2: " << *con_cditer2 << endl;
	cout << "*con_cditer3: " << *con_cditer3 << endl;
	
	cout << endl;

	CDAL<int>::const_iterator con_cdbeg = con_cditl.begin();
	CDAL<int>::const_iterator con_cdend = con_cditl.end();
	
	cout << "\ntesting while loop on const iterators" << endl;
	while(con_cdbeg != con_cdend){
		cout << *con_cdbeg << "-";
		++con_cdbeg;
	}
	cout << endl;
	
	cout << "testing enhanced for loop on const iterators" << endl;
	for(auto w : con_cditl){
		cout << w << "~";
	}
	cout << endl;cout << endl;
	
	cout << "testing iterators on empty list" << endl;
	CDAL<char> cd_emp;
	CDAL<char>::iterator cd_emp1 = cd_emp.begin();
	CDAL<char>::iterator cd_emp2 = cd_emp.end();
	cout << "printing iterator with enhanced for loop on empty list" << endl;
	for(auto w : cd_emp){
		cout << w << "~";
	}
	
	cout << endl;cout << endl;
	//big five
	cout << "testing copy constructor" << endl;
	CDAL<int> cdcc;
	for(int i = 0; i <= 55; i++){
		cdcc.push_back(i);
	}
	cout << "making a copy of cdcc called copy_cdcc" << endl;
	cout << "cdcc: "; 
	cdcc.print(cout);
	CDAL<int> copy_cdcc(cdcc);
	cout << "copy_cdcc: "; 
	copy_cdcc.print(cout); 
	cout << "\nmodify copy_cdcc (push_front(100))" << endl;
	copy_cdcc.push_front(100);
	cout << "copy_cdcc: "; 
	copy_cdcc.print(cout); 
	cout << "\ncdcc = copy_cdcc" << endl;
	cdcc=copy_cdcc;
	cout << "cdcc: "; 
	cdcc.print(cout);
	cout << "copy_cdcc: "; 
	copy_cdcc.print(cout); 
	
	cout << endl;cout << endl;
	cout << "testing move constructor" << endl;
	cout << "make new CDAL object called m_cdcc and have it steal cdcc's contents" << endl;
	cout << "cdcc: "; 
	cdcc.print(cout);
	cout << "\ncreated m_cdcc now" << endl;
	CDAL<int> m_cdcc(std::move(cdcc));
	cout << "m_cdcc: "; 
	m_cdcc.print(cout);
	cout << "cdcc: "; 
	cdcc.print(cout);
	
	cout << endl;cout << endl;
	
	cout << "testing move assignment" << endl;
	cout << "modify m_cdcc" << endl;
	for(int i = 0; i<=9; i++){
		m_cdcc.pop_front();
	}
	cout << "m_cdcc: "; 
	m_cdcc.print(cout);
	cout << "have copy_cdcc steal m_cdcc's information" << endl;
	cout << "\ncopy_cdcc=m_cdcc" << endl;
	copy_cdcc=(std::move(m_cdcc));
	cout << "copy_cdcc: "; 
	copy_cdcc.print(cout);
	cout << "m_cdcc: "; 
	m_cdcc.print(cout);
	
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	cout << "\ntesting push_back and \nshowing that every 50 inputs, a new node is allocated\n" << endl;
	CDAL<int> cdpb;
	cout << "pushing back numbers 1-103\nnumbers 1-50 will be stored in default node # 0\nThe rest should be stored in 2 more nodes chained to first" << endl;
	for(int i = 1; i <= 103; i++){
		cdpb.push_back(i);
	}
	cout << "\n";
	cdpb.test_print(cout);
	
	cout << "\ntesting print function" << endl;
	cdpb.print(cout);
	
	cout << "testin item_at" << endl; 
	cout << "item at position 0: " << cdpb.item_at(0) << endl;
	cout << "item at position 14: " << cdpb.item_at(14) << endl;
	cout << "item at position 60: " << cdpb.item_at(60) << endl;
	
	cout << "\n";cout << "\n";
	
	cout << "testing push_front" << endl;
	CDAL<int> cdpf;
	cout << "pushing front 0 to 103" << endl;
	for(int i = 0; i <= 103; i++){
		cdpf.push_front(i);
	}
	cdpf.test_print(cout);
	
	cout << "\ntesting print function" << endl;
	cdpf.print(cout);
	
	cout << "\n";cout << "\n";
	
	cout << "testing push_front and push_back" << endl;
	CDAL<int> cdpf2;
	cout << "push_front(2)" << endl;
	cdpf2.push_front(2);
	cdpf2.test_print(cout);
	cout << "\npush_back(55)" << endl;
	cdpf2.push_back(55);
	cdpf2.test_print(cout);
	cout << "\npush_back(9)" << endl;
	cdpf2.push_back(9);
	cdpf2.test_print(cout);
	cout << "\npush_front(11)" << endl;
	cdpf2.push_front(11);
	cdpf2.test_print(cout);
	
	cout << "\ntesting print function" << endl;
	cdpf2.print(cout);
	cout << "\n";cout << "\n";
	
	cout << "testing insert" << endl;
	CDAL<int> cdi;
	cout << "pushing back 0-99" << endl;
	for(int i = 0; i <= 99; i++){
		cdi.push_back(i);
	}
	cdi.test_print(cout);
	cout << "\ninsert 99 at position 12" << endl;
	cdi.insert(99,12);
	cdi.test_print(cout);
	cout << "\ninsert 88 at position 74" << endl;
	cdi.insert(88,74);
	cdi.test_print(cout);
	cout << "\ninsert 111 at position 29" << endl;
	cdi.insert(111,29);
	cdi.test_print(cout);
	cout << "\ntesting print function" << endl;
	cdi.print(cout);
	
	CDAL<int> cdit;
	cout << "\ntesting insert again on new list" << endl;
	cdit.push_back(1);cdit.push_back(2);cdit.push_back(4);cdit.push_back(5);
	cdit.test_print(cout);
	cout << "\ninsert 3 at position 2" << endl;
	cdit.insert(3, 2);
	cdit.test_print(cout);
	cout << "\ninsert 33 at position 0" << endl;
	cdit.insert(33, 0);
	cdit.test_print(cout);
	cout << "\ninsert 67 at position 5" << endl;
	cdit.insert(67, 5);
	cdit.test_print(cout);
	cout << "\ninsert 93 at position 7" << endl;
	cdit.insert(93, 7);
	cdit.test_print(cout);
	cout << "\ninsert 55 at position 10" << endl;
	try{
		cdit.insert(55, 10);
	}
	catch(runtime_error){
		cout << "error: position is outside of length of list" << endl;
	}
	cdit.test_print(cout);
	cout << "\ntesting print function" << endl;
	cdit.print(cout);
	
	cout << "\n";cout << "\n";
	
	CDAL<int> cdpopb;
	cout << "testing pop_back on full list" << endl;
	for(int i = 0; i <= 102; i++){
		cdpopb.push_back(i);
	}
	cdpopb.test_print(cout);
	cout << "\npop_back 53 times" << endl;
	for(int i = 0; i < 53; i++){
		cdpopb.pop_back();
	}
	cdpopb.test_print(cout);
	cout << "\npop_back(): " << cdpopb.pop_back() << endl;
	cdpopb.test_print(cout);
	cout << "\ntesting print function" << endl;
	cdpopb.print(cout);
	
	cout << "\n";cout << "\n";
	
	CDAL<int> cdpopf;
	cout << "testing pop_front on full list" << endl;
	for(int i = 0; i <= 150; i++){
		cdpopf.push_back(i);
	}
	cdpopf.test_print(cout);
	cout << "\npop_front(): " << cdpopf.pop_front() << endl;
	cdpopf.test_print(cout);
	cout << "\nagain pop_front(): " << cdpopf.pop_front() << endl;
	
	cdpopf.test_print(cout);
	cout << "\ntesting print function" << endl;
	cdpopf.print(cout);
	
	cout << "\n";cout << "\n";
	
	
	cout << "testing remove" << endl;
	CDAL<int> cdrem;
	cout << "\npushing back 0-51" << endl;
	for(int i = 0; i <= 51; i++){
		cdrem.push_back(i);
	}
	cdrem.test_print(cout);
	cout << "\nremove element at position 50: " << cdrem.remove(50) << endl;
	cdrem.test_print(cout);
	cout << "\nremove element at position 22: " << cdrem.remove(22) << endl;
	cdrem.test_print(cout);
	cout << "\nremove element at position 49: " << cdrem.remove(49) << endl;
	cdrem.test_print(cout);
	cout << "\ntesting print function" << endl;
	cdrem.print(cout);
	
	cout << "\n";cout << "\n";
	
	
	cout << "\ntesting remove on different list" << endl;
	CDAL<int> cdrem2;
	cdrem2.push_back(1);cdrem2.push_back(99);cdrem2.push_back(2);cdrem2.push_back(3);cdrem2.push_back(21);cdrem2.push_back(4);
	cdrem2.test_print(cout);
	cout << "remove at position 1: " << cdrem2.remove(1) << endl;
	cdrem2.test_print(cout);
	cout << "remove at position 3: " << cdrem2.remove(3) << endl;
	cdrem2.test_print(cout);
	cout << "\ntesting pop_back and pop_front on previous list" << endl;
	cout << "pop_back is: " << cdrem2.pop_back() << endl;
	cdrem2.test_print(cout);
	cout << "pop_front is: " << cdrem2.pop_front() << endl;
	cdrem2.test_print(cout);
	cout << "pop_front is: " << cdrem2.pop_front() << endl;
	cdrem2.test_print(cout);
	cout << "pop_back is: " << cdrem2.pop_back() << endl;
	cdrem2.test_print(cout);
	try{
	cout << "pop_back is: " << cdrem2.pop_back() << endl;
	cdrem2.test_print(cout);
	}
	catch(runtime_error){
		cout << "error: can't pop_back on empty list" << endl;
	}
	try{
	cout << "pop_front is: " << cdrem2.pop_front() << endl;
	cdrem2.test_print(cout);
	}
	catch(runtime_error){
		cout << "error: can't pop_front on empty list" << endl;
	}
	cout << "\ntesting print function" << endl;
	cdrem2.print(cout);
	
	cout << "\n";cout << "\n";
	///////////////////////////////////////here
	
	cout << "testing list shrinkage" << endl;
	cout << "push in so 5 nodes are allocated" << endl;
	CDAL<int> cdst;
	for(int i = 0; i <=249; i++){
		cdst.push_back(i);
	}
	cdst.test_print(cout);
	cout << "\npop 99x from the list" << endl;
	for(int i = 1; i <= 99; i++){
		cdst.pop_back();
	}
	cdst.test_print(cout);
	cout << "\npop once more to trigger shrink" << endl;
	cout << "remove(56): " << cdst.remove(56) << endl;
	cdst.test_print(cout);
	cout << "\npop_back(): " << cdst.pop_back() << endl;
	cdst.test_print(cout);
	cout << "\npop_front(): " << cdst.pop_front() << endl;
	cdst.test_print(cout);
	
	//cout << "testing trim half of unused arrays\nif there are more empty arrays than half of total nodes in list\n" << endl;
	//CDAL<int> cdtc;
	//cout << "push 8 nodes in (node count is up to node #7)\nloop a pop_back until 4 nodes are full (node count at 3)\npop_back once more to leave 3 nodes full (node count at 2)\nlist should resize by halving amount of free nodes from 5 to 2\nthus going from 7 nodes total to 4 nodes total\n" << endl;
	//cout << "push_back 0-350 to create 8 nodes (nodes are labelled 0 to 7)" << endl;
	//for(int i = 0; i <= 350; i++){
	//	cdtc.push_back(i);
	//}
	//cdtc.test_print(cout);
	//cout << "\npop_back 200 times to leave 0-150\nleave node count at 3" << endl;
	//for(int i = 0; i <= 199; i++){
	//	cdtc.pop_back();
	//}
	//cdtc.test_print(cout);
	//cout << "\npop_back" << endl;
	//cdtc.pop_back();
	//cdtc.test_print(cout);
	
	//cout << "\ntesting print function" << endl;
	//cdtc.print(cout);

	cout << "\n";cout << "\n";
	
	cout << "testing replace" << endl;
	CDAL<int> cdrep;
	cdrep.push_back(13);cdrep.push_back(2);cdrep.push_back(44);cdrep.push_back(4);cdrep.push_back(99);
	cdrep.test_print(cout);
	cout << endl;
	cout << "replacing position 0 with element 1 ~ replace(1,0): " << cdrep.replace(1,0) << endl;
	cdrep.test_print(cout);
	cout << endl;
	cout << "replacing position 2 with element 3 ~ replace(3,2): " << cdrep.replace(3,2) << endl;
	cdrep.test_print(cout);
	cout << endl;
	cout << "replacing position 4 with element 5 ~ replace(5,4): " << cdrep.replace(5,4) << endl;
	cdrep.test_print(cout);
	cout << endl;
	cout << "trying ~ replace(3,10)" << endl;
	try{
		cdrep.replace(3,10);
	}
	catch(runtime_error){
		cout << "error: position is not in bounds of list" << endl;
	}
	cout << endl;
	cout <<  "pop_back x 5replace to make empty list" << endl;
	for(int i = 0; i <= 4; i++){
		cdrep.pop_back();
	}
	cdrep.test_print(cout);
	cout << "trying ~ replace(5,2)" << endl;
	try{
		cdrep.replace(5,2);
	}
	catch(runtime_error){
		cout << "error: empty list" << endl;
	}
	cout << "\ntesting print function" << endl;
	cdrep.print(cout);
	
	cout << "\n";cout << "\n";
	
	
	CDAL<int> cdrep2;
	cout << "\ntesting replace on large list with >1 nodes" << endl;
	for(int i = 0; i<= 110; i++){
		cdrep2.push_back(i);

	}
	cdrep2.test_print(cout);
	cout << "\nreplacing position 23 with element 77 ~ replace(77,23): " <<cdrep2.replace(77,23) << endl;
	cdrep2.test_print(cout);
	cout << "\nreplacing position 103 with element 24 ~ replace(24,103): " <<cdrep2.replace(24,103) << endl;
	cdrep2.test_print(cout);
	cout << "\ntesting print function" << endl;
	cdrep2.print(cout);
	
	cout << "\n\n";
	
	cout << "testing item_at, peek_front, and peek_back\n" << endl;
	CDAL<int> cdia;
	cdia.push_back(44);cdia.push_back(23);cdia.push_back(7);cdia.push_back(91);cdia.push_back(0);
	cdia.print(cout);
	cout << "peek_front(): " << cdia.peek_front() << endl;
	cout << "item_at position 4 ~ item_at(4): " << cdia.item_at(4) << endl;
	cout << "item_at position 2 ~ item_at(2): " << cdia.item_at(2) << endl;
	cout << "item_at position 0 ~ item_at(0): " << cdia.item_at(0) << endl;
	cout << "peek_back(): " << cdia.peek_back() << endl;
	
	int * mycdarr1 = cdia.contents();
	for(int i = 0; i <= 4; i++){
		cout << mycdarr1[i] << "_";
	}
	cout << endl;
	//cout << "\npush_back on list and make new contents arr" << endl;
	cout << "push_back 100" << endl;
	cdia.push_back(100);
	//mycdarr1 = cdia.contents();
	//for(int i = 0; i <= cdia.length()-1; i++){
	//	cout << mycdarr1[i] << "_"; 
	//}
	delete[] mycdarr1;
	cout <<  endl;
	
	cout << "\ntesting contains" << endl;
	cout << "contains 4: " << cdia.contains(4, &compare_int) << endl;
	cout << "contains 44: " << cdia.contains(44, &compare_int) << endl;
	cout << "contains 23: " << cdia.contains(23, &compare_int) << endl;
	cout << "contains 5: " << cdia.contains(5, &compare_int) << endl << endl;
	
	cout << "push_back 1-50 in list" << endl;
	for(int i = 1; i <= 50; i++){
		cdia.push_back(i);
	}
	cdia.test_print(cout);
	
	cout << "\npeek_front(): " << cdia.peek_front() << endl;
	cout << "item_at position 14 ~ item_at(14): " << cdia.item_at(14) << endl;
	cout << "item_at position 2 ~ item_at(2): " << cdia.item_at(2) << endl;
	cout << "peek_back(): " << cdia.peek_back() << endl;
	
	cout << "\ntesting contents again" << endl;
	int * cdarr;  
	//cout << "address of cdarr: "<< &(*cdarr) << endl;
	cdarr = cdia.contents();
	for(int i = 0; i <= cdia.length()-1; i++){
		cout << cdarr[i] << "_";
	}
	delete[] cdarr;
	cout << endl;
	
	cout << "\ntesting print function" << endl;
	cdia.print(cout);
	
	cout << "\ntesting clear" << endl;
	cdia.clear();
	cout << "printing: " << endl;
	cdia.print(cout);
	
	
	cout << "\nmake big list with >1 node" << endl;
	CDAL<int> cdiab;
	for(int i = 0; i <= 102; i++){
		cdiab.push_back(i);
	}
	cdiab.test_print(cout);
	int * myarr = cdiab.contents();
	for(int i = 0; i <= cdiab.length()-1; i++){
		cout << myarr[i] << "_";
	}
	cout << endl;
	delete[] myarr;
	cout << "\npop_back(): " << cdiab.pop_back() << endl;
	
	int * myarr3 = cdiab.contents();
	for(int i = 0; i <= cdiab.length()-1; i++){
		cout << myarr3[i] << "_";
	}
	delete[] myarr3;
	cout << endl;
	
	cout << "\ntesting print function" << endl;
	cdiab.print(cout);
	
	cout << "\npeek_front(): " << cdiab.peek_front() << endl;
	cout << "item_at position 52 ~ item_at(52): " << cdiab.item_at(52) << endl;
	cout << "item_at position 101 ~ item_at(101): " << cdiab.item_at(101) << endl; 
	cout << "peek_back(): " << cdiab.peek_back() << endl;
	cout << "\ntesting clear" << endl;
	cdiab.clear();
	cout << "printing: " << endl;
	cdiab.print(cout);
	
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