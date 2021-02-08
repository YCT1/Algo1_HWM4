
#include <iostream>
using namespace std;
class Node{

    private:
        char *keys; //The array of keys
        int degree; //Minumum degree
        bool leaf; // If this is true, this node is leaf and end point,
        Node **childs; // Array of pointer to this nodes children
        int size; // Size of keys 

    public:
        Node(); //Normal Constructor
        Node(int degree, bool isLeaf); //

        void insertNonFull(char k);
        void splitChild(int i, Node*y);

        void traverse();
        Node *search(char k);
friend class Tree;
};

Node::Node(int degree, bool isLeaf){

    //Getting nececary data 
    this->degree = degree;
    this->leaf = isLeaf;

    //Doing nececary memory allocation
    keys = new char[2*degree-1];
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

void Node::insertNonFull(char k){
    int i = size - 1;

    if(leaf == true){
        while(i>= 0 && keys[i]>k){
            keys[i+1] = keys[i];
            i--;
        }

        keys[i+1] = k;
        size = size + 1;
    }else{

        while(i>= 0 && keys[i] > k){
            i--;
        }

        if(childs[i+1]->size == 2*degree-1){
            splitChild(i+1,childs[i+1]);

            if(keys[i+1] < k){
                i++;
            }

        }
        childs[i+1]->insertNonFull(k);

    }
}

void Node::splitChild(int i, Node *y){
    Node *z = new Node(y->degree,y->leaf);
    z->size = degree - 1; 
    for(int j = 0; j < degree-1; j++){
        z->keys[j] = y->keys[j+degree];
    }

    if(y->leaf == false){
        for(int j = 0; j < degree;j++){
            z->childs[j] = y->childs[j+degree];
        }
    }

    y->size = degree - 1;


    for (int j = size; j >= i+1; j--){
        childs[j+1] = childs[j]; 
    }

    childs[i+1] = z;

    for (int j = size-1; j >= i; j--) {
        keys[j+1] = keys[j];
    }

    keys[i] = y->keys[degree-1]; 

    size = size + 1;

}

class Tree{
    private:
        Node *root; //root of node (pointer)
        int degree; //Minumum degree
    
    public:
        Tree(int degree);
        void traverse();
        Node* search(char k);
        void insert(char k);

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

void Tree::insert(char k){

    //check tree is empty or not
    if(root == NULL){

        //Inisilizate the tree
        root = new Node(degree, true);
        root->keys[0] = k;
        root->size = 1;
        
    }else{

        //check if the root is full, resize it
        if(root->size == 2*degree-1){

            Node *s = new Node(degree,false);

            s->childs[0] = root;

            s->splitChild(0,root);

            int i = 0;
            if(s->keys[0] < k){
                i++;
            }
            s->childs[i]->insertNonFull(k);

            root = s;
        }else{
            root->insertNonFull(k);
        }

    }
}