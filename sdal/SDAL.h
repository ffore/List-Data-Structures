#ifndef SDAL_H
#define SDAL_H
#include "List.h"
#include <iostream>
#include <stdexcept>

using namespace std;
namespace cop3530{

template <typename E>
class SDAL : public List<E>{

	private:
		int maxsize;
		int start_capacity;
		//int tail = -1;
		int tail = 0;
		E * data;
		bool add_bool = false;
		bool sub_bool = false;
		E * cont_arr = nullptr;
	public:
		SDAL(size_t size);
		SDAL();
		SDAL(const SDAL<E>& other);						//copy constructor
		SDAL<E>& operator=(const SDAL<E>& other);		//copy assignemnt
		SDAL(SDAL<E>&& other);							//move constructor
		SDAL<E>&& operator=(SDAL<E>&& other);			//move assignment
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//iterators
		template <typename DataT>
		class SDAL_Iter{
			public:
				// type aliases required for C++ iterator compatibility
				using value_type = DataT;
				using reference = DataT&;
				using pointer = DataT*;
				using difference_type = std::ptrdiff_t;
				using iterator_category = std::forward_iterator_tag;

				// type aliases for prettier code
				using self_type = SDAL_Iter;
				using self_reference = SDAL_Iter&;
				
			private:
				int here;
				int iter_tail;
				E * arrpointer;				//need to set to data in iterator constructor
      
			public:
				//since the iterator will rely on tail value passed in constructor
				//therefore if an iterator is called and the list is manipulated
				//the iterator is  no good
				explicit SDAL_Iter(  int start = -1, int niter_tail = -1, E * arr = nullptr ) : here( start ), iter_tail(niter_tail),arrpointer( arr ) { /*cout << "iterator here: " << here << endl;*/}	//what you call from scratch
				SDAL_Iter( const SDAL_Iter& src ) : here( src.here ), iter_tail(src.iter_tail), arrpointer(src.arrpointer) {/*cout << "iterator copy here: " << here << endl;*/}	//make a constructor based off another iterator

				reference operator*() const{			//derefrencing operator
					if(arrpointer == nullptr){
						throw runtime_error("pointer to an array passed in points to null");
					}
					if(here< 0 || here >= iter_tail){
						throw runtime_error("iterator is pointing outside of list"); 
					}
					return arrpointer[here];
				}
				
				pointer operator->() const{				//derefrences and calls reference(method?)
					return &(operator*());
				}
				
				//this is an assignment operator (not equal)
				self_reference operator=( SDAL_Iter<DataT> const& src ){
					if( this == &src ){		
						return( *this );
					}
					here = src.here;
					iter_tail = src.iter_tail;
					arrpointer = src.arrpointer;
					return *this;
				}
				
				self_reference operator++(){			// preincrement
					if(here >= iter_tail){
						throw runtime_error("cannot increment as it is at or past tail now");
					}
					//cout << "using preincrement" << endl;
					++here;								//this = iterator
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
				
				bool operator==( SDAL_Iter<DataT> const& rhs ) const{
					return (arrpointer == rhs.arrpointer && here == rhs.here);			//first check if same array
				}																		//check if same index
				
				bool operator!=( SDAL_Iter<DataT> const& rhs) const{
					return (arrpointer != rhs.arrpointer || here != rhs.here);
				}
		};
	public:
    	//--------------------------------------------------
		// type aliases
		//--------------------------------------------------
		//using size_t = std::size_t; // you may comment out this line if your compiler complains
		using value_type = E;
		using iterator = SDAL_Iter<E>;
		using const_iterator = SDAL_Iter<E const>;
		
		// iterators over a non-const List
		iterator begin(){								//return  iterator denoting first element 
			return SDAL_Iter<E>(0, tail, data);
		} 
		
		iterator end() {
			return SDAL_Iter<E>(tail, tail, data);			
		}
		
		// iterators over a const List
		const_iterator begin() const{								//return  iterator denoting first element 
			return SDAL_Iter<E const>(0, tail, data);
		} 
		
		const_iterator end() const{
			return SDAL_Iter<E const>(tail, tail, data);			 
		}
		
		
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//void insert(E element, unsigned int position) override;
		void insert(E element, int position) override;
		//E item_at(unsigned int position) override;
		E& item_at(int position) override;
		//E remove(unsigned int position) override;
		E remove(int position) override;
		//E replace(E element, unsigned int position) override;
		E replace(E element, int position) override;
		void push_back(E element) override;
		void push_front(E element) override;
		E pop_back() override;
		E pop_front() override;
		//E peek_back() override;
		E& peek_back() override;
		//E peek_front() override;
		E& peek_front() override;
		E * contents() override;
		bool contains(E element, bool (*equals_function)(const E& element, const E& value)) override;
		void clear() override;
		size_t length() override;
		//void print(ostream& os) override;
		ostream& print(ostream& os) override;
		bool is_empty() override;
		bool is_full() override;
		~SDAL();

		//SDAL specific functions
		E* arr_fix(E* arr_data);
		void test_print(ostream& os);

};

//......user_input constructor //========================
template <typename E>
SDAL<E>::SDAL(size_t size){
	start_capacity = size;
	data = new E[size];
	maxsize = size;
	//E * tempdel = data;								//This was before the edit to shrink the backing array
	//sub_bool = true;
	//data = arr_fix(data);								//arr_fix() can alter the sub_bool
	//if(sub_bool){							
	//	delete[] tempdel;
	//}
	//sub_bool = false;
}
//========================//========================


//......default constructor//========================
template <typename E>
SDAL<E>::SDAL(){
	cout << "SDAL regular constructor called" << endl;
	start_capacity = 50;
	data = new E[50];
	maxsize = 50;
}
//========================//========================


//......copy_constructor//========================
template <typename E>
SDAL<E>::SDAL(const SDAL<E>& other){
	cout << "copy constructor called" << endl;
	this->start_capacity = other.start_capacity;
	this->maxsize = other.maxsize;
	this->data = new E[other.maxsize];
	this->tail = other.tail;
	if(this->tail == 0){
		//return;
	}
	else{
		for(int i = 0; i < this->tail; i++){
			this->data[i] = other.data[i];
		}
	}
}
//========================//========================


//......copy_assignment//========================
template <typename E>
SDAL<E>& SDAL<E>::operator=(const SDAL<E>& other){
	cout << "copy assignment called" << endl;
	//need to make this empty
	E * tempdel = this->data;
	this->data = new E[other.maxsize];
	delete[] tempdel;
	this->start_capacity = other.start_capacity;
	this->maxsize = other.maxsize;
	this->tail = other.tail;
	if(other.tail == 0){
		//return;
	}
	else{
		for(int i = 0; i < tail; i++){
			this->data[i] = other.data[i];
		}
	}
}
//========================//========================


//......move_constructor//========================
template <typename E>
SDAL<E>::SDAL(SDAL<E>&& other){
	cout << "move constructor called" << endl;
	//have this steal other's stuff
	this->start_capacity = other.start_capacity;
	this->maxsize = other.maxsize;
	this->tail = other.tail;
	this->data = other.data;
	//make other empty
	other.maxsize = other.start_capacity;
	other.tail = 0;
	other.data = nullptr;
	other.data = new E[other.start_capacity];
	
}
//========================//========================


//......move_assigment//========================
template <typename E>
SDAL<E>&& SDAL<E>::operator=(SDAL<E>&& other){
	cout << "move assignment called" << endl;
	//deallocate and delete this data
	E * tempdel = this->data;
	//make data point to other data
	this->data = other.data;
	delete[] tempdel;
	other.data = nullptr;
	//have this steal other's stuff
	this->start_capacity = other.start_capacity;
	this->maxsize = other.maxsize;
	this->tail = other.tail;
	//make other empty
	other.maxsize = other.start_capacity;
	other.tail = 0;
	other.data = new E[other.start_capacity];
	
	
	
	
}
//========================//========================


//......destructor//========================
template <typename E>
SDAL<E>::~SDAL(){
	//if(cont_arr){
	//	delete[] cont_arr;
	//}
	delete[] data;
	cout << "SDAL object has been destroyed" << endl;
}
//========================//========================


//......insert//========================
template <typename E>
//void SDAL<E>::insert(E element, unsigned int position){
void SDAL<E>::insert(E element, int position){
	if(position > length() || position < 0){
		throw std::runtime_error("error: position is outside of array");
	}
	if(position == length()){
		push_back(element);
		return;
	}
	else{
		add_bool = true;
		E * tempdel = data;
		data = arr_fix(data);							//checks size if at maxsize capacity
		if(add_bool){
			delete[] tempdel;
		}
		add_bool = false;
		E * temp = new E[maxsize];
		tail++;
		for(int i = 0; i < position; i++){
			temp[i] = data[i];
		}
		temp[position] = element;
		//for(int i = position; i<tail; i++){
		for(int i = position; i<(tail-1); i++){	
			temp[i+1] = data[i];
		}
		E * temp2 = data;
		data = temp;
		delete[] temp2;
		return;
	}
}
//========================//========================


//......item_at//========================
template <typename E>
//E SDAL<E>::item_at(unsigned int position){
E& SDAL<E>::item_at(int position){
	//if(position > tail || position < 0){
	if(position > (tail-1) || position < 0){
		throw runtime_error("error: position exceeds list length");
	}
	return data[position];
}
//========================//========================


//......remove//========================
template <typename E>
//E SDAL<E>::remove(unsigned int position){
E SDAL<E>::remove(int position){
	if(is_empty() || position < 0 || position > (tail-1)){
		throw runtime_error("error: cannot remove");
	}
	data = arr_fix(data);
	//if(position == tail){
	if(position == (tail-1)){
		return pop_back();
	}
	if(position == 0){
		return pop_front();
	}
	else{
		E val = data[position];
		E * temp = new E[maxsize];
		tail--;
		for(int i = 0; i <= position; i++){
			temp[i] = data[i];
		}
		//for(int i = position; i <= tail; i++){
		for(int i = position; i <= (tail-1); i++){
			temp[i] = data[i+1];
		}
		E * tempdel = data;
		data = temp;
		delete[] tempdel;
		sub_bool = true;
		E * tempdel2 = data;
		data = arr_fix(data);
		if(sub_bool){
			delete[] tempdel2;
		}
		sub_bool = false;		
		return val;
	}

}
//========================//========================


//......replace//========================
template <typename E>
//E SDAL<E>::replace(E element, unsigned int position){
E SDAL<E>::replace(E element, int position){
	//if(position > tail || position < 0){
	if(position > (tail-1) || position < 0){
		throw runtime_error("error: position exceeds list length");
	}
	E val = data[position];
	data[position] = element;
	return val;
}
//========================//========================


//......push_back//========================
template <typename E>
void SDAL<E>::push_back(E element){
	add_bool = true;
	E * tempdel = data;
	data = arr_fix(data);
	if(add_bool){										//if the data pointer was redirected to a new resized array
		delete[] tempdel;
	}
	add_bool = false;
	//data[tail+1] = element;
	data[tail] = element;
	tail++;
	return;


}
//========================//========================


//......push_front//========================
template <typename E>
void SDAL<E>::push_front(E element){
	add_bool = true;
	E * temp1 = data;
	data = arr_fix(data);
	if(add_bool){										//if the data pointer was redirected to a new resized array
		delete[] temp1;
	}	
	add_bool = false;
	E * temp = new E[maxsize];
	tail++;
	temp[0] = element;
	//for(int i = 0; i < tail; i++){
	for(int i = 0; i < (tail-1); i++){
		temp[i+1]=data[i];
	}
	E * temp2 = data;
	data = temp;
	delete[] temp2;
	return;
}
//========================//========================


//......pop_back//========================
template <typename E>
E SDAL<E>::pop_back(){
	if(is_empty()){
		throw runtime_error("error: empty list, nothing to pop");
	}
	//E val = data[tail];
	E val = data[tail-1];
	tail--;
	sub_bool = true;
	E * tempdel = data;
	data = arr_fix(data);
	if(sub_bool){
		delete[] tempdel;
	}
	sub_bool = false;
	return val;
}
//========================//========================


//......pop_front//========================
template <typename E>
E SDAL<E>::pop_front(){
	if(is_empty()){
		throw runtime_error("error: empty list, nothing to pop");
	}
	E val = data[0];
	//for(int i = 0; i <= tail -1; i++){
	for(int i = 0; i <= tail -2; i++){
		data[i] = data[i+1];
	}
	tail--;
	sub_bool = true;
	E * tempdel = data;
	data = arr_fix(data);
	if(sub_bool){
		delete[] tempdel;
	}
	sub_bool = false;
	return val;
}
//========================//========================


//......peek_back()//========================
template <typename E>
//E SDAL<E>::peek_back(){
E& SDAL<E>::peek_back(){
	if(is_empty()){
		throw runtime_error("error: empty list, nothing to peek");
	}
	//return data[tail];
	return data[tail-1];
}
//========================//========================

//......peek_front//========================
template <typename E>
//E SDAL<E>::peek_front(){
E& SDAL<E>::peek_front(){
	if(is_empty()){
		throw runtime_error("error: empty list, nothing to peek");
	}
	return data[0];
}
//========================//========================


//......contents//========================
template <typename E>
E * SDAL<E>:: contents(){
	//if(cont_arr){
	//	E * tempdel = cont_arr;
	//	cont_arr = nullptr;
	//	delete[] tempdel;
	//}
	cont_arr = new E[tail];
	for(int i = 0; i <= tail-1; i++){
		cont_arr[i] = data[i];
	}
	return cont_arr;
}
//========================//========================


//......contains//========================
template <typename E>
bool SDAL<E>::contains(E element, bool (*equals_function)(const E& element, const E& value)){
	if(is_empty()){
		return false;
	}
	else{
	int i = 0;
	//while(i != tail+1){
	while(i != tail){
		bool cbool = (*equals_function)(element, data[i]);
		if(cbool){
			return true;
		}
		i++;
	}
	return false;
}
}

//========================//========================


//......clear//========================
template <typename E>
void SDAL<E>::clear(){
	if(is_empty()){
		return;
	}
	//tail = -1;
	tail = 0;
	return;
}
//========================//========================


//......length//========================
template <typename E>
size_t SDAL<E>::length(){
	//if(tail == -1){
	if(tail == 0){
		return 0;
	}
	//return tail + 1;
	return tail;
}
//========================//========================


//......print//========================
template <typename E>
//void SDAL<E>::print(ostream& os){
ostream& SDAL<E>::print(ostream& os){
	if(is_empty()){
		os << "<empty list>" << endl;
		return os;
	}
	int i = 0;
	os << "[" << data[i];
	i++;
	//while(i != tail+1){
	while(i != tail){	
		os << "," << data[i];
		i++;
	}
	os << "]" << endl;
	//os << "tail: " << tail << " (filled up to slot " << tail-1 << ")"  << endl;
	return os;
}
//========================//========================


//......is_empty//========================
template <typename E>
bool SDAL<E>::is_empty(){
	//if(tail == -1){
	if(tail == 0){
		return true;
	}
	return false;
}
//========================//========================


//......is_full//========================
template <typename E>
bool SDAL<E>::is_full(){
	return false;
}
//========================//========================


//......SDAL SPECIFIC FUNCTIONS========================================================//

//......arr_fix//========================
template <typename E>
E* SDAL<E>::arr_fix(E* arr_data){
	//edit size if needed when adding
	if(add_bool){
		//if((tail + 1) == maxsize){							//if array is at capacity
		if((tail) == maxsize){
			cout << "alert arr_fix: making array 150% of original size" << endl;
			maxsize = (maxsize*1.5);
			cout << "new maxsize: " << maxsize << endl;
			E * ndata = new E[maxsize];
			int i = 0;
			//while(i != tail+1){
			while(i != tail){
				ndata[i] = arr_data[i];
				i++;
			}
			return ndata;
		}
		add_bool = false;
	}
	//edit size if needed when removing
	if(sub_bool){
		//if( maxsize >= 100 && (tail + 1) < maxsize/2 ){ //tail is at wrong pos
		//if( maxsize >= 100 && (tail) < maxsize/2 ){	//tail is at correct pos but old shrinking condition
		if( maxsize >= start_capacity*2 && tail < maxsize/2 ){
			cout << "alert arr_fix: making array 75% of original size" << endl;
			maxsize *= .75;
			cout << "new maxsize: " << maxsize << endl;
			E * ndata = new E[maxsize];
			int i = 0;
			//while(i != tail+1){
			while(i != tail){
				ndata[i] = arr_data[i];
				i++;
			}
			return ndata;
		}
		sub_bool = false;
	}
	return arr_data;
}
//========================//========================


//......test_print//========================
template <typename E>
void SDAL<E>::test_print(ostream& os){
	if(is_empty()){
		os << "<empty list>" << endl;
		return;
	}
	int i = 0;
	os << "[" << data[i];
	i++;
	//while(i != tail+1){
	while(i != tail){	
		os << "," << data[i];
		i++;
	}
	os << "]" << endl;
	os << "tail: " << tail << " (filled up to slot " << tail-1 << ")"  << endl;
	return;
}
//========================//========================


}
#endif
