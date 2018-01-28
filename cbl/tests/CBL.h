#ifndef CBL_H
#define CBL_H
#include "List.h"
#include <iostream>
#include <stdexcept>

using namespace std;
namespace cop3530{
	
template <typename E>
class CBL : public List<E>{
	
	private:
		int maxsize;
		int start_capacity;
		int head;
		int tail;
		E * data;
		E * cont_arr = nullptr;
	
	public:
		CBL(size_t size);								//user defined size
		CBL();											//default size (50)
		CBL(const CBL<E>& other);						//copy constructor
		CBL<E>& operator=(const CBL<E>& other);			//copy assignemnt
		CBL(CBL<E>&& other);							//move constructor
		CBL<E>&& operator=(CBL<E>&& other);				//move assignment
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//iterators
		template <typename DataT>
		class CBL_Iter{
			public:
				// type aliases required for C++ iterator compatibility
				using value_type = DataT;
				using reference = DataT&;
				using pointer = DataT*;
				using difference_type = std::ptrdiff_t;
				using iterator_category = std::forward_iterator_tag;
				
				// type aliases for prettier code
				using self_type = CBL_Iter;
				using self_reference = CBL_Iter&;
			private:
				int here;
				int iter_head;
				int iter_tail;
				int max_size;
				int length;
				E * arrpointer;				//need to set to data in iterator constructor
				
			public:
				explicit CBL_Iter( int start = -1, int niter_head = -1, int niter_tail = -1, int nmax_size = -1, int nlength = -1, E * arr = nullptr)
				: here(start), iter_head(niter_head), max_size(nmax_size), length(nlength), iter_tail(niter_tail), arrpointer(arr){}
				
				CBL_Iter(const CBL_Iter& src)
				: here(src.here), iter_head(src.iter_head), max_size(src.max_size), length(src.length), iter_tail(src.iter_tail), arrpointer(src.arrpointer){}
				
				reference operator*() const{
					if(arrpointer == nullptr){	//should never happen
						throw std::runtime_error("pointer to an array passed in points to null");
					}
					if(here >= length || here < 0){
						throw std::runtime_error("here is not in bounds of list");
					}
					return arrpointer[(here+iter_head)%max_size];
				}
				
				pointer operator->() const{				//derefrences and calls reference(method?)
					return &(operator*());
				}
				
				//this is an assignment operator (not equal)
				self_reference operator=( CBL_Iter<DataT> const& src ){
					if( this == &src ){		
						return( *this );
					}
					here = src.here;
					iter_head = src.iter_head;
					max_size = src.max_size;
					length = src.length;
					iter_tail = src.iter_tail;
					arrpointer = src.arrpointer;
					return *this;
				}
				
				self_reference operator++(){		//preincrement
					if(here >= length){
						throw std::runtime_error("cannot preincrement iterator as it is at tail");
					}
					++here;
					return *this;
				}
				
				self_type operator++(int){			//postincrement
					self_type tmp( *this );
					++(*this);
					return tmp;
				}
				
				bool operator==( CBL_Iter<DataT> const& rhs ) const{
					return (&(arrpointer[(here+iter_head)%max_size]) == &(rhs.arrpointer[(rhs.here+rhs.iter_head)%rhs.max_size]) && here==rhs.here);
				}
				
				bool operator!=( CBL_Iter<DataT> const& rhs ) const{
					return (&(arrpointer[(here+iter_head)%max_size]) != &(rhs.arrpointer[(rhs.here+rhs.iter_head)%rhs.max_size]) || here!=rhs.here);
				}
				
		};
	public:
		//--------------------------------------------------
		// type aliases
		//--------------------------------------------------
		//using size_t = std::size_t; // you may comment out this line if your compiler complains
		using value_type = E;
		using iterator = CBL_Iter<E>;
		using const_iterator = CBL_Iter<E const>;
		
		// iterators over a non-const List
		iterator begin(){								//return  iterator denoting first element 
			return CBL_Iter<E>(0, head, tail, maxsize, length(), data);
		} 
		
		iterator end(){
			return CBL_Iter<E>(length(), head, tail, maxsize, length(), data);
		}
		
		//iterators over a const list
		const_iterator begin() const{
			int x;
			if(head==tail && head!=-1){
				x = maxsize;
				return CBL_Iter<E const>(0, head, tail, maxsize, x, data);
			}
			x = tail - head;
			if(x < 0){
				x = (maxsize - head) + tail;
			}
			
			return CBL_Iter<E const>(0, head, tail, maxsize, x, data);
		}
		
		const_iterator end() const{
			int x;
			if(head==tail && head!=-1){
				x = maxsize;
				return CBL_Iter<E const>(x, head, tail, maxsize, x, data);
			}
			x = tail - head;
			if(x < 0){
				x = (maxsize - head) + tail;
			}
			
			return CBL_Iter<E const>(x, head, tail, maxsize, x, data);
		}
		
		
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		bool is_empty() override;
		bool is_full() override;
		//void print(ostream& os) override;
		ostream& print(ostream& os) override;
		//E item_at(unsigned int position) override;
		E& item_at(int position) override;
		//E peek_back() override;
		E& peek_back() override;
		//E peek_front() override;
		E& peek_front() override;
		size_t length() override;
		//void insert(E element, unsigned int position) override;
		void insert(E element, int position) override;
		void push_front(E element) override;
		void push_back(E element) override;
		//E remove(unsigned int position) override;
		E remove(int position) override;
		E pop_front() override;
		E pop_back() override;
		//E replace(E element, unsigned int position) override;
		E replace(E element, int position) override;
		void clear() override;
		bool contains(E element, bool (*equals_function)(const E& element, const E& value)) override;
		E * contents() override;
		~CBL();
	
	//CBL Specific Functions
		E * arr_bigger(E * arr_data);
		E * arr_smaller(E * arr_data);
		void test_print(ostream& os);
		bool bw_ht(int position);						//checks if position is between head and tail
		int get_size();
		bool ins_bool;
		bool rem_bool;
};
	
//......user_input constructor //====================
template <typename E>
CBL<E>::CBL(size_t size){
	maxsize = size;
	start_capacity = size;
	data = new E[size];
	head = -1;
	tail = -1;
}
//========================//========================
	

//......default constructor //======================
template <typename E>
CBL<E>::CBL(){
	maxsize = 50;
	start_capacity = 50;
	data = new E[50];
	head = -1;
	tail = -1;
}
//========================//========================	


//......copy_constructor //======================
template <typename E>
CBL<E>::CBL(const CBL<E>& other){
	this->maxsize = other.maxsize;
	this->start_capacity = other.start_capacity;
	this->data = new E[other.maxsize];
	this->head = other.head;
	this->tail = other.tail;
	//check if other is not empty
	if(!(other.tail == -1 && other.tail == -1)){
		for(int i = 0; i<this->get_size(); i++){
			this->data[(i+this->head)%maxsize] = other.data[(i+other.head)%maxsize]; 
		}		
	}
}	
//========================//========================	


//......copy_assignment //======================
template <typename E>
CBL<E>& CBL<E>::operator=(const CBL<E>& other){
	this->head = other.head;
	this->tail = other.tail;
	this->maxsize = other.maxsize;
	this->start_capacity = other.start_capacity;
	E * tempdel = this->data;
	this->data = new E[other.maxsize];
	delete[] tempdel;
	if(!(other.tail == -1 && other.tail == -1)){
		for(int i = 0; i<this->get_size(); i++){
			this->data[(i+this->head)%maxsize] = other.data[(i+other.head)%maxsize]; 
		}		
	}
}
//========================//========================	


//......move constructor //======================
template <typename E>
CBL<E>::CBL(CBL<E>&& other){
	//this steals other
	this->maxsize = other.maxsize;
	this->start_capacity = other.start_capacity;
	this->data = other.data;
	this->head = other.head;
	this->tail = other.tail;
	other.data = new E[other.maxsize];
	other.head = -1;
	other.tail = -1;
	//check if other needs to be resize
	if(other.maxsize >= 2*other.start_capacity && other.get_size() < other.maxsize/2){
		E * tempdel = other.data;
		other.data = other.arr_smaller(other.data);
		delete[] tempdel;
	}
}
//========================//========================	


//......move assignment //======================
template <typename E>
CBL<E>&& CBL<E>::operator=(CBL<E>&& other){
	//need to clear this
	E * tempdel = this->data;
	this->data = other.data;
	delete[] tempdel;
	//set this to other
	this->maxsize = other.maxsize;
	this->start_capacity = other.start_capacity;
	this->head = other.head;
	this->tail = other.tail;
	other.data = new E[other.maxsize];
	other.head = -1;
	other.tail = -1;
	//check if other needs to be resize
	if(other.maxsize >= 2*other.start_capacity && other.get_size() < other.maxsize/2){
		E * tempdel1 = other.data;
		other.data = other.arr_smaller(other.data);
		delete[] tempdel1;
	}
}
//========================//========================


//......destructor//================================
template <typename E>
CBL<E>::~CBL(){
	//if(cont_arr){
	//	delete[] cont_arr;
	//}
	delete[] data;
	cout << "CBL object has been destroyed" << endl;
}
//========================//========================	


//......is_empty//==================================
template <typename E>
bool CBL<E>::is_empty(){
	if(head == -1 && tail == -1){
		return true;
	}
	else{
		return false;
	}
}
//========================//========================


//......is_full//===================================
template <typename E>
bool CBL<E>::is_full(){
	return false;
}
//========================//========================


//......print//=====================================
template <typename E>
//void CBL<E>::print(ostream& os){
ostream& CBL<E>::print(ostream& os){
	if(is_empty()){
		os << "<empty list>" << endl;
		return os;
	}	/*
	int i = head;
	os << "[" << data[i];
	i = (i+1)%maxsize;
	while(i%maxsize != (head + get_size())%maxsize){	
		os << "," << data[i];
		i = (i+1)%maxsize;
	}
	os << "]" << endl;*/
	
	os << "[" << data[head%maxsize];
	for(int i = 1; i < get_size(); i++){
		os << "," << data[(head+i)%maxsize];
	}
	os << "]" << endl;
	return os;
}
//========================//========================


//......item_at//===================================
template <typename E>
//E CBL<E>::item_at(unsigned int position){
E& CBL<E>::item_at(int position){
	if(is_empty() || position < 0 || position >= get_size()){
		throw runtime_error("error: cannot use item_at outside of list bounds");
	}
	return data[(head+position)%maxsize];
}
//========================//========================


//......peek_back//===================================
template <typename E>
//E CBL<E>::peek_back(){
E& CBL<E>::peek_back(){
	if(is_empty()){
		throw runtime_error("error: empty list cannot peek");
	}
	return data[(tail-1+maxsize)%maxsize];
}
//========================//========================


//......peek_front//===================================
template <typename E>
//E CBL<E>::peek_front(){
E& CBL<E>::peek_front(){
	if(is_empty()){
		throw runtime_error("error: empty list cannot peek");
	}
	return data[head];
}
//========================//========================


//......length//====================================
template <typename E>
size_t CBL<E>::length(){
	return get_size();
}
//========================//========================


//......insert//====================================
template <typename E>
//void CBL<E>::insert(E element, unsigned int position){
void CBL<E>::insert(E element, int position){
	ins_bool = true;
	//position is less than zero OR position is between head and tail indices 
	if(position < 0 || bw_ht(position) || position > maxsize){
		ins_bool = false;
		throw runtime_error("error: cannot insert outside of list");
		return;
	}
	
	//list is empty
	if(is_empty()){
		if(position != 0){								//only want user to insert at position 0 if empty
			ins_bool = false;
			throw runtime_error("cannot insert outside of list");
			return;
		}
		head = position;
		data[position] = element;
		tail = (position + 1)%maxsize;
		ins_bool = false;
		return;
	}
	
	//list is full
	if(head == tail && head != -1){
		E * tempdel = data;
		data = arr_bigger(data);						//made arr bigger
		delete[] tempdel;								//delete old arr
		/*E val = data[(position+head)%maxsize];
		data[(position+head)%maxsize] = element;
		for(int i = (position + head + 1)%maxsize; i <= tail; i++){
			E val2 = data[i];
			data[i] = val;
			val = val2;
		}
		tail=(tail+1)%maxsize;
		ins_bool = false;
		return;*/
	}
	
	
	/*
	if((tail+1)%maxsize == head && position == tail ){					//filling in last slot before full
		data[(position + head)%maxsize] = element;
		tail=(tail+1)%maxsize;
		ins_bool = false;
		return;
	}
	
	//everything else
	//data[(position + head)%maxsize] = element;
	E val = data[(position + head)%maxsize];
	data[(position + head)%maxsize] = element;
	for(int i = (position + head + 1)%maxsize; i <= tail; i++){
		E val2 = data[i];
		data[i] = val;
		val = val2;
	}
	//}
	tail=(tail+1)%maxsize;
	ins_bool = false;*/
	
	//everything else
	/*int d_pos = (head + position)%maxsize;
	E val1 = data[d_pos];
	data[d_pos] = element;
	//if you just filled in the last slot to make the arr full
	if((tail+1)%maxsize == head && position == tail){
		tail = (tail +1)%maxsize;
		return;
	}
	//if it is wrapped
	if(head > tail){
		int i = (d_pos + 1)%maxsize;
		while(i <= tail){
			E val2 = data[i];
			data[i] = val1;
			val1 = val2;
			i = (i+1)%maxsize;
		}
	}
	//if it is not wrapped
	else{
		cout << "not wrapped" << endl;
		int i = (head + position + 1)%maxsize;
		while(i <= tail){
			E val2 = data[i];
			data[i] = val1;
			val1 = val2;
			i++;
		}
	}
	tail = (tail+1)%maxsize;*/
	
	//everything else take III
	int d_pos = (head + position)%maxsize;
	E val1 = data[d_pos];
	data[d_pos] = element;
	int i = d_pos; 
	int k = position;
	while(k < get_size()){
		E val2 = data[(i+1)%maxsize];
		data[(i+1)%maxsize] = val1;
		val1 = val2;
		i = (i+1)%maxsize; 
		k++;
	}
	tail = (tail + 1)%maxsize;
	
	ins_bool = false;
	return;
}
//========================//========================


//......push_front//================================
template <typename E>
void CBL<E>::push_front(E element){
	insert(element, 0);
	return;
}
//========================//========================


//......push_back//=================================
template <typename E>
void CBL<E>::push_back(E element){
	insert(element, get_size());
	return;
}
//========================//========================


//......remove//====================================
template <typename E>
//E CBL<E>::remove(unsigned int position){				//position is the user's perspective 
E CBL<E>::remove(int position){
	rem_bool = true;
	//position is less than zero OR position is between head and tail indices 
	if(position < 0 || bw_ht(position) || position >= maxsize || is_empty()){
		rem_bool = false;
		throw runtime_error("error: cannot remove outside of list");
	}
	
	//position is at head (user's perspective is 0)
	if(position == 0){
		E val = pop_front();
		return val;
	}
	
	//if position is at 1 before tail (user's perspective is end of their list)
	if(position == (get_size()-1)){
		E val = pop_back();
		return val;
	}
	
	//everything else
	int dr_pos = (head+position)%maxsize;
	E val_tr = data[dr_pos];
	E val1 = data[(dr_pos+1)%maxsize];
	int i = dr_pos;
	int k = position;
	while(k < (get_size()-1)){
		data[i] = val1;
		val1 = data[(i+2)%maxsize];
		i = (i+1)%maxsize;
		k++;
	}
	tail = (tail-1+maxsize)%maxsize;
	//check if need to shrink
	if(maxsize >= 2*start_capacity && get_size() < maxsize/2){
		E * tempdel = data;
		data = arr_smaller(data);
		delete[] tempdel;
	}
	
	//if popped last element in list 
	//head and tail will point to same slot
	//so reset head and tail to -1 to truly make an empty list
	if(head == tail){
		head = -1; tail = -1;
	}
	return val_tr;
	
}
//========================//========================


//......pop_front//=================================
template <typename E>
E CBL<E>::pop_front(){
	if(is_empty()){
		throw runtime_error("error: empty list");
	}
	E val = data[head];
	head = (head + 1)%maxsize;
	//check if need to shrink
	if(maxsize >= 2*start_capacity && get_size() < maxsize/2){
		E * tempdel = data;
		data = arr_smaller(data);
		delete[] tempdel;
	}
	
	//if popped last element in list 
	//head and tail will point to same slot
	//so reset head and tail to -1 to truly make an empty list
	if(head == tail){
		head = -1; tail = -1;
	}
	return val;
}
//========================//========================


//......pop_back//==================================
template <typename E>
E CBL<E>::pop_back(){
	if(is_empty()){
		throw runtime_error("error: empty list");
	}
	E val = data[((tail - 1)+maxsize)%maxsize];
	tail = ((tail - 1)+maxsize)%maxsize;
	//check if need to shrink
	if(maxsize >= 2*start_capacity && get_size() < maxsize/2){
		E * tempdel = data;
		data = arr_smaller(data);
		delete[] tempdel;
	}
	
	//if popped last element in list 
	//head and tail will point to same slot
	//so reset head and tail to -1 to truly make an empty list
	if(head == tail){
		head = -1; tail = -1;
	}
	return val;
}
//========================//========================


//......replace//===================================
template <typename E>
//E CBL<E>::replace(E element, unsigned int position){
E CBL<E>::replace(E element, int position){
	if(position < 0 || position >= get_size()){
		throw runtime_error("error: cannot replace, position out of bounds");
	}
	E val = data[(position+head)%maxsize];
	data[(position+head)%maxsize] = element;
	return val;
}
//========================//========================


//......clear//=====================================
template <typename E>
void CBL<E>::clear(){
	tail = -1;
	head = -1;
	if(maxsize >= 2*start_capacity && get_size() < maxsize/2){
		E * tempdel = data;
		data = arr_smaller(data);
		delete[] tempdel;
	}
	return;
}
//========================//========================


//......contains//==================================
template <typename E>
bool CBL<E>::contains(E element, bool (*equals_function)(const E& element, const E& value)){
	for(int i = 0; i < get_size(); i++){
		if((*equals_function)(element, data[(head + i)%maxsize])){
			return true;
		}
	}
	return false;
}
//========================//========================


//......contents//==================================
template <typename E>
E * CBL<E>::contents(){
	//if(cont_arr){
	//	cout << "deleting old contents array" << endl;
	//	delete[] cont_arr;
	//}
	cont_arr = new E[get_size()];
	for(int i = 0; i < get_size(); i++){
		cont_arr[i] = data[(head+i)%maxsize];
	}
	return cont_arr;
}
//========================//========================


//......CBL SPECIFIC FUNCTIONS========================================================//


//......arr_bigger//================================
template <typename E>
E * CBL<E>::arr_bigger(E * data_arr){
	cout << "arr_bigger-> old maxsize: " << maxsize << endl;
	int old_maxsize = maxsize;							//keep old maxsize
	maxsize = maxsize*1.5;								//update maxsize
	E * new_arr = new E[maxsize];
	int i = head;
	head = 0;
	tail = 0;
	int k = 0;		
	while(k < old_maxsize){								//updating new_arr starting from slot 0
		new_arr[k] = data[i%old_maxsize];
		i++;
		k++;
		tail++;
	}
	cout << "arr_bigger-> new maxsize: " << maxsize << endl;
	return new_arr;
}
//========================//========================


//......arr_smaller//================================
template <typename E>
E * CBL<E>::arr_smaller(E * data_arr){
	cout << "arr_smaller-> old maxsize: " << maxsize << endl;
	int oldmaxsize = maxsize;
	maxsize = maxsize*.75;
	E * new_arr = new E[maxsize];
	if(is_empty()){
		cout << "arr_smaller-> new maxsize: " << maxsize << endl;
		return new_arr;
	}
	int i = head;
	int temp_size = get_size();
	head = 0;
	tail = 0;
	int k = 0;
	while(k < temp_size){
		new_arr[k] = data[i%oldmaxsize];
		i++;
		k++;
		tail = (tail + 1)%maxsize;
	}
	cout << "arr_smaller-> new maxsize: " << maxsize << endl;
	return new_arr;
}
//========================//========================


//......test_print//================================
template <typename E>
void CBL<E>::test_print(ostream& os){
	if(is_empty()){
		os << "<empty list>" << endl;
		return;
	}
	int i = head;
	os << "[" << data[i];
	i = (i+1)%maxsize;
	while(i%maxsize != (head + get_size())%maxsize){	
		os << "," << data[i];
		i = (i+1)%maxsize;
	}
	os << "]" << endl;
	os << "head: " << head << endl;
	os << "tail: " << tail << endl;
	
}
//========================//========================


//......bw_ht//=====================================
template <typename E>
bool CBL<E>::bw_ht(int position){
	//conditions for insert
	if(ins_bool){
		/*if(is_empty() && position == 0){					//list is empty and pos at 0
			return false;									//valid 
		}
	
		if(is_empty() && position != 0){					//list is empty and pos not at 0
			return true;									//not valid
		}
	
		if((!is_empty() && tail == head)){					//list is full 
			return false;									//valid
		}
		
		//check if it is wrapped
		if(head > tail){
			//checks if user input is not within bounds of [head, tail] inclusive
			//not valid
			if(!(position >= 0 && position <= (maxsize-head)+tail)){		
				return true;
			}
			//checks if user input is within bounds of [head, tail] inclusive
			//valid
			if((position >= 0 && position <= (maxsize-head)+tail)){
				return false;
			}
		}
		
		//check if not wrapped
		if(head < tail){
			//check if position user inputs is not between [head, tail] inclusive 
			//not valid
			if(!((position + head)%maxsize >= head && (position + head)%maxsize <= tail)){	
				return true;
			}
			//check if position user inputs is between [head, tail] inclusive 
			//valid
			if(((position + head)%maxsize >= head && (position + head)%maxsize <= tail)){
				return false;
			}
		}*/
		//if position is in bounds of list []
		if(position >= 0 && position <= get_size()){
			return false;
		}
		else{
			return true;
		}
	}
	if(rem_bool){
		/*if(!(is_empty()) && head == tail){
			return false;
		}
		if(position >= tail && position < head){
			return true;
		}*/
		if(position >= 0 && position < get_size()){
			return false;
		}
		else{
			return true;
		}
	}
}
//========================//========================


//......get_size//==================================
template <typename E>
int CBL<E>::get_size(){
	if(head==tail && head!=-1){
		return maxsize;
	}
	int x = tail - head;
	if(x >= 0){
		return x;
	}
	else{
		x = (maxsize - head) + tail;
		return x;
	}
}
//========================//========================
}

#endif 