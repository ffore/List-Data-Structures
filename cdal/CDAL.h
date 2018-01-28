#ifndef CDAL_H
#define CDAL_H
#include "List.h"
#include <iostream>
#include <stdexcept>

using namespace std;
namespace cop3530{
	
template <typename E>
class CDAL : public List<E>{
	private: 
		struct Node{
			E * arr = new E[50];
			Node * next = nullptr;
		};
		Node * data;
		//int tail = -1;
		int tail = 0;
		E * cont_arr = nullptr;
	public:
		CDAL();											//regular constructor
		CDAL(const CDAL<E>& other);						//copy constructor
		CDAL<E>& operator=(const CDAL<E>& other);		//copy assignemnt
		CDAL(CDAL<E>&& other);							//move constructor
		CDAL<E>&& operator=(CDAL<E>&& other);			//move assignment
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//iterators
		template <typename DataT>
		class CDAL_Iter{
			public:
				// type aliases required for C++ iterator compatibility
				using value_type = DataT;
				using reference = DataT&;
				using pointer = DataT*;
				using difference_type = std::ptrdiff_t;
				using iterator_category = std::forward_iterator_tag;
				
				// type aliases for prettier code
				using self_type = CDAL_Iter;
				using self_reference = CDAL_Iter&;
				
			private:
				Node * here;
				int iter_pos;
				int iter_tail;				//need to set to data in iterator constructor
			
			public:
				explicit CDAL_Iter(  Node * start = nullptr, int fiter_pos = -1, int fiter_tail = -1) 
				: here( start ), iter_pos( fiter_pos ), iter_tail( fiter_tail ) { 
					//cout << "iterator here: " << here << endl;
					//cout << "iter_pos: " << iter_pos << endl;
					//cout << "iter_tail: " << iter_tail << endl;
					int pos_node = iter_pos/50;
					for(int i = 0; i < pos_node; i++){
						if(here->next){
							here = here->next;
						}
					}
				}	//what you call from scratch
				
				CDAL_Iter( const CDAL_Iter& src ) 	//make a constructor based off another iterator
				: here( src.here ), iter_pos( src.iter_pos ), iter_tail( src.iter_tail ) {
					//cout << "iterator copy here: " << here << endl;
					}	
				
				
				reference operator*() const{			//derefrencing operator
					if(here == nullptr){
						throw std::runtime_error("node pointer passed in points to null");
					}
					return here->arr[iter_pos%50];
				}
				
				pointer operator->() const{				//derefrences and calls reference(method?)
					return &(operator*());
				}
				
				//this is an assignment operator (not equal)
				//setting an iterator equal to another
				self_reference operator=( CDAL_Iter<DataT> const& src ){
					if( this == &src ){		
						return( *this );
					}
					here = src.here;
					iter_pos = src.iter_pos;
					iter_tail = src.iter_tail;
					return *this;
				}
				
				
				self_reference operator++(){			// preincrement
					if(iter_pos >= iter_tail){
						throw std::runtime_error("cannot increment as it is at or past tail now");
					}
					//cout << "using preincrement" << endl;
					if((iter_pos+1)%50 == 0 ){
						//cout << "moved" << endl;
						here = here -> next;
					}		
					++iter_pos;
					return *this;
				}
				
				self_type operator++(int){				// postincrement
					//cout << "using postincrement" << endl;
					self_type tmp( *this );				//creates copy of the iterator (calls iterator constructor)
					++(*this);							//calls preincrement on original iterator
					return tmp;							//returns copy
				}
				
				bool operator==( CDAL_Iter<DataT> const& rhs ) const{											//check if same node
					return (/*&here->arr[iter_pos%50] == &rhs.here->arr[rhs.iter_pos%50] && */iter_pos==rhs.iter_pos);		//& same val at same slot
				}
				
				bool operator!=( CDAL_Iter<DataT> const& rhs ) const{											//check if !same node
					return (/*&here->arr[iter_pos%50] != &rhs.here->arr[rhs.iter_pos%50] ||*/ iter_pos!=rhs.iter_pos);	//or !same val at !same slot
				}
		
		};
	public:
    	//--------------------------------------------------
		// type aliases
		//--------------------------------------------------
		//using size_t = std::size_t; // you may comment out this line if your compiler complains
		using value_type = E;
		using iterator = CDAL_Iter<E>;
		using const_iterator = CDAL_Iter<E const>;
		
		// iterators over a non-const List
		iterator begin(){								//return  iterator denoting first element 
			return CDAL_Iter<E>(data, 0, tail);
		} 
		
		// iterators over a non-const List
		iterator end(){								//return  iterator denoting one past last element 
			return CDAL_Iter<E>(data, tail, tail);
		} 
		
		// iterators over a const List
		const_iterator begin() const{								//return  iterator denoting first element 
			return CDAL_Iter<E const>(data, 0, tail);
		}
		
		// iterators over a const List
		const_iterator end() const{								//return  iterator denoting one past last element 
			return CDAL_Iter<E const>(data, tail, tail);
		}
		
	
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		bool is_empty() override;
		bool is_full() override;
		size_t length() override;
		void push_back(E element) override;
		void push_front(E element) override;
		//void insert(E element, unsigned int position) override;
		void insert(E element, int position) override;
		E pop_back() override;
		E pop_front() override;
		//E peek_back() override;
		E& peek_back() override;
		//E peek_front() override;
		E& peek_front() override;
		//E remove(unsigned int position) override;
		E remove(int position) override;
		//E replace(E element, unsigned int position) override;
		E replace(E element, int position) override;
		//E item_at(unsigned int position) override;
		E& item_at(int position) override;		
		E * contents() override;
		bool contains(E element, bool (*equals_function)(const E& element, const E& value)) override;
		//void print(ostream& os) override;
		ostream& print(ostream& os) override;
		void clear() override;
		
		//CDAL specific
		unsigned int get_node_number();
		void test_print(ostream& os);
		void waste_check();
		~CDAL();
};
//......constructor//========================
template <typename E>
CDAL<E>::CDAL(){
	cout << "CDAL regular constructor called" << endl;
	data = new Node;
}
//========================//========================


//......copy_constructor//========================
template <typename E>
CDAL<E>::CDAL(const CDAL<E>& other){
	//this copies contents of other array 
	this->tail = other.tail;
	if(other.data){
		this->data = new Node;
		for(int i = 0; i<=49; i++){
			this->data->arr[i] = other.data->arr[i];
		}
		Node * temp_other = other.data;
		Node * temp_this = this->data;
		while(temp_other->next){
			temp_other = temp_other->next;
			temp_this->next = new Node;
			temp_this = temp_this->next;
			for(int i = 0; i<=49; i++){
				temp_this->arr[i] = temp_other->arr[i];
			}
		}
	}
}
//========================//========================


//......copy_assignment//========================
template <typename E>
CDAL<E>& CDAL<E>::operator=(const CDAL<E>& other){
	this->clear();
	if(other.data){
		this->tail = other.tail;
		for(int i = 0; i<=49; i++){
				this->data->arr[i] = other.data->arr[i];
		}
		Node * temp_other = other.data;
		Node * temp_this = this->data;
		while(temp_other->next){
			temp_other = temp_other->next;
			temp_this->next = new Node;
			temp_this = temp_this->next;
			for(int i = 0; i<=49; i++){
				temp_this->arr[i] = temp_other->arr[i];
			}
		}
	}
}
//========================//========================


//......move_constructor//========================
template <typename E>
CDAL<E>::CDAL(CDAL<E>&& other){
	//have this steal other's stuff
	this->tail = other.tail;
	if(other.data){
		this->data = other.data;
		other.tail=0;
		other.data=new Node;
	}
	else{
		other.tail = 0;
	}
	//give other a new node (
}
//========================//========================


//......move_assignment//========================
template <typename E>
CDAL<E>&& CDAL<E>::operator=(CDAL<E>&& other){
	this->clear();
	if(other.data){
		this->tail=other.tail;
		other.tail = 0;
		Node * tempdel = this->data;
		this->data=other.data;
		delete[] tempdel->arr;
		delete tempdel;
		other.data = new Node;
	}
	else{
		other.tail = 0;
	}
}
//========================//========================


//......destructor//========================
template <typename E>
CDAL<E>::~CDAL(){
	//cout << "========DESTRUCTOR==================" << endl;
	//if(cont_arr){
	//	cout << "deleting contents array at address: " << &(*cont_arr) << endl;
	//	delete[] cont_arr;
	//}
	int i = 0;
	if(data){
		while(data -> next){
			//cout << i << "a" << endl;
			Node * curr = data;
			//cout << i << "b" << endl;
			data = data -> next;
			//cout << i << "c" << endl;
			//cout << "Deleting Node # " << i << " at address: " << &(*curr) << endl;
			delete[] curr->arr;
			delete curr;
			i++;
			//cout << endl;
		}
		//cout << "Deleting Node # " << i << " at address: " << &(*data) << endl;
		delete[] data->arr;
		//cout << "a" << endl;
		delete data;
	}
	cout << "CDAL object has been destroyed." << endl;
	//cout << "====================================" << endl;
}
//========================//========================


//......is_empty//========================
template <typename E>
bool CDAL<E>::is_empty(){
	//if(tail == -1){
	if(tail == 0){
		return true;
	}
	return false;
}
//========================//========================


//......is_full//========================
template <typename E>
bool CDAL<E>::is_full(){
	return false;
}
//========================//========================


//......length//========================
template <typename E>
size_t CDAL<E>::length(){
	//return tail+1;
	return tail;
}
//========================//========================


//......push_back//========================
template <typename E>
void CDAL<E>::push_back(E element){
	//insert(element, tail+1);
	insert(element, tail);
	return;
	
}
//========================//========================


//......push_front//========================
template <typename E>
void CDAL<E>::push_front(E element){
		insert(element, 0);
		return;
	//}
}
//========================//========================


//......insert//========================
template <typename E>
//void CDAL<E>::insert(E element, unsigned int position){
void CDAL<E>::insert(E element, int position){	
	if(position > length() || position < 0){
		throw runtime_error("error: position is outside of length of list");
	}
	unsigned int insert_node = position/50;
	Node * Tdata = data;
	//Move Tdata to insert_node
	for(int i = 0; i < insert_node; i++){
		if(!(Tdata -> next)){
			Tdata -> next = new Node;
		}
		
		Tdata = Tdata -> next;
	}
	
	//inserting element at position
	E oldv = Tdata -> arr[position%50];
	E oldv2;
	Tdata -> arr[position%50] = element;
	bool is_last = false;
	//for(int i = position; i <= tail; i++){
	for(int i = position; i <= tail-1; i++){	
		//if(position == tail){							//&{|}&\\//&{|}&\\//&{|}&\\//&{|}&
		if(position == tail-1){
			is_last = true;								//why is position not i?
		}
		if(i % 50 == 49){
			if(Tdata -> next == nullptr){
				Tdata -> next = new Node;
			}
			Tdata = Tdata -> next;
		}
		if(!is_last){
			oldv2 = Tdata -> arr[(i+1)%50];
		}
		Tdata -> arr[(i+1)%50] = oldv;
		if(!is_last){
			oldv = oldv2;
		}
	}
	tail++;
	return;
}
//========================//========================


//......pop_back//========================
template <typename E>
E CDAL<E>::pop_back(){
	//return remove(tail);
	return remove(tail-1);
}
//========================//========================


//......pop_front//========================
template <typename E>
E CDAL<E>::pop_front(){
	return remove(0);
}
//========================//========================


//......peek_back//========================
template <typename E>
//E CDAL<E>::peek_back(){
E& CDAL<E>::peek_back(){
	if(is_empty()){
		throw runtime_error("error: empty list");
	}
	//return item_at(tail);
	return item_at(tail-1);
}
//========================//========================


//......peek_front//========================
template <typename E>
//E CDAL<E>::peek_front(){
E& CDAL<E>::peek_front(){
	if(is_empty()){
		throw runtime_error("error: empty list");
	}
	return item_at(0);
}
//========================//========================


//......remove//========================
template <typename E>
//E CDAL<E>::remove(unsigned int position){
E CDAL<E>::remove(int position){
	if(position > length() || position < 0 || is_empty()){
		throw runtime_error("error: position is outside of length of list");
	}
	unsigned int target_node = position/50;
	Node * Tdata = data;
	
	//make Tdata point to node that contains position
	if(target_node > 0){
		for(int i = 0; i != target_node; i++){
			Tdata = Tdata -> next;
		}
	}
	E val_tr = Tdata -> arr[position % 50];
	//check if at end
	if(position==tail-1){
		tail--;
		waste_check();
		return val_tr;
	}
	E xnext;
	E xnext2;
	////////
	//set xnext
	if((position + 1) % 50 == 0){
		xnext = (Tdata -> next) -> arr[0];
	}
	else{
		xnext = Tdata -> arr[(position + 1) % 50];
	}
	
	//for(int i = position; i <= tail-1; i++){
	for(int i = position; i <= tail-2; i++){	
		//set xnext2
		if((i + 2) % 50 == 0){//if i is at 2nd to last slot
			if(Tdata->next){
				xnext2 = (Tdata -> next) -> arr[0];
			}
			Tdata -> arr[48] = xnext;
			xnext = xnext2;
		}
		else if((i + 2) % 50 == 1){//if i is at last slot
			if(Tdata->next){
				xnext2 = (Tdata -> next) -> arr[1];
			}
			Tdata -> arr[49] = xnext;
			xnext = xnext2;
			Tdata = Tdata -> next;
		}
		else{				//if i is anywhere else
			xnext2 = Tdata -> arr[(i + 2) % 50];
			Tdata -> arr[i % 50] = xnext;
			xnext = xnext2;
		}
	}
	tail--;
	waste_check();
	return val_tr;
}
//========================//========================


//......replace//========================
template <typename E>
//E CDAL<E>::replace(E element, unsigned int position){
E CDAL<E>::replace(E element, int position){
	if(is_empty()){
		throw runtime_error("error: empty list");
	}
	if(position > length() || position < 0){
		throw runtime_error("error: position is not in bounds of list");
	}
	
	//make temp point to node where position is
	unsigned int node_number = position/50;
	Node * temp = data;
	int i = 0;
	while(i != node_number){
		temp = temp -> next;
		i++;
	}
	E val = temp -> arr[position % 50];
	temp -> arr[position % 50] = element;
	return val;
}
//========================//========================


//......item_at//========================
template <typename E>
//E CDAL<E>::item_at(unsigned int position){
E& CDAL<E>::item_at(int position){
//const E& CDAL<E>::item_at(unsigned int position) const{
	if(is_empty()){
		throw runtime_error("error: empty list");
	}
	if(position > length() || position < 0){
		throw runtime_error("error: position is not in bounds of list");
	}
	//make temp point to node where position is
	unsigned int interest_node = position/50;
	Node * temp = data;
	int i = 0;
	while(i != interest_node){
		temp = temp -> next;
		i++;
	}
	return temp -> arr[position % 50];
}
//========================//========================

/*
//const
//......item_at//========================
template <typename E>
const E& CDAL<E>::item_at(int position) const{
	
	
}
//========================//========================
*/

//......contents//========================
template <typename E>
E * CDAL<E>::contents(){
	//if(cont_arr){
	//	cout << "deleting old contents array" << endl;
	//	delete[] cont_arr;
	//}
	//cont_arr = new E[tail+1];
	cont_arr = new E[tail];
	int i = 0;
	//while(i != tail + 1){
	//while(i < tail+1){
	while(i < tail){
		cont_arr[i] = item_at(i);
		i++;
	}
	cout << "made cont_arr at address: " << &(*cont_arr) << endl;
	return cont_arr;
}
//========================//========================


//......contains//========================
template <typename E>
bool CDAL<E>:: contains(E element, bool (*equals_function)(const E& element, const E& value)){
	if(is_empty()){
		return 1;
		//cout << "error: empty list" << endl;
	}
	Node * temp = data;
	bool cbool;
	//unsigned int lf_node = tail/50;
	unsigned int lf_node = (tail-1)/50;
	unsigned int i = 0;
	while(i != lf_node){
		//for(int i = 0; i <= tail % 49; i++){
		for(int i = 0; i <= (tail-1) % 49; i++){	
			cbool = (*equals_function)(element, temp -> arr[i]);
			if(cbool){
				return true;
			}
		}
		i++;
	}
	//last node
	//for(int i = 0; i <= tail % 49; i++){
	for(int i = 0; i <= (tail-1) % 49; i++){
		cbool = (*equals_function)(element, temp -> arr[i]);
		if(cbool){
			return true;
		}
	}
	return false;
}
//========================//========================


//......print//========================
template <typename E>
//void CDAL<E>::print(ostream& os){
ostream& CDAL<E>::print(ostream& os){
	if(is_empty()){
		os << "<empty list>" << endl;
		//return;
		return os;
	}
	
	//int node_count = tail/50;
	int node_count = (tail-1)/50;
	//if there is 1 node
	os << "[";
	if(node_count == 0){
		os << data -> arr[0];
		//for(int i = 1; i <= tail; i++){
		for(int i = 1; i <= tail-1; i++){	
			os << "," << data -> arr[i];
		}
		os << "]" << endl;
		//return;
		return os;
	}
	//if there are >1 nodes
	//prints out in seperate arrays
	Node * temp = data;
	int i = 0;
	while(i != node_count){
		os << temp -> arr[0];
		for(int i = 1; i <= 49; i++){
			os << "," << temp -> arr[i];
		}
		os << ",";
		//os << "]\n" << "next array..." << endl; 
		temp = temp -> next;
		i++;
	}
	//last node 
	os << temp -> arr[0];
	//for(int i = 1; i <= tail%50; i++){
	for(int i = 1; i <= (tail-1)%50; i++){	
		os << "," << temp -> arr[i];
	}
	os << "]" << endl;
	//os << "Node count is up to node #" << node_count << endl;
	//return;
	return os;
	
}
//========================//========================

//......clear//========================
template <typename E>
void CDAL<E>::clear(){
	//idea:
	//delete all but start node and set tail to -1
	Node * temp;
	cout << "node_count before clear: " << get_node_number() << endl;
	//tail = -1;
	tail = 0;
	//if data points to nothing (no nodes) should never happen
	if(data == nullptr){
		cout << "node_count after clear: " << get_node_number() << endl;
		return;
	}

	//if data points to only one node
	if(data -> next == nullptr){
		cout << "node_count after clear: " << get_node_number() << endl;
		return;
	}
	
	//if data points to >1 nodes
	temp = data->next;
	data -> next = nullptr;
	while(temp -> next){
		Node * tempdel = temp;
		temp = temp -> next;
		tempdel -> next = nullptr;
		cout << "clear: deleting node at: " << &(*tempdel) << endl;
		delete[] tempdel->arr;
		delete tempdel;
	}
	cout << "clear: deleting node at: " << &(*temp) << endl;
	delete[] temp->arr;
	delete temp;
	cout << "node_count after clear: " << get_node_number() << endl;
	return;
}
//========================//========================


//......CDAL SPECIFIC FUNCTIONS========================================================//

//......get_node_number//========================
template <typename E>
unsigned int CDAL<E>::get_node_number(){
	if(is_empty()){
		return 0;
	}
	unsigned int node_number = 0;
		Node * temp = data;
		while(temp -> next != nullptr){
			temp = temp -> next;
			node_number++;
		}
	return node_number;
	
}
//========================//========================


//......test_print//========================
template <typename E>
void CDAL<E>::test_print(ostream& os){
	os << "printing now...\n" <<"tail is at: " << tail << "(filled up to slot " << tail-1 << ")"  << endl;
	if(is_empty()){
		os << "<empty list>" << endl;
		return;
	}
	
	//int node_count = tail/50;
	int node_count = (tail-1)/50;
	//if there is 1 node
	if(node_count == 0){
		cout << "Node's address: " << &(*data) << endl;
		os << "[" << data -> arr[0];
		//for(int i = 1; i <= tail; i++){
		for(int i = 1; i <= (tail-1); i++){
			os << "," << data -> arr[i];
		}
		os << "]" << endl;
		os << "Filled up to node #" << node_count << endl;
		return;
	}
	
	//if there are >1 nodes
	//prints out in seperate arrays
	Node * temp = data;
	int i = 0;
	while(i != node_count){
		cout << "Node's address: " << &(*temp) << endl;
		os << "[";
		os << temp -> arr[0];
		for(int i = 1; i <= 49; i++){
			os << "," << temp -> arr[i];
		}
		os << "]\n" << "next array..." << endl; 
		temp = temp -> next;
		i++;
	}
	//last node 
	cout << "Node's address: " << &(*temp) << endl;
	os << "[" << temp -> arr[0];
	//for(int i = 1; i <= tail%50; i++){
	for(int i = 1; i <= (tail-1)%50; i++){
		os << "," << temp -> arr[i];
	}
	os << "]" << endl;
	os << "Filled up to node #" << node_count << endl;
	return;
	}
//========================//========================

//......waste_check//========================
template <typename E>
void CDAL<E>::waste_check(){
	if(is_empty()){
		return;
	}
	size_t node_count = get_node_number();

	Node * temp;
	//size_t lf_node = tail/50;							//last filled node
	size_t lf_node = (tail-1)/50;
	/*if((node_count / 2) > lf_node){						//if more than half of allocated nodes are unused
		cout << "waste_check: node_count before resize: "<< node_count << endl;
		//size_t nodes_tokeep = ((node_count - lf_node)/2)+ lf_node; //deallocate half of unused nodes
		size_t nodes_tokeep = node_count - ((node_count - lf_node)/2); //deallocate half of unused nodes
		
		cout << "Keep all nodes up to and including node # " << nodes_tokeep <<endl;
		temp = data;
		int i = 1;
		while(i <= nodes_tokeep){
			temp = temp -> next;
			cout << "Keeping node # " << i << endl;
			i++;
		}
		Node * tempdel = temp -> next;
		temp -> next = nullptr;

		while(tempdel -> next){
			Node * tempdel2 = tempdel;
			tempdel = tempdel -> next;
			tempdel2 -> next = nullptr;
			cout << "Deleting node # " << i << " at address: " << &(*tempdel2) << endl;
			i++;
			delete[] tempdel2->arr;
			delete tempdel2;
			cout << endl;
		}
		cout << "Deleting node # " << i << " at address: " << &(*tempdel) << endl;
		delete[] tempdel->arr;
		delete tempdel;
		//this is to check node_count after trim
		cout << "waste_check: node_count after resize: " << get_node_number() << endl;
	}*/
	//new resize condition: "the chain shall contain at most 1 empty array"
	if(node_count-lf_node > 1){
		cout << "resizing list..." << endl;
		cout << "node count (starting at 0) before: " << get_node_number() << endl;
		temp = data;
		for(int i = 0; i <= lf_node; i++){
			temp = temp->next;
		}
		Node * temptemp = temp->next;
		temp->next = nullptr;
		while(temptemp){
			Node * tempdel = temptemp;
			temptemp = temptemp->next;
			delete[] tempdel->arr;
			delete tempdel;
		}
		cout << "node count (starting at 0) after: " << get_node_number() << endl;
	}
	
	return;
}
//========================//========================

}
#endif