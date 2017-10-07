#ifndef TREENODE_H
#define TREENODE_H

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
using std::ostream;

#include <memory>
using std::unique_ptr;

#include <utility>
using std::pair;

// ~~ Debug code unrelated to coursework ~~ //

#define DEBUG 0

#if DEBUG

	template <typename T>
	void logD(T t){ // prints single value
	    
		std::cout << t;
	}

	template<typename T, typename... Args>
	void logD(T t, Args... args){ // recursive variadic function
	    
		logD(t);
	    logD(args...) ;
	}

	template<typename T, typename... Args>
	void logDLn(T t){ // recursive variadic function without new line

	    logD(t);
	    std::cout << std::endl;
	}

	template<typename T, typename... Args>
	void logDLn(T t, Args... args){ // recursive variadic function with new line

	    logD(t,args...);
	    std::cout << std::endl;
	}

#define mLog(format, ...) printf(format, ##__VA_ARGS__);
#define logD(start, ...) logD(start, ##__VA_ARGS__)
#define logDLn(start, ...) logDLn(start, ##__VA_ARGS__)
#else
#define mLog(format, ...)
#define logD(start, ...)
#define logDLn(start, ...)
#endif

//##################################################################################//

template<typename T>
class TreeNode {

	private:

		static bool _VAR_;

		const bool _HEAP_ = _VAR_;

	public:

		unique_ptr<TreeNode<T>> rightChild = nullptr;

		unique_ptr<TreeNode<T>> leftChild = nullptr;

		T data;

		TreeNode<T>* parent = nullptr;

		TreeNode(const T & dataIn);

		~TreeNode();

		static void* operator new(size_t size);

		void write(ostream & o) const;

		void setLeftChild(TreeNode<T>* node);

		void setRightChild(TreeNode<T>* node);
	
		const bool & isOnHeap(){ return _HEAP_; }

		bool operatorbool() const{ return this == nullptr; }
};

template<typename T>
bool TreeNode<T>::_VAR_ = false;

//  ##  functions for TreeNode<T> defined bellow  ##  //

	//  --  public functions  --  //

	template<typename T>
	TreeNode<T>::TreeNode(const T & dataIn):
	data(dataIn){

		if(_VAR_) _VAR_ = false;
	}

	template<typename T>
	TreeNode<T>::~TreeNode(){}

	template<typename T>
	void TreeNode<T>::write(ostream & o) const{

		if(leftChild.get()) leftChild.get()->write(o);

		o << " " << data << " ";
		
		if(rightChild.get()) rightChild.get()->write(o);
	}

	template<typename T>
	void TreeNode<T>::setLeftChild(TreeNode<T>* node){

		leftChild.reset(node);
		node->parent = this;
	}

	template<typename T>
	void TreeNode<T>::setRightChild(TreeNode<T>* node){

		rightChild.reset(node);
		node->parent = this;
	}

	template<typename T>
	static void* TreeNode<T>::operator new(size_t size){
		
		_VAR_ = true;

		return ::operator new(size);
	}

//###############################################################//

template<typename T>
class TreeNodeIterator {

	private:

		TreeNode<T>* current;

	public:

		TreeNodeIterator(TreeNode<T>* node);

		const T & operator*() const{ return current->data; }

		bool operator==(const TreeNodeIterator<T> & another) const{ return current == another.current; }

		bool operator!=(const TreeNodeIterator<T> & another) const{ return current != another.current; }

		const TreeNodeIterator<T> operator++();
};

// ## functions for TreeNodeIterator<T> defined bellow  ##  //

	//  --  public functions  --  //

	template<typename T>
	TreeNodeIterator<T>::TreeNodeIterator(TreeNode<T>* node):
	current(node){}

	template<typename T>
	const TreeNodeIterator<T> TreeNodeIterator<T>::operator++(){
			
			if(!current) { 
				
				logDLn("I am null");
				
				return *this;
			}
			
			TreeNode<T>* currentPos = current;

			if(current == nullptr) return *this;

			bool searching = true;

			while(searching){

				if(currentPos->rightChild){

					currentPos = currentPos->rightChild.get();

					if(currentPos->leftChild){

						currentPos = currentPos->rightChild.get();

						do{

							if(currentPos->leftChild) currentPos = currentPos->leftChild.get();

							else break;

						}while(searching);

					}

					searching = false; 

				}else{

					if(currentPos->parent){

						if(currentPos->data < currentPos->parent->data){

							currentPos = currentPos->parent;
							searching = false;
						
						}else{

							do{

								if(currentPos->parent) { 

									if(currentPos->data < currentPos->parent->data){

										currentPos = currentPos->parent;
										searching = false;
										break;
									
									}else{

										currentPos = currentPos->parent;
										continue;
									}

								}else{

									searching = false;
									break;
								}

							}while(searching);
						}
					
					}else{

						searching = false;
					}
				}
			}

			if(current->data < currentPos->data) current = currentPos;

			else current = current->rightChild.get();

		return *this;
	}

//###########################################################//

// do not edit below this line

#endif
