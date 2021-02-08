
#include <iostream>
using namespace std;
class Node{

    private:
        int *keys; //The array of keys
        int degree; //Minumum degree
        bool leaf; // If this is true, this node is leaf and end point,
        Node **childs; // Array of pointer to this nodes children
        int size; // Size of keys 

    public:
        Node(); //Normal Constructor
        Node(int degree, bool isLeaf); //
        void traverse();

        Node *search(char k);
friend class Tree;
};

Node::Node(int degree, bool isLeaf){

    //Getting nececary data 
    this->degree = degree;
    this->leaf = isLeaf;

    //Doing nececary memory allocation
    keys = new int[2*degree-1];
    childs = new Node* [2*degree];

    //Number of keys at this point
    size = 0;

}

void Node::traverse(){
    int i = 0;
    for(i = 0; i < size; i++){
        if(leaf == false){
            childs[i]->traverse();
        }
        cout << " " << keys[i];
    }

    if(leaf == false){
        childs[i]->traverse();
    }

}

Node* Node::search(char k){
    int  i = 0;
    while (i < degree && k > keys[i]){
        i++;
    }

    if(keys[i] == k){
        return this;
    }

    if(leaf == true){
        return NULL;
    }

    return childs[i]->search(k);

}

class Tree{
    private:
        Node *root; //root of node (pointer)
        int degree; //Minumum degree
    
    public:
        Tree(int degree);
        void traverse();
        Node* search(char k);

};


Tree::Tree(int degree){
    root = NULL; 
    this->degree = degree;
}

void Tree::traverse(){
    if(root != NULL){
        root->traverse();
    }
}

Node* Tree::search(char k){
    if(root == NULL){
        return NULL;
    }else{
        root->search(k);
    }
    return NULL;
}