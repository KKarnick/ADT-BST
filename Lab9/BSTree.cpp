
#include "BSTree.h"

template <typename DataType, class KeyType>
BSTree<DataType, KeyType>::BSTreeNode::BSTreeNode ( const DataType &nodeDataItem, BSTreeNode *leftPtr, BSTreeNode *rightPtr ){
	dataItem = nodeDataItem;
	left = leftPtr;
	right = rightPtr;
}

template < typename DataType, class KeyType >
BSTree<DataType, KeyType>::BSTree ()
{
	root = NULL;  //given
}

template < typename DataType, class KeyType >
BSTree<DataType, KeyType>::BSTree ( const BSTree<DataType,KeyType>& other ){
	*this = other;  //FIXME
}

template < typename DataType, class KeyType >
BSTree<DataType, KeyType>& BSTree<DataType, KeyType>:: operator= ( const BSTree<DataType,KeyType>& other ){
	if (this != &other) { //ensure not pointing to same object
		clear();
		copyHelper(root, other.root);
	}
	return *this;  //return other in either case
}

template < typename DataType, class KeyType >
BSTree<DataType, KeyType>::~BSTree (){
	clear();
}

template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::insert ( const DataType& newDataItem ){
	//call hidden function
	insertHelper(root, newDataItem);
}

template < typename DataType, class KeyType >
bool BSTree<DataType, KeyType>::retrieve ( const KeyType& searchKey, DataType& searchDataItem ) const{
	//call hidden function

	return retrieveHelper(root, searchKey, searchDataItem);
}

template < typename DataType, class KeyType >
bool BSTree<DataType, KeyType>::remove ( const KeyType& deleteKey ){
	  //call hidden function
	return removeHelper(deleteKey, root);
}

template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::writeKeys () const{
	writeKeysHelper(root);
}

template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::clear (){
	//call private function
	clearHelper(root);
	//declare tree as empty (root = null)
	root = 0;

}

template < typename DataType, class KeyType >
bool BSTree<DataType, KeyType>::isEmpty () const{
	if (root == 0)
		return true;
	else
		return false;
}

template < typename DataType, class KeyType >
int BSTree<DataType, KeyType>::getHeight () const{
	//call hidden function
	return heightHelper(root);
}

template < typename DataType, class KeyType >
int BSTree<DataType, KeyType>::getCount () const{
	//call hidden function
	return countHelper(root);

}

template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::writeLessThan ( const KeyType& searchKey ) const{
	//call hidden function
	return lessThanHelper(searchKey, root);
}


#include "show9.cpp"

template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::copyHelper(BSTreeNode*& r, BSTreeNode* o) {

	if (o != nullptr) {
		//copy values from each node and call helper on subtree
		r = new BSTreeNode(other->dataItem, other->left, other->right);
		copyHelper(r->left, o->left);
		copyHelper(r->right, o->right);
	}
}

template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::insertHelper(BSTreeNode*& r, const DataType& newDataItem) {
	if(r == 0)  //empty tree
		r = new BSTreeNode(newDataItem, 0, 0);
	        //traverse tree to empty location that's appropriate
	else {
		if (newDataItem.getKey() < (r->dataItem).getKey())
			insertHelper(r->left, newDataItem);
		else if (newDataItem.getKey() > (r->dataItem).getKey())
			insertHelper(r->right, newDataItem);
		else  //equal, so change current dataItem (no repeats in this lab)
			r->dataItem = newDataItem;
	}
}


template<typename DataType, class KeyType>
bool BSTree<DataType, KeyType>::retrieveHelper(BSTreeNode* r, const KeyType& searchKey, DataType& searchItem) const{
	    //check if null
	if (r != 0) { 
		if (searchKey == (r->dataItem).getKey()) {
			searchItem = r->dataItem;
			return true;  //item found
		}
		//traverse recursively to find location item would be
		else if (searchKey < (r->dataItem).getKey())
			return retrieveHelper(root->left, searchKey, searchItem);
		else
			return retrieveHelper(root->right, searchKey, searchItem);
	}
	else
	return false;
}


template<typename DataType, class KeyType>
bool BSTree<DataType, KeyType>::removeHelper(const KeyType& deleteKey, BSTreeNode* r){

	if (r == 0)
		return false;
	else {
		if (deleteKey < (r->dataItem).getKey())
			return removeHelper(deleteKey, r->left);
		else if(deleteKey > (r->dataItem).getKey() )
			return removeHelper(deleteKey, r->right);
		        //if found, determine children
		else {  //found
			BSTreeNode* nodeToRemove = r;
			if (r->left == 0) {
				r = r->right;
				delete nodeToRemove;
			}
			else if (r->right == 0) {
				r = r->left;
				delete nodeToRemove;
			}
			//case 3: 2 children
				 //move up left subtree greatest value
			else {
				BSTreeNode* nodeToMove = r->left;
				while (nodeToMove->right)
					//traverse to largest value in subtree
					nodeToMove = nodeToMove->right;
				r->dataItem = nodeToMove->dataItem;
				//call removeHelper to remove node whose value was used for r
				removeHelper((nodeToMove->dataItem).getKey(), r->left);

			}
			
		}
		return true;
	}
}

template<typename DataType, class KeyType>
void BSTree<DataType, KeyType>::clearHelper(BSTreeNode* r){
	//recursively traverse tree and delete nodes
	if (r != 0) {
		clearHelper(r->left);
		clearHelper(r->right);
		delete r;
	}
	//returns when left & right of leaves have been evaluated to be null

}

template<typename DataType, class KeyType>
void BSTree<DataType, KeyType>::writeKeysHelper(BSTreeNode* r) const{
	if (r == 0)  //empty tree or child of leaf  (base case)
		return;
	else {
		writeKeysHelper(r->left);
		cout << (r->dataItem).getKey() << "  ";
		writeKeysHelper(r->right);
	}
	cout << endl;
}

template<typename DataType, class KeyType>
int BSTree<DataType, KeyType>::heightHelper(BSTreeNode* r) const{
	          //height of leaf node is 0
	if (r == 0) 
		return -1;
		
	else {
		int maxLeft = 1 + heightHelper(r->left);
		int maxRight = 1 + heightHelper(r->right);
		if (maxRight > maxLeft)
			return maxRight;
		else
			return maxLeft;
	}
}

template<typename DataType, class KeyType>
int BSTree<DataType, KeyType>::countHelper(BSTreeNode* r) const{
	if (r == 0)  //if node is null, add 0 to count
		return 0;
	else
		return (1 + countHelper(r->left) + countHelper(r->right));  //add "self" to subtree counts


}

template<typename DataType, class KeyType>
void BSTree<DataType, KeyType>::lessThanHelper(const KeyType& searchKey, BSTreeNode* r) const{
	if (r != nullptr) {
		lessThanHelper(searchKey, r->left);
		if ((r->dataItem).getKey() < searchKey)
			cout << (r->dataItem).getKey() << "  ";
		lessThanHelper(searchKey, r->right);
	}

}



