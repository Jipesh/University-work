#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <initializer_list>

#include "node.h"


template<typename T> class LinkedList {

	private:

		Node<T>* _head;
		Node<T>* _tail;

		int _size;

		void clearList();

	public:

		LinkedList();

		LinkedList(const std::initializer_list<T> & list);

		~LinkedList();

		void push_front(const T & data);

		void push_back(const T & data);

		const int & size() const{
			return _size;
		}

		const T & front() const{
			return _head->data;
		}

		const T & back() const{
			return _tail->data;
		}

		NodeIterator<T> begin() const{
			return NodeIterator<T> (_head);
		}

		NodeIterator<T> end() const{
			NodeIterator<T> nodeIterator (_tail);
			return ++nodeIterator;
		}

		const NodeIterator<T> erase(NodeIterator<T> NodeIterator);

		const NodeIterator<T> insert(NodeIterator<T> NodeIterator
			, const T & data);
};

//	function for class LinkedList<T> defined below	//


	//	--	public functions	--	//

	template<typename T>
	LinkedList<T>::LinkedList() :
		_head(nullptr),
		_tail(nullptr),
		_size(0)
		{}

	template<typename T>
	LinkedList<T>::LinkedList(const std::initializer_list<T> & list) :
		_head(nullptr),
		_tail(nullptr),
		_size(0){
		
			for(auto & n : list){
				
				push_back(n);
			
			}

	}


	template<typename T>
	LinkedList<T>::~LinkedList(){

		if(size() > 0){
			
			clearList();
		
		}
	}

	template<typename T>
	void LinkedList<T>::push_front(const T & data){
		
		Node<T>* node = new Node<T>(data);
				
		if(_size == 0){
					
			_head = _tail;
			_tail = node;
			
		}else{

			node->next = _head; //set the next of the new node to the head
			_head->previous = node;

		}

		_head = node; //updates head
		++_size;

	}

	template<typename T>
	void LinkedList<T>::push_back(const T & data){

		Node<T>* node = new Node<T>(data);
				
		if(_size == 0){
					
			_tail = _head;
			_head = node;
			
		}else{

			node->previous = _tail; //set the previous of the new node to the tail
			_tail->next = node;

		}

		_tail = node; //updates tail
		++_size;

	}

	template<typename T>
	const NodeIterator<T> LinkedList<T>::erase(NodeIterator<T> nodeIterator){

		if(size() < 1){

			return NodeIterator<T> (_head);

		}else if(size() == 1){

			--_size;

			_head = nullptr;

			_tail = nullptr;

			return begin();
		
		}else {


			if(*(nodeIterator) == _head->data){

				NodeIterator<T> toDelte = _head;

				_head = _head->next;

				toDelte.remove();

				--_size;

				return begin();

			}else if(*(nodeIterator) == _tail->data){

				NodeIterator<T> toDelte = _tail;

				_tail = _tail->previous;

				toDelte.remove();

				--_size;

				return NodeIterator<T> (_tail);

			}else{


				NodeIterator<T> duplicate = nodeIterator;

				NodeIterator<T> next = ++duplicate;

				--duplicate;

				next.setPrev(--duplicate);

				nodeIterator.remove();

				--_size;

				return next;

			}

		}
	}

	template<typename T>
	const NodeIterator<T> LinkedList<T>::insert(NodeIterator<T> nodeIterator
		,const T & data){

		if(size() == 0){

			push_back(data);

			return begin();

		}else{

			if(*(nodeIterator) == _head->data){

				push_front(data);

				return NodeIterator<T> (_head);

			}else{

				Node<T>* node = new Node<T>(data);

				NodeIterator<T> temp (node);

				NodeIterator<T> currentPos = nodeIterator;

				temp.setPrev(--nodeIterator);

				temp.setNext(currentPos);

				++_size;

				return temp;

			}
		}
	}

	//	--	private functions	--	//

	template<typename T>
	void LinkedList<T>::clearList(){

		NodeIterator<T> nodeIterator = begin();

		for(int i = 0 ; i < size() ; ++i){
			
			Node<T>* node = nodeIterator.getCurrent();

			++nodeIterator;

			delete node;
		}
	}

//##########################################################//

// do not edit below this line

#endif
