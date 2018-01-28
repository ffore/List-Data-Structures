#include <iostream>
#include <stdexcept>
#include "List.h"
#include "PSLL.h"

using namespace std;
using namespace cop3530;


//======this is the function parameter passed for contains()====
template <typename E>
bool compare_int(const E& element, const E& value);
//==============================================================


int main(){
	cout << "testing iterators" << endl;
	PSLL<char> psit;
	psit.insert('I', 0);
	psit.insert('J', 1);
	psit.insert('K', 2);
	psit.print(cout);
	const PSLL<char> cpsit(psit);
	//cpsit.insert('J', 1); /*Uncomment this to throw compile error, cannot modify const list*/
	
	cout << "\nmake iterator called psiter1 point to beginning of list" << endl;
	PSLL<char>::iterator psiter1 = psit.begin();
	cout << "*psiter1: " << *psiter1 << endl;
	
	cout << "\nmake another iterator called psiter2 based off of psiter1" << endl;
	PSLL<char>::iterator psiter2(psiter1);
	cout << "*psiter2: " << *psiter2 << endl;
	cout << "*psiter1: " << *psiter1 << endl;
	cout << "now preincrement psiter2" << endl;
	++psiter2;
	cout << "*psiter2: " << *psiter2 << endl;
	
	cout << "\nuse assignment operator to make psiter1 = psiter2" << endl;
	psiter1 = psiter2;
	cout << "*psiter1: " << *psiter1 << endl;
	cout << "*psiter2: " << *psiter2 << endl;
	
	bool bool_psit = psiter1 == psiter2;
	cout << "\ncheck if psiter1 == psiter2: " << bool_psit << endl;
	
	
	cout << "\npost incrememnt psiter1" << endl;
	psiter1++;
	cout << "*psiter1: " << *psiter1 << endl;
	
	bool_psit = psiter1 != psiter2;
	cout << "\ncheck if psiter1 != psiter2: " << bool_psit << endl;
	
	cout << "\nconstructing psiter3 using psiter1" << endl;
	PSLL<char>::iterator psiter3(psiter1);
	cout << "*psiter3: " << *psiter3 << endl;
	
	cout << "enhanced for loop using iterators" << endl;
	for(auto w: psit){
		cout << w << "~";
	}
	cout << endl;
	
	cout << "pop_back in psit to put a node in pool to demonstrate deep copy" << endl;
	cout << "pop_back(): " << psit.pop_back() << endl;
	
	cout << "\ntesting copy constructor" << endl;
	cout << "constructing copy of psit called copypsit" << endl;
	PSLL<char> copypsit(psit);
	cout << "\nprint copypsit: " << endl;
	copypsit.print(cout);
	cout << "\nprint psit: " << endl;
	psit.print(cout);
	psit.push_back('Z');
	cout << "\nmodifiying copypsit" << endl;
	copypsit.insert('A', 2);
	cout << "print copypsit: " << endl;
	copypsit.print(cout);
	cout << endl;
	cout << "\ntesting const iterators" << endl;
	cout << "making const list called const_copysit through copy constructor using psit" << endl;
	const PSLL<char> const_copypsit(psit);
	cout << "making const iterator called const_psiter1" << endl;
	PSLL<char>::const_iterator const_psiter1 = const_copypsit.begin();
	cout << "*const_psiter1: " << *const_psiter1 << endl;
	cout << "++const_psiter1" << endl;
	++const_psiter1;
	cout << "*const_psiter1: " << *const_psiter1 << endl;
	cout << "making const iterator const_psiter2 based off const_psiter1" << endl;
	PSLL<char>::const_iterator const_psiter2(const_psiter1);
	cout << "*const_psiter2: " << *const_psiter2 << endl;
	cout << "const_psiter2++" << endl;
	const_psiter2++;
	cout << "*const_psiter2: " << *const_psiter2 << endl;
	cout << "*const_psiter1: " << *const_psiter1 << endl;
	
	cout << "make const_psiter1 = const_psiter2" << endl;
	const_psiter1 = const_psiter2;
	cout << "*const_psiter2: " << *const_psiter2 << endl;
	cout << "*const_psiter1: " << *const_psiter1 << endl;
	
	
	cout << "\nenhanced for loop using const iterators" << endl;
	for(auto w: const_copypsit){
		cout << w << "~";
	}
	cout << endl;
	
	cout << "\ntesting copy assignemnt" << endl;
	cout << "making list called a_copypsit" << endl;
	PSLL<char> a_copypsit;
	cout << "push_back A,B,C,X,Y,Z in a_copypsit" << endl;
	a_copypsit.push_back('A');a_copypsit.push_back('B');a_copypsit.push_back('C');a_copypsit.push_back('X');a_copypsit.push_back('Y');a_copypsit.push_back('Z');
	cout << "print a_copypsit: " << endl;
	a_copypsit.print(cout);
	cout << "pop_front three times" << endl;
	a_copypsit.pop_front();a_copypsit.pop_front();a_copypsit.pop_front();
	cout << "print a_copypsit: " << endl;
	a_copypsit.print(cout);
	cout << "\nset a_copypsit = copypsit" << endl;
	a_copypsit = copypsit;
	cout << "print a_copypsit: " << endl;
	a_copypsit.print(cout);
	
	cout << endl;cout << endl;
	
	cout << "testing move assignment" << endl;
	cout << "make psll object called dest_copypsit" << endl;
	PSLL<char> dest_copypsit;
	dest_copypsit.push_back('R');dest_copypsit.push_back('E');dest_copypsit.push_back('D');
	cout << "going to make move contents from copypsit to dest_copypsit" << endl;
	copypsit.pop_back();
	cout << "print copypsit: " << endl;
	copypsit.print(cout);
	cout << "print dest_copypsit: " << endl;
	dest_copypsit.print(cout);
	cout << "\nmove from copypsit to dest_copypsit" << endl;
	dest_copypsit = std::move(copypsit);
	cout << "print copypsit: " << endl;
	copypsit.print(cout);
	cout << "print dest_copypsit: " << endl;
	dest_copypsit.print(cout);
	cout << "\nedit dest_copypsit" << endl;
	dest_copypsit.insert('P',1);
	cout << "print dest_copypsit: " << endl;
	dest_copypsit.print(cout);
	
	cout << endl;
	
	cout << "testing move constructor" << endl;
	cout << "make new object final_copypsit that takes the information from dest_copypsit" << endl;
	PSLL<char> final_copypsit(std::move(dest_copypsit));
	cout << "print dest_copypsit: " << endl;
	dest_copypsit.print(cout);
	cout << "print final_copypsit: " << endl;
	final_copypsit.print(cout);
	cout << "\nedit final_copypsit" << endl;
	final_copypsit.push_front('X');
	cout << "print final_copypsit: " << endl;
	final_copypsit.print(cout);
	
	cout << endl;cout << endl;
	
	
	
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	PSLL<int> psnc; 
	cout << "push_back 55 nodes and then pop_back more than 50 nodes" << endl;
	cout << "pool should only have 50 nodes as that is the maximum it can hold" << endl;
	cout << "\npush_back() i (i = 1 - 55)" << endl;
	for(int i = 1; i <= 55; i++){
		psnc.push_back(i);
	}
	psnc.print(cout);
	cout << "length: " << psnc.length() << endl;
	cout << "\npop_back() 49 times" << endl;
	for(int i = 1; i<= 49; i++){
		psnc.pop_back();
	}
	psnc.print(cout);
	cout << "length: " << psnc.length() << endl;
	cout << "\npop_back(): " << psnc.pop_back() << endl;
	psnc.print(cout);
	cout << "length: " << psnc.length() << endl;
	
	cout << "\npop_back() once to trigger pool maxsize condition" << endl;
	cout << "pop_back(): " << psnc.pop_back() << endl;
	psnc.print(cout);
	cout << "length: " << psnc.length() << endl;
	
	cout << "\nnow pop_front() once to trigger pool maxsize condition" << endl;
	cout << "pop_front(): " << psnc.pop_front() << endl;
	psnc.print(cout);
	cout << "length: " << psnc.length() << endl;
	
	cout << "\ninsert 44 at position 2" << endl;
	cout << "using a node from the pool" << endl;
	psnc.insert(44, 2);
	psnc.print(cout);
	cout << "length: " << psnc.length() << endl;
	
	cout << "\npop_back() once to add node to pool" << endl;
	cout << "pop_back(): " << psnc.pop_back() << endl;
	psnc.print(cout);
	cout << "length: " << psnc.length() << endl;
	
	cout << "\nnow remove once to trigger pool maxsize condition" << endl;
	cout << "remove element at position 1: " << psnc.remove(1) << endl;
	psnc.print(cout);
	cout << "length: " << psnc.length() << endl;
	
	cout << "\nnow pop_front() once to trigger pool maxsize condition" << endl;
	cout << "pop_front(): " << psnc.pop_front() << endl;
	psnc.print(cout);
	cout << "length: " << psnc.length() << endl;
	
	cout << "\nnow remove once to trigger pool maxsize condition" << endl;
	cout << "remove element at position 0: " << psnc.remove(0) << endl;
	psnc.print(cout);
	cout << "length: " << psnc.length() << endl;
	
	cout << "\nagain pop_back() once to trigger pool maxsize condition" << endl;
	try{
		cout << "pop_back(): " << psnc.pop_back() << endl;	
	}
	catch(runtime_error){
		cout << "error cannot pop_back" << endl;
	}
	
	cout << endl;cout << endl;
	
	PSLL<int> pspub;
	cout << "testing push_back" << endl;
	cout << "push_back(11)" << endl;
	pspub.push_back(11);
	pspub.print(cout);
	cout << "length of list: " << pspub.length() << endl;
	cout << "push_back(9)" << endl;
	pspub.push_back(9);
	pspub.print(cout);
	cout << "length of list: " << pspub.length() << endl;
	cout << "push_back 0 - 50" << endl;
	for(int i = 0; i <= 50; i++){
		pspub.push_back(i);
	}
	pspub.print(cout);
	cout << "length of list: " << pspub.length() << endl;
	cout << "pop_front(): " << pspub.pop_front() << endl;
	pspub.print(cout);
	cout << "length of list: " << pspub.length() << endl;
	cout << "push_back(2)" << endl;
	pspub.push_back(2);
	pspub.print(cout);
	cout << "length of list: " << pspub.length() << endl;
	
	cout << endl;cout << endl;
	
	PSLL<int> pspuf;
	cout << "testing push_front" << endl;
	cout << "push_front(9)" << endl;
	pspuf.push_front(9);
	pspuf.print(cout);
	cout << "length of list: " << pspuf.length() << endl;
	cout << "push_front(88)" << endl;
	pspuf.push_front(88);
	pspuf.print(cout);
	cout << "length of list: " << pspuf.length() << endl;
	cout << "push_front 0 - 50" << endl;
	for(int i = 0; i <= 50; i++){
		pspuf.push_front(i);
	}
	pspuf.print(cout);
	cout << "length of list: " << pspuf.length() << endl;
	cout << "pop_back(): " << pspuf.pop_back() << endl;
	pspuf.print(cout);
	cout << "length of list: " << pspuf.length() << endl;
	cout << "push_front(44)" << endl;
	pspuf.push_front(44);
	pspuf.print(cout);
	cout << "length of list: " << pspuf.length() << endl;
	
	cout << endl;cout << endl;
	
	
	PSLL<int> psi;
	cout << "testing insert on empty list" << endl;
	psi.insert(4, 0);
	psi.print(cout);
	cout << "length of list: " << psi.length() << endl;
	cout << "\ntesting insert at end of filled list" << endl;
	psi.insert(7, 1);
	psi.print(cout);
	cout << "length of list: " << psi.length() << endl;
	cout << "\ninsert 2 at position 2 (end of list)" << endl;
	psi.insert(2, 2);
	psi.print(cout);
	cout << "length of list: " << psi.length() << endl;
	cout << "\ninsert 5 at position 1" << endl;
	psi.insert(5, 1);
	psi.print(cout);
	cout << "length of list: " << psi.length() << endl;
	cout << "\ninsert 10 at position 0" << endl;
	psi.insert(10, 0);
	psi.print(cout);
	cout << "length of list: " << psi.length() << endl;
	cout << "\ninsert 55 at position 0" << endl;
	psi.insert(55, 0);
	psi.print(cout);
	cout << "length of list: " << psi.length() << endl;
	
	cout << "\nremove element at position 1" << endl;
	psi.remove(1);
	psi.print(cout);
	cout << "length of list: " << psi.length() << endl;
	
	cout << "\nremove element at position 1" << endl;
	psi.remove(1);
	psi.print(cout);
	cout << "length of list: " << psi.length() << endl;
	
	cout << "\ninsert element at position 2" << endl;
	psi.insert(44, 2);
	psi.print(cout);
	cout << "length of list: " << psi.length() << endl;
	
	cout << "\npop back" << endl;
	psi.pop_back();
	psi.print(cout);
	cout << "length of list: " << psi.length() << endl;
	
	cout << endl; cout << endl;
	
	PSLL<int> pspb;
	cout << "testing pop_back" << endl;
	cout << "push_back 1" << endl;
	pspb.push_back(1);
	pspb.print(cout);
	cout << "length of list: " << pspb.length() << endl;
	cout << "pop_back(): " << pspb.pop_back() << endl;
	pspb.print(cout);
	cout << "length of list: " << pspb.length() << endl;
	cout << "inserting element i at position i (i = 0-60)" << endl;
	for(int i = 0; i <= 60; i++){
		pspb.insert(i, i);
	}
	pspb.print(cout);
	cout << "length of list: " << pspb.length() << endl;
	cout << "\npop_back(): " << pspb.pop_back() << endl;
	pspb.print(cout);
	cout << "length of list: " << pspb.length() << endl;
	cout << "\npop_back(): " << pspb.pop_back() << endl;
	pspb.print(cout);
	cout << "length of list: " << pspb.length() << endl;
	
	cout << endl; cout << endl;
	
	PSLL<int> pspf;
	cout << "testing pop_front" << endl;
	cout << "push_front 1" << endl;
	pspf.push_front(1);
	pspf.print(cout);
	cout << "length of list: " << pspf.length() << endl;
	cout << "pop_front(): " << pspf.pop_front() << endl;
	pspf.print(cout);
	cout << "length of list: " << pspf.length() << endl;
	cout << "\npush back 0-60" << endl;
	for(int i = 0; i <= 60; i++){
		pspf.push_back(i);
	}
	pspf.print(cout);
	cout << "length of list: " << pspf.length() << endl;
	cout << "\npop_front(): " << pspf.pop_front() << endl;
	pspf.print(cout);
	cout << "length of list: " << pspf.length() << endl;
	cout << "\npop_front(): " << pspf.pop_front() << endl;
	pspf.print(cout);
	cout << "length of list: " << pspf.length() << endl;
	cout << "\npop_back(): " << pspf.pop_back() << endl;
	pspf.print(cout);
	cout << "length of list: " << pspf.length() << endl;
	cout << "\nremove element at position 4: " << pspf.remove(4) << endl;
	pspf.print(cout);
	cout << "length of list: " << pspf.length() << endl;
	cout << "\nremove element at position 0: " << pspf.remove(0) << endl;
	pspf.print(cout);
	cout << "length of list: " << pspf.length() << endl;
	cout << "\nremove element at position 55: " << pspf.remove(55) << endl;
	pspf.print(cout);
	cout << "length of list: " << pspf.length() << endl;
	
	cout << endl;cout << endl;
	
	cout << "testing the pool check for psll" << endl;
	cout << "push 1-151 nodes in list" << endl;
	cout << "\n";
	PSLL<int> psch;
	for(int i = 1 ; i <= 151; i++){
		psch.push_back(i);
	}
	psch.print(cout);
	cout << "length of list: " << psch.length() << endl;
	cout << "\npop 49 nodes into pool" << endl;
	for(int i = 1; i <= 49; i++){
		psch.pop_back();
	}
	psch.print(cout);
	cout << "length of list: " << psch.length() << endl;
	cout << "\npop_back(): " << psch.pop_back() << endl;
	psch.print(cout);
	cout << "length of list: " << psch.length() << endl << endl;
	cout << "pop once more to put 51 nodes in free list" << endl;
	cout << "but after the resize condition of psll's" << endl;
	cout << "the pool should have 50 nodes" << endl;
	cout << "pop_back() again: " << psch.pop_back() << endl;
	psch.print(cout);
	cout << "length of list: " << psch.length() << endl;
	cout << "\npop_back(): " << psch.pop_back() << endl;
	psch.print(cout);
	cout << "length of list: " << psch.length() << endl;
	
	cout << "\nreplace element at position 2 with 66" << endl;
	cout << "replace(66, 2): " << psch.replace(66, 2) << endl;
	psch.print(cout);
	cout << "length of list: " << psch.length() << endl;
	cout << "\nreplace element at position 5 with 0" << endl;
	cout << "replace(0, 5): " << psch.replace(0, 5) << endl;
	psch.print(cout);
	cout << "length of list: " << psch.length() << endl;
	cout << "\nreplace element at position 0 with 10" << endl;
	cout << "replace(10, 0): " << psch.replace(10, 0) << endl;
	psch.print(cout);
	cout << "length of list: " << psch.length() << endl;
	cout << "\nreplace element at position 98 with 4" << endl;
	cout << "replace(4, 98): " << psch.replace(4, 98) << endl;
	psch.print(cout);
	cout << "length of list: " << psch.length() << endl;
	
	
	cout << "\ntesting peek_back, peek_front, & item_at" << endl;
	cout << "peek_back(): " << psch.peek_back() << endl;
	cout << "peek_front(): " << psch.peek_front() << endl;
	cout << "item_at(8): " << psch.item_at(8) << endl;
	cout << "item_at(2): " << psch.item_at(2) << endl;
	
	cout << "\ntesting contains" << endl;
	cout << "Does the list contain 77: " << psch.contains(77, &(compare_int)) << endl;
	cout << "Does the list contain 101: " << psch.contains(101, &(compare_int)) << endl;
	cout << "Does the list contain 4: " << psch.contains(4, &(compare_int)) << endl;
	
	cout << "\ntesting contents" << endl;
	int * psarr = psch.contents();
	for(int i = 0; i <= 98; i++){
		cout << psarr[i] << "_";
	}
	delete[] psarr;
	cout << endl;
	
	cout << "\ntesting clear" << endl;
	psch.clear();
	psch.print(cout);
	cout << "length of list: " << psch.length() << endl;
	cout << "\npush_back(8)"<< endl;
	psch.push_back(8);
	psch.print(cout);
	cout << "length of list: " << psch.length() << endl;
	cout << "\nremove(0): " << psch.remove(0) << endl;
	psch.print(cout);
	cout << "length of list: " << psch.length() << endl;
	cout << "\npush_front(11)"<< endl;
	psch.push_front(11);
	psch.print(cout);
	
	cout << "\ntesting contents again" << endl;
	int * psarr2 = psch.contents();
	cout << psarr2[0] << "_" << endl;
	delete[] psarr2;
	
	cout << endl;cout << endl;
	

	cout << "testing pop_back()" << endl;
	PSLL<int> ppop;
	ppop.push_back(3);
	ppop.push_back(1);
	ppop.push_back(2);
	ppop.print(cout);
	cout << "\n";
	cout << "\n";
	cout << "pop_back once" << endl;
	ppop.pop_back();
	ppop.print(cout);
	cout << "\n";
	cout << "\n";
	cout << "pop_back twice" << endl;
	ppop.pop_back();
	ppop.print(cout);
	cout << "\n";
	cout << "\n";
	cout << "pop_back thrice" << endl;
	ppop.pop_back();
	ppop.print(cout);
	cout << "\n";
	cout << "\n";
	cout << "\ntesting pop_back() on empty list" << endl;
	try{
		ppop.pop_back();
	}
	catch(runtime_error){
		cout << "error: empty list, cannot pop_back" << endl;
	}
	ppop.print(cout);


	cout << "\n";
	cout << "\n";

	cout << "testing replace\n" << endl;
	PSLL<int> prep;
	cout << "testing replace on empty list" << endl;
	cout<< "replace(22, 5): " << endl;
	try{
	prep.replace(22,5);
	}
	catch(runtime_error){
		cout << "error: empty list, nothing to replace" << endl;
	}
	cout << "\ntesting replace on position outside of filled list" << endl;
	prep.push_back(25);
	prep.print(cout);
	cout << "replace(13 , 4): " << endl;
	try{
		prep.replace(13,4);
	}
	catch(runtime_error){
		cout << "error: position exceeds list length" << endl;
	}
	

	cout << "\n";
	cout << "\n";

	cout << "testing remove" << endl;
	cout << "\n";
	cout << "testing if list is empty" << endl;
	PSLL<int> premt;
	cout << "remove(2)" << endl;
	try{
		premt.remove(2);
	}
	catch(runtime_error){
		cout << "error: can't remove from empty list" << endl;
	}
	cout << "\n";
	cout << "testing if position > length" << endl;
	premt.push_back(11);
	premt.push_back(9);
	premt.push_back(10);
	premt.print(cout);
	cout << "remove(6)" << endl;
	try{
		premt.remove(6);
	}
	catch(runtime_error){
		cout << "error: position is outside of list length cannot remove" << endl;
	}


	cout << "\n";
	cout << "\n";

	cout << "testing item_at" << endl;
	PSLL<int> pita;
	cout << "\ntesting item_at on empty list" << endl;
	cout << "item_at(2)" << endl;
	try{
	pita.item_at(2);
	}
	catch(runtime_error){
		cout << "error: empty list" << endl;
	}
	cout << "\ntesting item_at on !empty list and outside position" << endl;
	pita.push_back(9);
	pita.print(cout);
	cout << "item_at(3)" << endl;
	try{
		pita.item_at(3);
	}
	catch(runtime_error){
		cout << "error: position exceeds length of list" << endl;
	}

	cout << "\n";
	cout << "\n";

	cout << "testing peek_back()" << endl;
	PSLL<int> ppeekb;
	cout << "testing peek back on empty list" << endl;
	try{
		ppeekb.peek_back();
	}
	catch(runtime_error){
		cout << "empty list, cannot peek_back()" << endl;
	}

	cout << "\n";
	cout << "\n";

	cout << "testing peek_front()" << endl;
	PSLL<int> ppeekf;
	cout << "testing peek front on empty list" << endl;
	try{
		ppeekf.peek_front();
	}
	catch(runtime_error){
		cout << "empty list, cannot peek_front()" << endl;
	}	
	
	cout << "\n";
	cout << "\n";
	
	
	cout << "testing clear on big list" << endl;
	PSLL<int> psblcl;
	for(int i =0; i <=99; i++){
		psblcl.insert(i,i);
	}
	psblcl.print(cout);
	cout << "calling clear" << endl;
	psblcl.clear();
	psblcl.print(cout);
	
	cout << "\ntesting clear on now empty list" << endl;
	psblcl.clear();
	psblcl.print(cout);
	
	
	cout << "\n";
	cout << "\n";
	
	cout << "testing clear on newly initialized list" << endl;
	PSLL<int> psblcl2;
	psblcl2.print(cout);
	cout << "calling clear" << endl;
	psblcl2.clear();
	psblcl2.print(cout);
	
	
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