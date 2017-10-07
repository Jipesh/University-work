#ifndef NODE_H
#define NODE_H

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

template<typename T> class Node {
	

	public:

		Node<T>* previous = nullptr;
		Node<T>* next = nullptr;

		T data;

		Node(const T & dataIn);

		~Node();

};

//	function for class Node<T> defined below	//

	template<typename T>
	Node<T>::Node(const T & dataIn) :
	previous(nullptr),
	next(nullptr),
	data(dataIn){}

	template<typename T>
	Node<T>::~Node(){}

//##########################################################//


template<typename T> class NodeIterator {
  
	private:
    
    	Node<T>* current;
    
	public:

		NodeIterator(Node<T>* currentIn)
		    : current(currentIn) {        
		}

		~NodeIterator();

		void remove();

		void setPrev(const NodeIterator<T> & itterator);

		void setNext(const NodeIterator<T> & itterator);
		
		Node<T>* & getPrev();

		Node<T>* & getCurrent() { return current; }

		Node<T>* & getNext();

		const T & operator*() const{
		    return current->data;
		}

		const NodeIterator<T> & operator++();

		const NodeIterator<T> & operator--();

		const bool operator==(const NodeIterator<T> & another) const{
			return current == another.current;
		}

		const bool operator!=(const NodeIterator<T> & another) const{
			return  current != another.current;
		}


    
};

//	function for NodeIterator<T> defined below	//

	template<typename T>
	NodeIterator<T>::~NodeIterator(){}

	template<typename T>
	void NodeIterator<T>::remove(){
		delete current;
	}

	template<typename T>
	void NodeIterator<T>::setPrev(const NodeIterator<T> & itterator){
		current->previous = itterator.current;
		itterator.current->next = current;
	}

	template<typename T>
	void NodeIterator<T>::setNext(const NodeIterator<T> & itterator){
		current->next = itterator.current;
		itterator.current->previous = current;
	}

	template<typename T>
	Node<T>* & NodeIterator<T>::getPrev(){
		return current->previous;
	}

	template<typename T>
	Node<T>* & NodeIterator<T>::getNext(){
		return current->next;
	}

	template<typename T>
	const NodeIterator<T> & NodeIterator<T>::operator++(){
		
		if(current != nullptr){
			
			current = current->next;
		
		}
		
		return *this;
	}

	template<typename T>
	const NodeIterator<T> & NodeIterator<T>::operator--(){
		
		if(current != nullptr){

			current = current->previous;

		}
		return *this;

	}

//##########################################################//

// do not edit below this line

#endif
