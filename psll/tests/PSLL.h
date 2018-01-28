#ifndef PSLL_H
#define PSLL_H
#include "List.h"
#include <iostream>
#include <stdexcept>

using namespace std;
namespace cop3530{

template <typename E>
class PSLL : public List<E>{

	private:
		struct Node{
			E data;
			Node * next = nullptr;
		};
		Node * head;
		Node * tail;
		Node * free;
		E * cont_arr = nullptr;
		
	public:
		PSLL();
		PSLL(const PSLL<E>& other);						//copy constructor
		PSLL<E>& operator=(const PSLL<E>& other);		//copy assignment
		PSLL(PSLL<E>&& other);							//move constructor
		PSLL<E>&& operator=(PSLL<E>&& other);			//move assignment
		~PSLL();
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//iterators
		template <typename DataT>
		class PSLL_Iter{
			public:
				// type aliases required for C++ iterator compatibility
				using value_type = DataT;
				using reference = DataT&;
				using pointer = DataT*;
				using difference_type = std::ptrdiff_t;
				using iterator_category = std::forward_iterator_tag;

				// type aliases for prettier code
				using self_type = PSLL_Iter;
				using self_reference = PSLL_Iter&;
				
			private:
				Node* here;
      
			public:
				explicit PSLL_Iter( Node* start = nullptr ) : here( start ) { /*cout << "iterator here: " << here << endl;*/}	//what you call from scratch
				PSLL_Iter( const PSLL_Iter& src ) : here( src.here ) {/*cout << "iterator copy here: " << here << endl;*/}			//make a constructor based off another iterator	
      
				reference operator*() const{			//derefrencing operator
					if(here==nullptr){
						throw std::runtime_error("iterator error: iterator points to nullptr");
					}
					return here->data;
				}
				
				pointer operator->() const{				//derefrences and calls method
					return &(operator*());
				}	
		
				//this is an assignment operator (not equal)
				self_reference operator=( PSLL_Iter<DataT> const& src ){
					if( this == &src ){		
					return( *this );
					}
					here = src.here;
					return *this;
				}
		
				self_reference operator++(){			// preincrement
					if(here == nullptr){
						throw std::runtime_error("cannot increment iterator");
					}
					//cout << "using preincrement" << endl;
					here = here->next;					//this = iterator
														//here = node
														//could have seg fault if return nullptr
					return *this;
				} 
      
				self_type operator++(int){				// postincrement
					//cout << "using postincrement" << endl;
					self_type tmp( *this );				//creates copy of the iterator (calls iterator constructor)
					++(*this);							//calls preincrement on original iterator
					return tmp;							//returns copy
				} 
      
				bool operator==( PSLL_Iter<DataT> const& rhs ) const{
					return (here == rhs.here); 
				}
				bool operator!=( PSLL_Iter<DataT> const& rhs) const{
					return (here != rhs.here);
				}
				//}
				
		};//end psll iter
	public:
    	//--------------------------------------------------
		// type aliases
		//--------------------------------------------------
		using size_t = std::size_t; // you may comment out this line if your compiler complains
		using value_type = E;
		using iterator = PSLL_Iter<E>;
		using const_iterator = PSLL_Iter<E const>;
		
		// iterators over a non-const List
		iterator begin(){								//return  iterator denoting first element 
			return PSLL_Iter<E>(head);
		}
		iterator end() {
			return PSLL_Iter<E>(nullptr);			//had as tail->next//return itterator denoting 1 past the last element 
		} 											//put nullptr if making iterator on empty list (nullptr always follows tail)

		// iterators over a const List
		const_iterator begin() const {
			return PSLL_Iter<E const>(head);					//return  const_iterator denoting first element
		}  
		const_iterator end() const {
			return PSLL_Iter<E const>(nullptr);			//had as tail->next//return  const_iterator denoting 1 past the last element ;
		} 												//put nullptr if making iterator on empty list (nullptr always follows tail)
		
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		bool is_empty() override;
		bool is_full() override;
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
		void clear() override;
		size_t length() override;
		//E item_at(unsigned int position) override;
		E& item_at(int position) override;
		bool contains(E element, bool(*equals_function)(const E& element, const E& value)) override;
		E* contents() override;
		//void print(ostream& os) override;
		ostream& print(ostream& os) override;
		
		//PSLL specific functions
		bool ispool_empty();
		void pool_check();
		bool pool_bool();
		size_t plength();
		void test_print(ostream& os);
		
		
};

//......constructor//========================
template <typename E>
PSLL<E>::PSLL(){
	cout << "PSLL regular constructor called" << endl;
	head = nullptr;
	tail = nullptr;
	free = nullptr;
}
//========================//========================

//......copy_constructor//========================
template <typename E>
PSLL<E>::PSLL(const PSLL<E>& other){					
	cout << "copy constructor called" << endl;			//replicate others data chain
	if(other.head == nullptr){							//give this an empty pool
		this->head = nullptr;
		this->tail = nullptr;
		this->free = nullptr;
	}
	else{
		this->head = new Node;						
		this->head->data = other.head->data;
		Node * temp_this = this->head;
		Node * temp_other = other.head;
		while(temp_other->next){
			temp_other = temp_other->next;
			temp_this->next = new Node;
			temp_this = temp_this->next;
			temp_this->data = temp_other->data;
		}
		this->tail = temp_this;
		this->free = nullptr;
	}
}
//========================//========================

//......copy_assignemnt//========================
template <typename E>
PSLL<E>& PSLL<E>::operator=(const PSLL<E>& other){
	//need to clear lhs(this) before setting equal to rhs(other)
	cout << "copy assignment called" << endl;			
	//deallocate existing data chain in this
	//copy data chain from other
	//keep this's original free pool
	
	//delete this's nodes
	Node * temp_this = this->head; 
	this->head = nullptr;
	while(temp_this->next){
		Node * tempdel = temp_this;
		temp_this = temp_this->next;
		delete tempdel;
	}
	delete temp_this;
	
	//copy other's info into this
	if(other.head == nullptr){
		this->head = nullptr;
		this->tail = nullptr;
		//return;
	}
	else{
		this->head = new Node;						
		this->head->data = other.head->data;
		Node * temp_this = this->head;
		Node * temp_other = other.head;
		while(temp_other->next){
			temp_other = temp_other->next;
			temp_this->next = new Node;
			temp_this = temp_this->next;
			temp_this->data = temp_other->data;
		}
		this->tail = temp_this;
	}
}
//========================//========================

//......move_constructor//========================
template <typename E>
PSLL<E>::PSLL(PSLL<E>&& other){
	//this steals other's info
	this->head = other.head;
	this->tail = other.tail;
	this->free = other.free;
	//other's info is deallocated
	other.head = nullptr;
	other.tail = nullptr;
	other.free = nullptr;
}
//========================//========================

//......move_assignment//========================
template <typename E>
PSLL<E>&& PSLL<E>::operator=(PSLL<E>&& other){
	//this steals everything from other
	
	//clear this
	this->clear();
	if(this->free){
		Node * free_temp = free;
		free = nullptr;
		while(free_temp->next){
			Node * tempdel = free_temp;
			free_temp = free_temp->next;
			delete tempdel;
		}
		delete free_temp;
	}
	//this steals other's info
	this->head = other.head;
	this->tail = other.tail;
	this->free = other.free;
	//other's info is deallocated
	other.head = nullptr;
	other.tail = nullptr;
	other.free = nullptr;
}
//========================//========================

//......destructor//========================
template <typename E>
PSLL<E>::~PSLL(){
	if(head){
		while(head){
			Node * curr = head;
			head = head -> next;
			delete curr;
		}
		delete head;
	}
	if(free){
		while(free){
			Node * curr = free;
			free = free ->next;
			delete curr;
		}
		delete free;
	}
	//if(cont_arr){
	//	delete[] cont_arr;
	//}
	cout << "PSLL object has been destroyed " << endl;
}
//========================//========================

//......is_empty//========================
template <typename E>
bool PSLL<E>::is_empty(){
	if (head == nullptr && tail == nullptr){
		return true;
	}
	else{
		return false;
	}
}
//========================//========================


//......is_full//========================
template <typename E>
bool PSLL<E>::is_full(){
	return false;
}
//========================//========================


//......push_back//========================
template <typename E>
void PSLL<E>::push_back(E element){
	insert(element, length());
	return;
}
//========================//========================


//......push_front//========================
template <typename E>
void PSLL<E>::push_front(E element){
	insert(element, 0);
	return;	
} 
//========================//========================


//......insert//========================
template <typename E>
//void PSLL<E>::insert(E element, unsigned int position){
void PSLL<E>::insert(E element, int position){
	if(position > length() || position < 0){
		throw std::runtime_error("error: position exceeds list length");
		return;
	}
	if(ispool_empty()){
		if(position == 0){
			if(is_empty()){
				//if(position == 0){							//inserting in empty list
					Node * temp = new Node;
					head = temp;
					tail = temp;
					head -> data = element;
					return;
				//}
			}
			else{
				Node * temp = new Node;
				temp -> data = element;
				temp -> next = head;
				head = temp;
				return;
			}
		}
		else if(position == length()){						//inserting at end of list
			Node * temp = new Node;
			tail -> next = temp;
			tail = temp;
			tail -> next = nullptr;
			tail -> data = element;
			return;
		}
		else{
			Node * pre;							//insert after this node
			Node * curr = head;					//insert before this node
			Node * temp = new Node;
			for(int i = 0; i < position; i++){
				pre = curr;
				curr = curr -> next;
			}
			pre -> next = temp;
			temp -> next = curr;
			temp -> data = element;
			return;
		}
	}
	else{												//if pool is !empty
		if(position == 0){
			if(is_empty()){
				head = free;
				tail = free;
				free = free -> next;
				head -> next = nullptr;
				head -> data = element;
				return;
			}
			else{
				Node * curr = head;
				head = free;
				free = free -> next;
				head -> next = curr;
				head -> data = element;
				return;
			}
		}
		else if(position == length()){
			tail -> next = free;
			tail = free;
			free = free -> next;
			tail -> next = nullptr;
			tail -> data = element;
			return;
		}
		else{
			Node * pre;									//insert after this node
			Node * curr = head;							//insert before this node
			Node * temp;
			for(int i = 0; i < position; i++){
				pre = curr;
				curr = curr -> next;
			}
			temp = free;
			pre -> next = temp;
			free = free -> next;
			temp -> next = curr;
			temp -> data = element;
			return;
		}
	}
}
//========================//========================


//......pop_back//========================
template <typename E>
E PSLL<E>::pop_back(){
	if(is_empty()){
		throw std::runtime_error("error cannot pop_back");
	}
	Node * temp = head;
	if(length()==1){
		head = nullptr;
		tail = nullptr;
		temp -> next = free;
		free = temp;
		E val = free -> data;
		pool_check();
		return val;
	}
	Node * tempfree = tail;
	for(int i = 0; i < length()-2; i++){
		temp = temp -> next;
	}
	tail = temp;
	tail -> next = nullptr;
	tempfree -> next = free;
	free = tempfree;
	E val = free -> data;
	pool_check();
	return val;
}
//========================//========================

//......pop_front()//========================
template <typename E>
E PSLL<E>::pop_front(){
	if(is_empty()){
		throw std::runtime_error("error: empty list, cannot pop_front");
	}
	if(length() == 1){
		head -> next = free;
		free = head;
		head = nullptr;
		tail = nullptr;
		E val = free -> data;
		pool_check();
		return val;
	}
	else{
		Node * tempfree = head;
		head = tempfree -> next;
		tempfree -> next = free;
		free = tempfree;
		E val = free -> data;
		pool_check();
		return val;
	}
}
//========================//========================


//......peek_back()//========================
template <typename E>
//E PSLL<E>::peek_back(){
E& PSLL<E>::peek_back(){
	if(is_empty()){
		throw std::runtime_error("cannot peek back");
	}
	return tail -> data;
}
//========================//========================

//......peek_front()//========================
template <typename E>
//E PSLL<E>::peek_front(){
E& PSLL<E>::peek_front(){
	if(is_empty()){
		throw std::runtime_error("cannot peek front");
	}
	return head -> data;
}
//========================//========================


//......remove//========================
template <typename E>
//E PSLL<E>::remove(unsigned int position){
E PSLL<E>::remove(int position){
	if(is_empty() || position >= length() || position < 0){
		throw std::runtime_error("remove error: position out of bounds");;
	}
	if(position == 0){						//if removing first and only node
		return pop_front();
	}
	else if(position == length()-1){
		return pop_back();
	}
	Node * curr = head;
	Node * pre;
	for(int i = 0; i < position; i++){
		pre = curr;
		curr = curr -> next;
	}
	pre -> next = curr -> next;
	curr -> next = free;
	free = curr;
	E val = free -> data;
	pool_check();
	return val;
}
//========================//========================


//......replace//========================
template <typename E>
//E PSLL<E>::replace(E element, unsigned int position){
E PSLL<E>::replace(E element, int position){	
	if(is_empty() || position > length()-1 || position < 0){
		throw std::runtime_error("error: cannot replace");
	}
	Node * temp = head;
	int i = 0;
	while(i != position){
		temp = temp -> next;
		i++;
	}
	E val = temp -> data;
	temp -> data = element;
	return val;
	
}
//========================//========================


//......clear()//========================
template <typename E>
void PSLL<E>::clear(){
	//deletes all nodes in list
	//and puts them all in pool
	//call resize
	/*Node * temp = head;
	head = nullptr;
	tail = nullptr;
	while(temp){
		Node * curr = temp;
		temp = temp -> next;
		delete curr;
	}
	delete temp;
	Node * ftemp = free;
	free = nullptr;
	while(ftemp){
		Node * curr = ftemp;
		ftemp = ftemp ->next;
		delete curr;
	}
	delete ftemp;*/
	if(is_empty()){
		return;
	}
	if(free){
		Node * freeback = free;
		while(freeback->next){
			freeback = freeback->next;
		}
	
		freeback->next = head;
		head = nullptr;
		tail = nullptr;
		pool_check();
	}
	else{
		free = head;
		head = nullptr;
		tail = nullptr;
		pool_check();
	}
	
	return;
}
//========================//========================


//......length()//========================
template <typename E>
size_t PSLL<E>::length(){
	size_t count = 0;
	Node * temp = head;
	if(temp == nullptr){
		return count;
	}
	else{
		while(temp != nullptr){
			temp = temp -> next;
			count++;
		}
		return count;
	}
}
//========================//========================


//......item_at//========================
template <typename E>
//E PSLL<E>::item_at(unsigned int position){
E& PSLL<E>::item_at(int position){
	if(is_empty() || position > length()-1 || position < 0){
		throw std::runtime_error("error: cannot use item_at" );
	}
	else{
		Node * flag = head;
		for(unsigned int i = 0; i < position; i++){
			flag = flag -> next;
		}
		return flag -> data;
	}
}
//========================//========================


//......contains//========================
template <typename E>
bool PSLL<E>::contains(E element, bool(*equals_function)(const E& element, const E& value)){
	Node * temp = head;
	while(temp != nullptr){
		bool cbool = (*equals_function)(element, temp -> data);
		if(cbool){
			return true;
		}
		temp = temp -> next;
	}
	return false;
}
//========================//========================


//......contents//========================
template <typename E>
E* PSLL<E>::contents(){
	//if(cont_arr){
	//	E * temp = cont_arr;
	//	cont_arr = nullptr;
	//	delete[] temp;
	//}
	cont_arr = new E[length()];
	Node * temp = head;
	int i = 0;
	while(temp){
		cont_arr[i] = temp -> data;
		temp = temp -> next;
		i++;
	}
	
	return cont_arr;
}
//========================//========================


//......print//========================
template <typename E>
//void PSLL<E>::print(ostream& os){
ostream& PSLL<E>::print(ostream& os){
	if(is_empty()){										//if list is empty, don't print
		os << "<empty list>" << endl;
		//os << "pool length: " << plength() << endl; 	//maybe delete later, included for main666
		return os;
	}
	Node * temp = head;
	os << "[" << temp -> data;
	temp = temp -> next;
	while(temp != nullptr){
		os << "," << temp -> data;
		temp = temp -> next;
	}
	os << "]";
	//******debugging************//
	//os << "\n";
	//os << "head: " << head -> data << endl;
	//os << "tail: " << tail -> data << endl;
	//os << "free: " << free << endl;
	//os << "pool length: " << plength() << endl;
	return os;
}
//========================//========================


//......ispool_empty//========================
template <typename E>
bool PSLL<E>::ispool_empty(){
	if (free == 0){
		return true;
	}
	else{
		return false;
	}
}
//========================//========================


//......pool_check//========================
template <typename E>
void PSLL<E>::pool_check(){
	/*if(pool_bool()){
		cout << "pool_check: pool length before: " << plength() << endl;
		int new_psize = plength() - (length()/2);
		Node * tempfree = free;
		int counter = 0;
		//cout << "alert: pool_check resized pool" << endl;
		while(new_psize != counter){
			free = tempfree -> next;
			tempfree -> next = nullptr;
			delete tempfree;
			Node * tempfree = free;
			counter++;
		}
		cout << "pool_check: pool length after: " << plength() << endl;
		return;
	}
	else 
		return;*/
	if(pool_bool()){
		cout << "Resizing pool back to max capacity (50 nodes)" << endl;
		int del_count = plength() - 50;
		for(int i = 0; i < del_count; i++){
			Node * temp = free;
			free = free -> next;
			delete temp;
		}
		return;
		}
	else{
		return;
	}
}
//========================//========================


//......pool_bool//========================
template <typename E>
bool PSLL<E>::pool_bool(){
	/*if(length() >= 100 && plength() > length()/2){
		return true;
	}
	else{
		return false;
	}*/
	if(plength() > 50){
		return true;
	}
	else{
		return false;
	}
}
//========================//========================


//......plength//========================
template <typename E>
size_t PSLL<E>::plength(){
	size_t count = 0;
	Node * temp = free;
	if(temp == nullptr){
		return count;
	}
	else{
		while(temp != nullptr){
			temp = temp -> next;
			count++;
		}
		return count;
	}
}
//========================//========================


//......test_print//========================
template <typename E>
void PSLL<E>::test_print(ostream& os){
	if(is_empty()){										//if list is empty, don't print
		os << "<empty list>" << endl;
		os << "pool length: " << plength() << endl; 	//maybe delete later, included for main666
		return;
	}
	Node * temp = head;
	os << "[" << temp -> data;
	temp = temp -> next;
	while(temp != nullptr){
		os << "," << temp -> data;
		temp = temp -> next;
	}
	os << "]";
	//******debugging************//
	os << "\n";
	os << "head: " << head -> data << endl;
	os << "tail: " << tail -> data << endl;
	//os << "free: " << free << endl;
	os << "pool length: " << plength() << endl;
	return;
}
//========================//========================

}

#endif