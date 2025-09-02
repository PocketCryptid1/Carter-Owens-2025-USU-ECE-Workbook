//include gaurd
#ifndef _Lib_Header_
#define _Lib_Header_

class Node {
public:
    //fields
    int key;
    Node* left;
    Node* right;
    int height;

    //functions
    Node(int);
};

class Tree {
private:
    //fields
    Node* root;

    //functions
    int height(Node*);
    int bFactor(Node*);
    Node* rightRotate(Node*);
    Node* leftRotate(Node*);
    Node* balance(Node*);
    Node* insert(Node*, int);
    Node* minValueNode (Node*);
    Node* deleteNode(Node*, int);
    void preOrder(Node*);
    void inOrder(Node*);
    void postOrder(Node*);
    bool search(Node*, int);

public:
    Tree();
    void insert(int);
    void remove(int);
    bool search(int);
    void printInOrder();
};

#endif