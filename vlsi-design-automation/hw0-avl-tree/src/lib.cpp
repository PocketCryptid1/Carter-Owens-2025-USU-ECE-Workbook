#include "lib.h"
#include <algorithm>
#include <iostream>

using namespace std;

Node::Node(int k):
    key(k),
    left(nullptr),
    right(nullptr),
    height(1)
{}

int Tree::height(Node* node)
{
    if (node == nullptr)
        return 0;
    return node->height;
}

int Tree::bFactor(Node* node)
{
    if (node == nullptr)
        return 0;
    return height(node->left) - height(node->right);
}

Node* Tree::rightRotate(Node* y)
{
    Node* x= y->left;
    Node* T2= x->right;

    //rotate
    x->right = y;
    y->left = T2;
    
    //update heights
    y->height
        = max(height(y->left),height(y->right)) + 1;
    x->height
        = max(height(x->left),height(x->right)) + 1;

    return x;
}

Node* Tree::leftRotate(Node* x)
{
    Node* y = x->right;
    Node* T2 = y->left;

    //rotate
    y->left = x;
    x->right = T2;
    
    //update heights
    x->height
        = max(height(x->left),height(x->right)) + 1;
    y->height
        = max(height(y->left),height(y->right)) + 1;

    return y;
}

Node* Tree::balance(Node* current)
{
	//update heights
	current->height = 1
   		+ max(height(current->left),height(current->right));

	//check balance factor
    int bal = bFactor(current);

    //four out-of-balance cases:

    //left left
    if (bal > 1 && bFactor(current->left) >= 0 )
		return rightRotate(current);
    
    //left right
	if (bal > 1 && bFactor(current->left) < 0){
		current->left = leftRotate(current->left);
		return rightRotate(current);
	}
	
	//right left
	if (bal < -1 && bFactor(current->right) > 0) {
		current->right = rightRotate(current->right);
		return leftRotate(current);
	}

	//right right
	if (bal < -1 && bFactor(current->right) <= 0)
		return leftRotate(current);
	
	//already balanced
	return current;
}

Node* Tree::insert(Node* current, int key)
{

//insert node
	//open space
    if (current == nullptr)
        return new Node(key);
	//left
    if (key < current->key)
        current->left = insert(current->left, key);
	//right
    else if (key > current->key)
        current->right = insert(current->right, key);
	//already in tree
    else
        return balance(current);
	//balance
	return balance(current);
}

Node* Tree::minValueNode(Node* prev)
{
	Node* current = prev;
	while (current->left != nullptr)
		current = current->left;
	return current;
}

Node* Tree::deleteNode(Node* current, int key)
{
	//empty tree
	if (current == nullptr)
		return current;

	//find target node
	if (key < current->key)
		current->left = deleteNode(current->left, key);
	else if (key > current->key)
		current->right = deleteNode(current->right, key);
	//found node
	else {
		//one or no children
		if ((current->left == nullptr) || (current->right == nullptr)){
			//if child exists, copy it
			Node* temp = 
				current->left ? current->left : current->right;
			//if no child exists, move current to temp tp be deleted
			if (temp == nullptr){
				temp = current;
				current = nullptr;
			}
			//if child exists, replace current with temp
			else
				*current = *temp;
			delete temp;
		}
		//two children
		else{
			//find leftmost node on right subtree
			Node* temp = minValueNode(current->right);
			//bring temp up and remove original temp node
			current->key = temp->key;
			current->right = deleteNode(current->right, temp->key);
		}

		if (current == nullptr)
			return current;

		//update height as we exit recursion
		current -> height = 1
			+ max(height(current->left),height(current->right));
			
		return balance(current);
	}
	//should be unreachable 
	//but added to make the compiler happy
	return (nullptr);
}

void Tree::preOrder(Node* current){
	if (current != nullptr) {
		cout << current->key << ", ";
		preOrder(current->left);
		preOrder(current->right);
	}
	return;
}

void Tree::inOrder(Node* current)
{
	if (current != nullptr) {
		inOrder(current->left);
		cout << current->key << ", ";
		inOrder(current->right);
	}
	return;
}

void Tree::postOrder(Node* current){
	if (current != nullptr) {
		postOrder(current->left);
		postOrder(current->right);
		cout << current->key << ", ";
	}
	return;
}

bool Tree::search(Node* current, int key){
	if (current == nullptr)
        return false;
    if (current->key == key)
        return true;
    if (key < current->key)
        return search(current->left, key);
    return search(current->right, key);
}
/*=====PUBLIC FUNCTIONS=====*/

Tree::Tree():
	root(nullptr)
{}

void Tree::insert(int key){
	root = insert(root, key);
	return;
}

void Tree::remove(int key){
	root = deleteNode(root, key);
	return;
}

bool Tree::search(int key){
	return search(root, key);
}

void Tree::printPreOrder(){
	preOrder(root);
	cout << endl;
	return;
}

void Tree::printInOrder(){
	inOrder(root);
	cout << endl;
	return;
}

void Tree::printPostOrder(){
	postOrder(root);
	cout << endl;
	return;
}