#include "Lib.hpp"
#include <algorithm>
#include <iostream>

using namespace std;

Node::Node(int k):
    key(k),
    left(nullptr),
    right(nullptr),
    height(1)
{
}

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
    Node* y= x->right;
    Node* T2= y->left;

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
	if (bal > 1 && bFactor(current->right) <= 0)
		return leftRotate(current);
	
	//already balanced
	return current;
}

Node* Tree::insert(Node* current, int key)
{

//insert node
	//empty tree
    if (current == nullptr)
        return new Node(key);
	//left
    if (key < current->key)
        current->left = insert(current->left, key);
	//right
    else if (key > current->key)
        current->right = insert(current->left, key);
	//already in tree
    else
        return current;

    //update height as we step out of recursion
    current->height = 1
        + max(height(current->left),height(current->right));

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
}
void preOrder(Node* root){
	if (root != nullptr) {
		cout << root->key << ", ";
		inOrder(root->left);
		inOrder(root->right);
	}
	return;
}

void inOrder(Node* root)
{
	if (root != nullptr) {
		inOrder(root->left);
		cout << root->key << ", ";
		inOrder(root->right);
	}
	return;
}
