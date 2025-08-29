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

Node* Tree::rightRotate(Node* parent)
{
    Node* oldleft= parent->left;
    Node* oldright= parent->right;

    //rotate
    oldleft->right = parent;
    parent->left = oldright;
    
    //update heights
    parent->height
        = max(height(parent->left),height(parent->right)) + 1;
    oldleft->height
        = max(height(oldleft->left),height(oldleft->right)) + 1;

    return oldleft;
}
