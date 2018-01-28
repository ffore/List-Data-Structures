#ifndef SSLL_H	
#define SSLL_H
#include "List.h"
#include <iostream>
#include <stdexcept>

using namespace std;
namespace cop3530{
	
template <typename E> 
class SSLL : public List<E>{
	
	private: 											
		struct Node{
			E data;										
			Node * next = nullptr;
		};
		Node * head;
		Node * tail;
		E * cont_arr = nullptr;
	public:
		SSLL();											//constructor
		SSLL(const SSLL<E>& other);						//copy constructor
		SSLL<E>& operator=(const SSLL<E>& other);		//copy assignemnt
		SSLL(SSLL<E>&& other);							//move constructor	
		SSLL<E>&& operator=(SSLL<E>&& other);			//move assignment
		~SSLL();										//destructor
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////		
		template <typename DataT>
		class SSLL_Iter{
			public:
				// type aliases required for C++ iterator compatibility
				using value_type = DataT;
				using reference = DataT&;
				using pointer = DataT*;
				using difference_type = std::ptrdiff_t;
				using iterator_category = std::forward_iterator_tag;

				// type aliases for prettier code
				using self_type = SSLL_Iter;
				using self_reference = SSLL_Iter&;
      
			private:
				Node* here;
      
			public:
				explicit SSLL_Iter( Node* start = nullptr ) : here( start ) { /*cout << "iterator here: " << here << endl;*/}	//what you call from scratch
				SSLL_Iter( const SSLL_Iter& src ) : here( src.here ) {/*cout << "iterator copy here: " << here << endl;*/}			//make a constructor based off another iterator	
      
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
				self_reference operator=( SSLL_Iter<DataT> const& src ){
					if( this == &src ){		
					return( *this );
					}
					here = src.here;
					return *this;
				}
		
				self_reference operator++(){			// preincrement
					if(here == nullptr){
						throw std::runtime_error("cannot preincrement as here points to nullptr");
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
      
				bool operator==( SSLL_Iter<DataT> const& rhs ) const{
					return (here == rhs.here); 
				}
				bool operator!=( SSLL_Iter<DataT> const& rhs) const{
					return (here != rhs.here);
				}
				//}
		}; 
			// end SSLL_Iter
		
	public:
    	//--------------------------------------------------
		// type aliases
		//--------------------------------------------------
		using size_t = std::size_t; // you may comment out this line if your compiler complains
		using value_type = E;
		using iterator = SSLL_Iter<E>;
		using const_iterator = SSLL_Iter<E const>;
		
		// iterators over a non-const List
		iterator begin(){								//return  iterator denoting first element 
			return SSLL_Iter<E>(head);
		} 
		iterator end() {
			return SSLL_Iter<E>(nullptr);			//had as tail->next//return itterator denoting 1 past the last element 
		} 											//put nullptr if making iterator on empty list (nullptr always follows tail)

		// iterators over a const List
		const_iterator begin() const {
			return SSLL_Iter<E const>(head);					//return  const_iterator denoting first element
		}  
		const_iterator end() const {
			return SSLL_Iter<E const>(nullptr);			//had as tail->next//return  const_iterator denoting 1 past the last element ;
		} 												//put nullptr if making iterator on empty list (nullptr always follows tail)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		size_t length() override;									
		bool is_empty() override;									
		bool is_full() override;										
		//E item_at(unsigned int position) override;
		E& item_at(int position) override;
		//void insert(E element, unsigned int position) override;
		void insert(E element, int position) override;
		void push_back(E element) override;							
		void push_front(E element) override;							
		//E replace(E element, unsigned int position) override;					
		E replace(E element, int position) override;
		//E remove(unsigned int position) override;
		E remove(int position) override;
		E pop_back() override;										
		E pop_front() override;										
		void clear() override;									
		//E peek_back() override;										
		E& peek_back() override;
		//E peek_front() override;								
		E& peek_front() override;
		//void print(ostream& os) override;
		ostream& print(ostream& os) override;
		const ostream& print(ostream& os) const;
		
		//bool contains(E element, bool (*equals_function)(E element, E value)) override;
		bool contains(E element, bool (*equals_function)(const E& element, const E& value)) override;
		E * contents() override;
		void test_print(ostream& os);
		

};
//......copy_constructor//========================
template <typename E>
SSLL<E>::SSLL(const SSLL<E>& other){			//this=means the list i am making ||other = the list i am passing in
	cout << "copy constructor called" << endl;
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


//......copy_assignment//========================
template <typename E>
SSLL<E>& SSLL<E>::operator=(const SSLL<E>& other){
	//need to clear lhs(this) before setting it equal to rhs(other)
	this->clear();
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
SSLL<E>::SSLL(SSLL<E>&& other){							//don't want a const list to be passed in as we
//SSLL<E>::SSLL(SSLL<E>&& other){						//want to edit the source(other)
	cout << "move constructor called" << endl;
	//make this point to everything in other 
	//make other point to null (steal)
	
	
	/*if(other.is_empty()){
		this->clear();
	}
	else{
		this->clear();
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
		other.clear();*/
		this->head = other.head;
		other.head = nullptr;
		this->tail = other.tail;
		other.tail = nullptr;
	//}
}
//========================//========================


//......move_assignment//========================
template <typename E>
SSLL<E>&& SSLL<E>::operator=(SSLL<E>&& other){
	cout << "move assignment called" << endl;
	//clear this
	//make this point to everything in other 
	//make other point to null (steal)
	
	/*if(other.is_empty()){
		this->clear();
	}
	else{
		this->clear();
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
		other.clear();
	}*/
	this->clear();
	this->head = other.head;
	other.head = nullptr;
	this->tail = other.tail;
	other.tail = nullptr;
	
}
//========================//========================


//......constructor//========================
template <typename E>
SSLL<E>::SSLL(){
	cout << "SSLL regular constructor called" << endl;
	head = nullptr;											
	tail = nullptr;										
}
//========================//========================

//......destructor//========================
template <typename E>
SSLL<E>::~SSLL(){
	while(head){
		Node * curr = head;
		head = head -> next;
		delete curr;
	}
	delete head;
	if(cont_arr){
		//delete[] cont_arr;
	}
	cout << "SSLL object has been destroyed " << endl;
}
//========================//========================

//......length()//========================
template <typename E>
size_t SSLL<E>::length(){
	size_t count = 0;
	
	if(head == nullptr){
		return count;
	}
	Node * temp = head;
	while(temp -> next){
		temp = temp -> next;
		count++;
	}
	return count+1;
}
//========================//========================

//......is_empty//========================
template <typename E>
bool SSLL<E>::is_empty(){
	if(head == nullptr){
		return true;
	}
	else
		return false;
}
//========================//========================

//......is_full//========================
template <typename E>
bool SSLL<E>::is_full(){
	return false;
}
//========================//========================

//......item_at//========================
template <typename E>
//E SSLL<E>::item_at(unsigned int position){
E& SSLL<E>::item_at(int position){	
	if(position >= length() || position < 0){
		throw std::runtime_error("item_at error: position is outside of list");									//catch is in main
		//cout << "error: position is outside of list" << endl;
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

//......insert//========================
template <typename E>
//void SSLL<E>::insert(E element, unsigned int position){			//this will probably need a lot of ridiculous case testing
void SSLL<E>::insert(E element, int position){
	if(position > length() || position < 0){
		throw std::runtime_error("insert error: position is outside of list");
	}
	int temp_length = length();
	if(position == 0){
		push_front(element);
		return;
	}
	Node * temp = new Node;
	temp -> data = element;
	Node * pre;											//insert after this node
	Node * curr = head;									//insert before this node
	for(unsigned int i = 0; i < position; i++){
		pre = curr;
		curr = curr -> next;
	}
	pre -> next = temp;
	temp -> next = curr;
	if(position == temp_length){ 
		tail = temp;
	}
	return;
}
//========================//========================

//......push_back//========================
template <typename E>
void SSLL<E>::push_back(E element){
	Node * temp = new Node;
	temp -> data = element;
	temp -> next = nullptr;								//makes the node that temp is pointing to, point to 0 (new node is now tail)
	if(is_empty()){										
		head = temp;
		tail = temp;
		//temp = nullptr;
	}
	else{
		tail -> next = temp;
		tail = temp;		
	}
	return;
}
//========================//========================

//......push_front//========================
template <typename E>
void SSLL<E>::push_front(E element){
	Node * temp = new Node;
	temp -> data = element;
	if(is_empty()){										
		//temp -> next = nullptr;
		head = temp;
		tail = temp;
	}
	else{
		temp -> next = head;
		head = temp;
	}
	return;
}
//========================//========================

//......replace//========================
template <typename E>
//E SSLL<E>::replace(E element, unsigned int position){
E SSLL<E>::replace(E element, int position){
	if(is_empty() || position > length()-1 || position < 0){
		throw std::runtime_error("error: cannot use replace");
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

//......remove//========================
template <typename E>
//E SSLL<E>::remove(unsigned int position){
E SSLL<E>::remove(int position){
	if(is_empty() || position > length()-1 || position < 0){
		throw std::runtime_error("error: cannot use remove");
	}
	Node * curr = head;
	if(position == 0 && length() == 1){					//removing first and only node
		E val = head -> data;
		head = nullptr;
		tail = nullptr;
		delete curr;
		return val;
	}
	if(position == 0){									//removing first node in several
		E val = curr -> data;
		head = head -> next;
		curr -> next = nullptr;
		delete curr;
		return val;
	}
	if(position == length()-1){							//removing tail node in several
		int i = 0;
		while(i < position-1){
			curr = curr -> next;
			i++;
		}
		Node * tempdel = curr -> next;
		E val = tempdel -> data;
		curr -> next = nullptr;
		tail = curr;
		delete tempdel;
		return val;
	}
	Node * pre;
	for(unsigned int i = 0; i < position; i++){
		pre = curr;
		curr = curr -> next;
	}
	E val = curr -> data;
	pre -> next = curr -> next;
	curr -> next = nullptr;
	delete curr;
	return val;
}
//========================//========================

//......pop_back//========================
template <typename E>
E SSLL<E>::pop_back(){
	return remove(length()-1);
}
//========================//========================

//......pop_front//========================
template <typename E>
E SSLL<E>::pop_front(){
	return remove(0);
}
//========================//========================

//......clear//========================
template <typename E>
void SSLL<E>::clear(){
	if(is_empty()){										//just in case clear on empty list
		return;
	}
	Node * temp = head;
	head = nullptr;
	tail = nullptr;
	while(temp -> next){
		Node * tempdel = temp;
		temp = temp -> next;
		delete tempdel;
	}
	delete temp;
	return;
}
//========================//========================

//......peek_back//========================
template <typename E>
//E SSLL<E>::peek_back(){
E& SSLL<E>::peek_back(){	
	if(is_empty()){
		throw std::runtime_error("error: can't peek back");
	}
	return tail -> data;
}
//========================//========================

//......peek_front//========================
template <typename E>
//E SSLL<E>::peek_front(){
E& SSLL<E>::peek_front(){	
	if(is_empty()){
		throw std::runtime_error("error: can't peek front");
	}
	return head -> data;
}
//========================//========================

//......print//========================
template <typename E>
//void SSLL<E>::print(ostream& os){
ostream& SSLL<E>::print(ostream& os){	
	if(is_empty()){										//if list is empty, don't print
		os << "<empty list>" << endl;
		return os;
	}
	Node * temp = head;
	os << "[" << temp -> data;
	temp = temp -> next;
	while(temp){
		os << "," << temp -> data;
		temp = temp -> next;
	}
	os << "]";
	//os << "\n";
	//os << "head points to: " << head->data << endl;
	//os << "tail points to: " << tail->data << endl;
	return os;
}
//========================//========================

//......CONST print//========================
template <typename E>
const ostream& SSLL<E>::print(ostream& os) const {
	//if(is_empty()){										//if list is empty, don't print
	//	os << "<empty list>" << endl;
	//	return os;
	//}
	Node * temp = head;
	os << "[" << temp -> data;
	temp = temp -> next;
	while(temp){
		os << "," << temp -> data;
		temp = temp -> next;
	}
	os << "]";
	return os;
}
//========================//========================

//......contains//========================
template <typename E>
//bool SSLL<E>::contains(E element,bool (*equals_function)(E element, E value)){
bool SSLL<E>::contains(E element,bool (*equals_function)(const E& element, const E& value)){
	if(is_empty()){
		return false;
	}
	Node * temp = head;
	while(temp){
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
E * SSLL<E>::contents(){
	//if(cont_arr){
	//	E * temp = cont_arr;
	//	cont_arr = nullptr;
		//delete[] temp;
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


//......test_print//========================
template <typename E>
void SSLL<E>::test_print(ostream& os){
	if(is_empty()){										//if list is empty, don't print
		os << "<empty list>" << endl;
		return;
	}
	Node * temp = head;
	os << "[" << temp -> data;
	temp = temp -> next;
	while(temp){
		os << "," << temp -> data;
		temp = temp -> next;
	}
	os << "]";
	os << "\n";
	os << "head points to: " << head->data << endl;
	os << "tail points to: " << tail->data << endl;
	return;
}

}

#endif