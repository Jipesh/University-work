#ifndef TREE_H
#define TREE_H

#include "treenode.h"

template<typename T> class BinarySearchTree {

	private:

		unique_ptr<TreeNode<T>> root;	

		void rebalance(TreeNode<T>* node);

		void leftRotate(TreeNode<T>* node);

		void rightRotate(TreeNode<T>* node);

		const int & maxDepth(int & currentDepth,TreeNode<T>* node);

	public:

		BinarySearchTree();

		~BinarySearchTree();

		void write(ostream & o) const;

		TreeNode<T>* insert(const T & data);

		TreeNode<T>* find(const T & data);

		const TreeNodeIterator<T> begin();

		const TreeNodeIterator<T> end() const;

		const int maxDepth();

		const int maxDepth(TreeNode<T>* node);

		const int getBalanceFactor(TreeNode<T>* node);
};

// ##  funtions for BinarySearchTree<T> defined bellow  ##  //

	//  --  public functions  --  //

	template<typename T>
	BinarySearchTree<T>::BinarySearchTree():
	root(nullptr){}

	template<typename T>
	BinarySearchTree<T>::~BinarySearchTree(){}

	template<typename T>
	void BinarySearchTree<T>::write(ostream & o) const{ root->write(o); }

	template<typename T>
	TreeNode<T>* BinarySearchTree<T>::insert(const T & data){

		if(!root){

			root.reset(new TreeNode<T> (data));

			return root.get();

		}else{

			TreeNode<T>* currentNode;
			currentNode = root.get();
			bool searching = true;

			while(searching){

				if(data < currentNode->data){

					if((currentNode->leftChild)){
						
						currentNode = currentNode->leftChild.get();
						
						continue;

					}else{

						searching = false;
						currentNode->setLeftChild( new TreeNode<T> (data) );
						currentNode->leftChild->parent = currentNode;
						currentNode = currentNode->leftChild.get();

						break;
					}

				}else if (currentNode->data < data){

					if(currentNode->rightChild){
						
						currentNode = currentNode->rightChild.get();
						
						continue;
					
					}else{

						searching = false;
						currentNode->setRightChild( new TreeNode<T> (data) );
						currentNode->rightChild->parent = currentNode;
						currentNode = currentNode->rightChild.get();

						break;
					}

				}else { searching = false; }

				currentNode = nullptr;
			}

			logDLn("reached here , currentNode == nullptr : ",(currentNode == nullptr));

			if(currentNode) rebalance(currentNode);

			return currentNode;
		}
	}

	template <typename T>
	TreeNode<T>* BinarySearchTree<T>::find(const T & data){

		TreeNode<T>* currentNode;
		currentNode = root.get();
		bool searching = true;

		while(searching){

			if(data < currentNode->data){

				if((currentNode->leftChild)){
								
					currentNode = currentNode->leftChild.get();
					
					continue;
							
				}else{

					searching = false;
					currentNode = nullptr;
				}

			}else if(currentNode->data < data){

				if(currentNode->rightChild){
								
					currentNode = currentNode->rightChild.get();
					
					continue;
							
				}else{

					searching = false;
					currentNode = nullptr;
				}

			}else { searching = false; }		
		}

		return currentNode;
	}

	template<typename T>
	const TreeNodeIterator<T> BinarySearchTree<T>::begin(){

		if(!root) return TreeNodeIterator<T> (nullptr);

		TreeNode<T>* currentNode = root.get();
		bool searching = true;

		while(searching){

			if(currentNode->leftChild){

				currentNode = currentNode->leftChild.get();

				continue;

			}else { searching = false; }
		}

		return TreeNodeIterator<T> (currentNode);
	}

	template<typename T>
	const TreeNodeIterator<T> BinarySearchTree<T>::end() const{

		return TreeNodeIterator<T> (nullptr);
	}


	template<typename T>
	const int BinarySearchTree<T>::maxDepth(){ return maxDepth(root.get()); }

	template<typename T>
	const int BinarySearchTree<T>::maxDepth(TreeNode<T>* node){

		if(!node) return 0;

		if( !(node->leftChild) && !(node->rightChild) ) return 1;

		int max_left = 0;

		if( node->leftChild ) max_left = 1 + maxDepth(max_left, node->leftChild.get() );

		int max_right = 0;

		if( node->rightChild ) max_right = 1 + maxDepth(max_right, node->rightChild.get() );

		if( max_left >= max_right ) return max_left;

		return max_right;
	}



	template<typename T>
	const int BinarySearchTree<T>::getBalanceFactor(TreeNode<T>* node){
		
		int left, right;

		if(node->leftChild) left = maxDepth(node->leftChild.get());

		else left = 0;

		if (node->rightChild) right = maxDepth(node->rightChild.get());

		else right = 0; 

		return left - right;
	}

	//  -- private functions  --  //

	template<typename T>
	void BinarySearchTree<T>::rebalance(TreeNode<T>* node){

		int balanceFactor = 0;
		int count = 0;
		TreeNode<T>* currentNode = node;

		do{

			TreeNode<T>* _parent;

			if(currentNode->parent){

				_parent = currentNode->parent;
				balanceFactor = getBalanceFactor(_parent);

				if(balanceFactor == -2 ){

					if(_parent->rightChild->leftChild) rightRotate(currentNode);

					leftRotate(_parent);

					return;
				
				}else if(balanceFactor == 2){


					if(_parent->leftChild->rightChild) leftRotate(currentNode);

					rightRotate(_parent);

					return;

				}else { currentNode = currentNode->parent; }

				++count;

			}else{

				return;
			}

		}while(count < 2);
	}

	template<typename T>
	void BinarySearchTree<T>::leftRotate(TreeNode<T>* node){

		
		TreeNode<T>* currentNode = node;
		TreeNode<T>* toSwap = node->rightChild.release();
		TreeNode<T>* temp = toSwap->leftChild.release();

		if(node == root.get()){

			currentNode = new TreeNode<T>(node->data);
			currentNode->rightChild.reset( node->rightChild.get() );
			currentNode->parent = toSwap;
			root.reset( toSwap );
			toSwap->parent = nullptr;

		}else{

			toSwap->parent = currentNode->parent;

			if(currentNode->parent->leftChild.get() == node){

				currentNode = currentNode->parent->leftChild.release();
				node->parent->leftChild.reset( toSwap );
			}

			else if(currentNode->parent->rightChild.get() == node){

				currentNode = currentNode->parent->rightChild.release();
				node->parent->rightChild.reset( toSwap );
			}

		}

		currentNode->parent = toSwap;
		toSwap->leftChild.reset( currentNode );
		currentNode->rightChild.reset(temp);
	}

	template<typename T>
	void BinarySearchTree<T>::rightRotate(TreeNode<T>* node){

		TreeNode<T>* currentNode = node;
		TreeNode<T>* toSwap = node->leftChild.release();
		TreeNode<T>* temp = toSwap->rightChild.release();

		if(node == root.get()){

			currentNode = new TreeNode<T>(node->data);
			currentNode->leftChild.reset( node->leftChild.get() );
			currentNode->parent = toSwap;
			root.reset( toSwap );
			toSwap->parent = nullptr;

		}else{

			toSwap->parent = currentNode->parent;

			if(currentNode->parent->leftChild.get() == node){

				currentNode = currentNode->parent->leftChild.release();
				node->parent->leftChild.reset( toSwap );
			}

			else if(currentNode->parent->rightChild.get() == node){

				currentNode = currentNode->parent->rightChild.release();
				node->parent->rightChild.reset( toSwap );
			}

		}

		currentNode->parent = toSwap;
		toSwap->rightChild.reset( currentNode );
		currentNode->leftChild.reset(temp);
	}

	template<typename T>
	const int & BinarySearchTree<T>::maxDepth(int & currentDepth,TreeNode<T>* node){

		if( !(node->leftChild) && !(node->rightChild) ){

			++currentDepth;
			return currentDepth;
		}

		currentDepth = maxDepth(node);

		return currentDepth;
	}

//#############################################################//

// do not edit below this line

#endif
