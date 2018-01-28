#include "List.h" 
#include "CBL.h" 
#define CATCH_CONFIG_MAIN
#include "catch.hpp" 

	using namespace std;
	
	
	//======this is the function parameter passed for contains()====
	template <typename E>
	bool compare_char(const E& element, const E& value){
		//cout << "comparing " << element << "with " << value << endl;
		if(element == value){
			return true;
		}
		else
		return false;
	}
//==============================================================
	cop3530::CBL<char> cba(5);
	
	
	TEST_CASE("making sure item_at/peekfront/peekback matches insert and testing contains", "[constructore]"){
		cout << "==========TEST1==========" << endl;
		cba.insert('A', 0);
		cba.insert('B', 1);
		cba.insert('C', 2);
		cout << "insert A,B,C at positions 0,1,2" << endl;
		cba.test_print(cout);
		
		const cop3530::CBL<char> ccba(cba);
		//ccba.pop_front(); /*Uncomment this to throw compile error, cannot modify const list*/
	
		REQUIRE(cba.item_at(0) == 'A');
		REQUIRE(cba.item_at(1) == 'B');
		REQUIRE(cba.item_at(2) == 'C');
		REQUIRE(cba.get_size() == 3);
		REQUIRE(cba.peek_back() == 'C');
		REQUIRE(cba.peek_front() == 'A');
		REQUIRE(cba.contains('A', &compare_char) == 1);
		REQUIRE(cba.contains('X', &compare_char) == 0);
		REQUIRE(cba.contains('C', &compare_char) == 1);
		REQUIRE(cba.contains('Z', &compare_char) == 0);
		
	}

	
	TEST_CASE("testing pop_front" , "[pop_front]"){
		cout << "\n==========TEST2==========" << endl;
		cout << "pop_front" << endl;
		REQUIRE(cba.pop_front() == 'A');
		REQUIRE(cba.item_at(0) == 'B');
		REQUIRE(cba.item_at(1) == 'C');
		cba.test_print(cout);
	}
	
	TEST_CASE("testing insert until the list resizes" , "[insert_to_resize]"){
		cout << "\n==========TEST3==========" << endl;
		cout << "insert D,E,F at positions 2,3,4 " << endl;
		cout << "list will be filled in completely" << endl;
		cba.insert('D', 2);
		cba.insert('E', 3);
		cba.insert('F', 4);
		cba.test_print(cout);
		REQUIRE(cba.item_at(0) == 'B');
		REQUIRE(cba.item_at(1) == 'C');
		REQUIRE(cba.item_at(2) == 'D');
		REQUIRE(cba.item_at(3) == 'E');
		REQUIRE(cba.item_at(4) == 'F');
		
		cout << "\ninsert G at position 5" << endl;
		cba.insert('G', 5);
		cba.test_print(cout);
		REQUIRE(cba.item_at(5) == 'G');
	}
	
	TEST_CASE("testing pop_front, pop_back, insert, peekfront/back, contains, and clear" , "[pop_fb&insert]"){
		cout << "\n==========TEST4==========" << endl;
		char tpi = cba.pop_front();
		cout << "pop_front(): " << tpi << endl;
		REQUIRE(tpi == 'B');
		//cba.test_print(cout);
		cba.print(cout);
		
		tpi = cba.pop_front();
		cout << "\npop_front(): " << tpi << endl; 
		REQUIRE(tpi == 'C');
		//cba.test_print(cout);
		cba.print(cout);
		
		cout << "\ninsert H and I position 4 and 5" << endl;
		cba.insert('H' , 4);
		cba.insert('I', 5);
		REQUIRE(cba.item_at(4) == 'H');
		REQUIRE(cba.item_at(5) == 'I');
		//cba.test_print(cout);
		cba.print(cout);
		
		tpi = cba.pop_front();
		cout << "\npop_front(): " << tpi << endl;
		REQUIRE(tpi == 'D');
		//cba.test_print(cout);
		cba.print(cout);
		
		tpi = cba.pop_back();
		cout << "\npop_back(): " << tpi << endl;
		REQUIRE(tpi == 'I');
		//cba.test_print(cout);
		cba.print(cout);
		
		cout << "\ninsert X,Y,Z at positions 0,1,2" << endl;
		cba.insert('X', 0);
		cba.insert('Y', 1);
		cba.insert('Z', 2);
		REQUIRE(cba.item_at(0) == 'X');
		REQUIRE(cba.item_at(1) == 'Y');
		REQUIRE(cba.item_at(2) == 'Z');
		//cba.test_print(cout);
		cba.print(cout);
		
		tpi = cba.pop_back();
		cout << "\npop_back(): " << tpi << endl;
		REQUIRE(tpi == 'H');
		//cba.test_print(cout);
		cba.print(cout);
		
		cout << "\ninsert A at position 0" << endl;
		cba.insert('A', 0);
		REQUIRE(cba.item_at(0) == 'A');
		//cba.test_print(cout);
		cba.print(cout);
		
		tpi = cba.pop_front();
		cout << "\npop_front(): " << tpi << endl;
		REQUIRE(tpi == 'A');
		//cba.test_print(cout);
		cba.print(cout);
		
		REQUIRE(cba.peek_front() == 'X');
		REQUIRE(cba.peek_back() == 'G');
		
		REQUIRE(cba.contains('X', &compare_char) == 1);
		REQUIRE(cba.contains('B', &compare_char) == 0);
		REQUIRE(cba.contains('F', &compare_char) == 1);
		REQUIRE(cba.contains('A', &compare_char) == 0);
		
		cout << "\ntesting clear" << endl;
		cba.clear();
		//cba.test_print(cout);
		cba.print(cout);
		cout << "\npush_front('A')" << endl;
		cba.push_front('A');
		REQUIRE(cba.item_at(0) == 'A');
		//cba.test_print(cout);
		cba.print(cout);
	}
	
	cop3530::CBL<char> pbcbas(2);
	
	TEST_CASE("testing list shrinkage pop_front" , "[popf_shrink]"){
		cout << "\n==========TEST5==========" << endl;
		cout << "testing shrink with pop_front" << endl;
		cout << "insert A and B in list size 2" << endl;
		pbcbas.insert('A', 0);
		REQUIRE(pbcbas.item_at(0) == 'A');
		pbcbas.insert('B', 1);
		REQUIRE(pbcbas.item_at(1) == 'B');
		cout << "\ninsert C~should resize to 3" << endl;
		pbcbas.insert('C', 2);
		REQUIRE(pbcbas.item_at(2) == 'C');
		pbcbas.test_print(cout);
		cout << "\ninsert D~should resize to 4" << endl;
		pbcbas.insert('D', 3);
		REQUIRE(pbcbas.item_at(3) == 'D');
		pbcbas.test_print(cout);
		cout << "\npop front x 3 to have the list be twice the original capacity" << endl;
		cout << "and since it is filled to less than half of the capacity" << endl;
		cout << "should resize to 3" << endl;
		char tpbcbas = pbcbas.pop_front();
		REQUIRE(tpbcbas == 'A');
		cout << "\npop_front(): " << tpbcbas << endl;
		pbcbas.test_print(cout);
		tpbcbas = pbcbas.pop_front();
		REQUIRE(tpbcbas == 'B');
		cout << "\npop_front(): " << tpbcbas << endl;
		pbcbas.test_print(cout);
		tpbcbas = pbcbas.pop_front();
		REQUIRE(tpbcbas == 'C');
		cout << "\npop_front(): " << tpbcbas << endl;
		pbcbas.test_print(cout);
	}
	
	cop3530::CBL<char> pfcbas(2);
	
	TEST_CASE("testing list shrinkage pop_back" , "[popb_shrink]"){
		cout << "\n==========TEST6==========" << endl;
		cout << "testing shrink with pop_back" << endl;
		cout << "insert A and B in list size 2" << endl;
		pfcbas.insert('A', 0);
		REQUIRE(pfcbas.item_at(0) == 'A');
		pfcbas.insert('B', 1);
		REQUIRE(pfcbas.item_at(1) == 'B');
		cout << "\ninsert C~should resize to 3" << endl;
		pfcbas.insert('C', 2);
		REQUIRE(pfcbas.item_at(2) == 'C');
		pfcbas.test_print(cout);
		cout << "\ninsert D~should resize to 4" << endl;
		pfcbas.insert('D', 3);
		REQUIRE(pfcbas.item_at(3) == 'D');
		pfcbas.test_print(cout);
		cout << "\npop back x 3 to have the list be twice the original capacity" << endl;
		cout << "and since it is filled to less than half of the capacity" << endl;
		cout << "should resize to 3" << endl;
		char tpfcbas = pfcbas.pop_back();
		REQUIRE(tpfcbas == 'D');
		cout << "\npop_back(): " << tpfcbas << endl;
		pfcbas.test_print(cout);
		tpfcbas = pfcbas.pop_back();
		REQUIRE(tpfcbas == 'C');
		cout << "\npop_back(): " << tpfcbas << endl;
		pfcbas.test_print(cout);
		tpfcbas = pfcbas.pop_back();
		REQUIRE(tpfcbas == 'B');
		cout << "\npop_back(): " << tpfcbas << endl;
		pfcbas.test_print(cout);
	}
	
	cop3530::CBL<char> remcb(2);
	
	TEST_CASE("testing list shrinkage remove" , "[rem_shrink]"){
		cout << "\n==========TEST7==========" << endl;
		cout << "testing shrink with remove" << endl;
		cout << "insert A and B in list size 2" << endl;
		remcb.insert('A', 0);
		REQUIRE(remcb.item_at(0) == 'A');
		remcb.insert('B', 1);
		REQUIRE(remcb.item_at(1) == 'B');
		
		cout << "\ninsert C~should resize to 3" << endl;
		remcb.insert('C', 2);
		REQUIRE(remcb.item_at(2) == 'C');
		remcb.test_print(cout);
		
		cout << "\ninsert D~should resize to 4" << endl;
		remcb.insert('D', 3);
		REQUIRE(remcb.item_at(3) == 'D');
		remcb.test_print(cout);
		
		cout << "\nremove x 3 to have the list be twice the original capacity" << endl;
		cout << "and since it is filled to less than half of the capacity" << endl;
		cout << "should resize to 3" << endl;
		char tremcb = remcb.remove(1);
		REQUIRE(tremcb == 'B');
		cout << "\nremove(1): " << tremcb << endl;
		remcb.test_print(cout);
		
		tremcb = remcb.remove(1);
		REQUIRE(tremcb == 'C');
		cout << "\nremove(1): " << tremcb << endl;
		remcb.test_print(cout);
		
		tremcb = remcb.remove(1);
		REQUIRE(tremcb == 'D');
		cout << "\nremove(1): " << tremcb << endl;
		remcb.test_print(cout);
	}
	
	cop3530::CBL<char> cbpfb(6);
	
	TEST_CASE("testing pushfront and pushback and replace" , "[pushfrontbackreplace]"){
		cout << "\n==========TEST8==========" << endl;
		//guitar
		//geyser
		cout << "push_front('I')" << endl;
		cbpfb.push_front('I');
		cbpfb.test_print(cout);
		REQUIRE(cbpfb.item_at(0) == 'I');
		
		cout << "push_back('T')" << endl;
		cbpfb.push_back('T');
		cbpfb.test_print(cout);
		REQUIRE(cbpfb.item_at(cbpfb.length()-1) == 'T');
		
		cout << "push_front('U')" << endl;
		cbpfb.push_front('U');
		cbpfb.test_print(cout);
		REQUIRE(cbpfb.item_at(0) == 'U');
		
		cout << "push_back('A')" << endl;
		cbpfb.push_back('A');
		cbpfb.test_print(cout);
		REQUIRE(cbpfb.item_at(cbpfb.length()-1) == 'A');
		
		cout << "push_front('G')" << endl;
		cbpfb.push_front('G');
		cbpfb.test_print(cout);
		REQUIRE(cbpfb.item_at(0) == 'G');
		
		cout << "push_back('R')" << endl;
		cbpfb.push_back('R');
		cbpfb.test_print(cout);
		REQUIRE(cbpfb.item_at(cbpfb.length()-1) == 'R');
		
		cout << "replace element at position 1 with E" << endl;
		char tcbpfb = cbpfb.replace('E',1);
		REQUIRE(tcbpfb == 'U');
		cbpfb.test_print(cout);
		
		cout << "replace element at position 2 with Y" << endl;
		tcbpfb = cbpfb.replace('Y',2);
		REQUIRE(tcbpfb == 'I');
		cbpfb.test_print(cout);
		
		cout << "replace element at position 3 with S" << endl;
		tcbpfb = cbpfb.replace('S',3);
		REQUIRE(tcbpfb == 'T');
		cbpfb.test_print(cout);
		
		cout << "replace element at position 4 with E" << endl;
		tcbpfb = cbpfb.replace('E',4);
		REQUIRE(tcbpfb == 'A');
		cbpfb.test_print(cout);
		
	}
	
	cop3530::CBL<int> cbbl;
	
	TEST_CASE("testing pushback & popback/popfront/remove on big list" , "[pb_big_list]"){
		cout << "\n==========TEST9==========" << endl;
		cout << "push_back 0-20" << endl;
		for(int i = 0; i<=20; i++){
			cbbl.push_back(i);
		}
		cbbl.test_print(cout);
		
		for(int i = 0; i<=20; i++){
			REQUIRE(cbbl.item_at(i) == i);
		}
		
		int rembl = cbbl.remove(5);
		cout << "\nremove(5): " <<  rembl << endl;
		REQUIRE(rembl == 5);
		
		rembl = cbbl.pop_front();
		cout << "\npop_front(): " <<  rembl << endl;
		REQUIRE(rembl == 0);
		
		rembl = cbbl.pop_back();
		cout << "\npop_back(): " <<  rembl << endl;
		REQUIRE(rembl == 20);
		
		cbbl.test_print(cout);
		
	}
	
	cop3530::CBL<int> cbbl1;
	
	TEST_CASE("testing pushfront & popback/popfront/remove on big list" , "[pf_big_list]"){
		cout << "\n==========TEST10==========" << endl;
		cout << "push_front 0-20" << endl;
		for(int i = 0; i<=20; i++){
			cbbl1.push_front(i);
		}
		cbbl1.test_print(cout);
		
		int bli = 0;
		for(int i = 20; i>=0; i--){
			REQUIRE(cbbl1.item_at(bli) == i);
			bli++;
		}
		
		int rembl = cbbl1.remove(5);
		cout << "\nremove(5): " <<  rembl << endl;
		REQUIRE(rembl == 15);
		
		rembl = cbbl1.pop_front();
		cout << "\npop_front(): " <<  rembl << endl;
		REQUIRE(rembl == 20);
		
		rembl = cbbl1.pop_back();
		cout << "\npop_back(): " <<  rembl << endl;
		REQUIRE(rembl == 0);
		
		cbbl1.test_print(cout);
		
	}
	
	cop3530::CBL<int> cbbl2;
	
	TEST_CASE("testing insert, popback/popfront/remove, and contents on big list" , "[in_big_list]"){
		cout << "\n==========TEST11==========" << endl;
		cout << "insert 0-20" << endl;
		for(int i = 0; i<=20; i++){
			cbbl2.insert(i,i);
		}
		cbbl2.test_print(cout);
		
		for(int i = 0; i<=20; i++){
			REQUIRE(cbbl2.item_at(i) == i);
		}
		
		int rembl = cbbl2.remove(5);
		cout << "\nremove(5): " <<  rembl << endl;
		REQUIRE(rembl == 5);
		
		rembl = cbbl2.pop_front();
		cout << "\npop_front(): " <<  rembl << endl;
		REQUIRE(rembl == 0);
		
		rembl = cbbl2.pop_back();
		cout << "\npop_back(): " <<  rembl << endl;
		REQUIRE(rembl == 20);
		
		cbbl2.test_print(cout);
		
		int * cbtarr = cbbl2.contents();
		for(int i = 0; i < cbbl2.length(); i++){
			REQUIRE(cbtarr[i] == cbbl2.item_at(i));
		}
		delete[] cbtarr;
		
	}
	
	TEST_CASE("testing big five", "[big_five]"){
		cout << "\n==========TEST12==========" << endl;
		cout << "testing copy constructor" << endl;
		cop3530::CBL<char> cbbf(5);
		cbbf.push_front('A');cbbf.push_front('B');cbbf.push_front('C');cbbf.push_front('X');cbbf.push_front('D');
		cout << "making a copy of cbbf called copy_cbbf" << endl;
		cout << "cbbf: ";
		cbbf.print(cout);
		cop3530::CBL<char> copy_cbbf(cbbf);
		for(int i = 0; i < copy_cbbf.length(); i++){
			REQUIRE(copy_cbbf.item_at(i) == cbbf.item_at(i));
		}
		cout << "copy_cbbf: ";
		copy_cbbf.print(cout);
		
		cout << "\ntesting copy assignment on copy_cbbf and cbca" << endl;
		cop3530::CBL<char> cbca(4);
		cbca.push_back('A');cbca.push_back('B');cbca.pop_front();cbca.push_front('X');cbca.push_back('Y');cbca.pop_front();cbca.push_back('Z');
		cout << "copy_cbbf: ";
		copy_cbbf.print(cout);
		cout << "cbca: ";
		cbca.print(cout);
		cout << "\nmaking copy_cbbf = cbca" << endl;
		copy_cbbf = cbca;
		for(int i = 0; i < copy_cbbf.length(); i++){
			REQUIRE(copy_cbbf.item_at(i) == cbca.item_at(i));
		}
		cout << "copy_cbbf: ";
		copy_cbbf.print(cout);
		cout << "cbca: ";
		cbca.print(cout);
		
		cout << "\ntesting move constructor" << endl;
		cout << "create new object called m_cbca that steals the contents of cbca" << endl;
		cop3530::CBL<char> m_cbca(std::move(cbca));
		for(int i = 0; i < m_cbca.length(); i++){
			REQUIRE(copy_cbbf.item_at(i) == m_cbca.item_at(i));
		}
		REQUIRE(cbca.length() == 0);
		cout << "m_cbca: ";
		m_cbca.print(cout);
		cout << "cbca: ";
		cbca.print(cout);
		
		cout << "\ntesting move assignment" << endl;
		cout << "want to move contents from copy_cbbf to cbca" << endl;
		cout << "copy_cbbf: ";
		copy_cbbf.print(cout);
		cout << "cbca: ";
		cbca.print(cout);
		cbca=(std::move(copy_cbbf));
		cout << "moving contents now" << endl;
		for(int i = 0; i < cbca.length(); i++){
			REQUIRE(cbca.item_at(i) == m_cbca.item_at(i));
		}
		cout << "copy_cbbf: ";
		copy_cbbf.print(cout);
		cout << "cbca: ";
		cbca.print(cout);
		REQUIRE(copy_cbbf.length() == 0);
	}
	
	TEST_CASE("testing iterators" , "[iterators]"){
		cout << "\n==========TEST13==========" << endl;
		cop3530::CBL<char> cdit(5);
		cdit.push_back('A');cdit.push_back('A');cdit.push_back('A');cdit.push_back('A');cdit.pop_front();cdit.pop_front();cdit.pop_front();
		cdit.push_back('B');cdit.push_back('C');cdit.push_back('D');cdit.push_back('E');
		cout << "testing iterators on list cdit" << endl;
		cout << "cdit: ";
		cdit.print(cout);
		cop3530::CBL<char>::iterator cditer1 = cdit.begin();
		cout << "\nmade iterator cditer1 point to beginning of cdit" << endl;
		cout << "*cditer1: " << *cditer1 << endl;
		REQUIRE(*cditer1 == cdit.item_at(0));
		
		cout << "\ntesting preincrement on cditer1" << endl;
		++cditer1;
		cout << "*cditer1: " << *cditer1 << endl;
		REQUIRE(*cditer1 == cdit.item_at(1));
		
		cout << "\ntesting postincremement on cditer1" << endl;
		cditer1++;
		cout << "*cditer1: " << *cditer1 << endl;
		REQUIRE(*cditer1 == cdit.item_at(2));
		
		cout << "\ntesting copy constructor for non const iterator" << endl;
		cop3530::CBL<char>::iterator copy_cditer1(cditer1);
		bool cbbool = (copy_cditer1 == cditer1);
		REQUIRE(cbbool == true);
		cout << "*cditer1: " << *cditer1 << endl;
		cout << "*copy_cditer1: " << *copy_cditer1 << endl;
		
		cout << "\ntesting copy assignment for non const iterator" << endl;
		cout << "assigning cditer2 (which points to end) to cditer1" << endl;
		cop3530::CBL<char>::iterator cditer2=cdit.end();
		cbbool = (cditer2 != cditer1);
		REQUIRE(cbbool == true);
		cditer2 = cditer1;
		cbbool = (cditer2 == cditer1);
		REQUIRE(cbbool == true);
		cout << "*cditer2: " << *cditer2 << endl;
		cout << "*cditer1: " << *cditer1 << endl;
		
		cout << "\ntesting enhanced for loop with non-const iterators" << endl;
		int cbi = 0;
		for(auto w : cdit){
			cout << w << "~";
			REQUIRE(w == cdit.item_at(cbi));
			cbi++;
		}
		cout << endl;
		
		cout << "\ntesting const iterators" << endl;
		cout << "making const list const_cdit" << endl;
		const cop3530::CBL<char> const_cdit(cdit);
		cop3530::CBL<char>::const_iterator const_cditer1 = const_cdit.begin();
		cout << "making const iterator called const_cditer1" << endl;
		cout << "const_cditer1: " << *const_cditer1 << endl;
		REQUIRE(*const_cditer1 == cdit.item_at(0));
		cout << "testing preincrement ++const_cditer1" << endl;
		++const_cditer1;
		cout << "const_cditer1: " << *const_cditer1 << endl;
		REQUIRE(*const_cditer1 == cdit.item_at(1));
		
		cout << "\nmaking const iterator called const_cditer2 based off const_cditer1" << endl;
		cop3530::CBL<char>::const_iterator const_cditer2(const_cditer1);
		REQUIRE(*const_cditer2 == *const_cditer1);
		cout << "const_cditer2: " << *const_cditer2 << endl;
		cout << "const_cditer1: " << *const_cditer1 << endl;
		
		cbbool = (const_cditer2 == const_cditer1);
		REQUIRE(cbbool == true);
		
		cout << "\npostincrement const_cditer2" << endl;
		const_cditer2++;
		REQUIRE(*const_cditer2 == cdit.item_at(2));
		cout << "*const_cditer2: " << *const_cditer2 << endl;
		cbbool = (const_cditer2 != const_cditer1);
		REQUIRE(cbbool == true);
		
		cout << "\ntesting assignment for const iterators" << endl;
		cout << "making const_cditer1 = const_cditer2" << endl;
		const_cditer1 = const_cditer2;
		cbbool = (const_cditer2 == const_cditer1);
		REQUIRE(cbbool == true);
		cout << "*const_cditer2: " << *const_cditer2 << endl;
		cout << "*const_cditer1: " << *const_cditer1 << endl;
		
		cout << "\ntesting enhanced for loop wiht const iterators" << endl;
		cbi = 0;
		for(auto w : const_cdit){
			cout << w << "~";
			REQUIRE(w == cdit.item_at(cbi));
			cbi++;
		}
		cout << endl;
	}
	
	
	
	
	
