
#include <iostream>
#include <string>
using namespace std;

class Data{

    private:
        char key;
        int x,y;
        char operationMode;
    
    public:
        Data();
        Data(const Data &p);
        void copy(Data &p);
        string get(){return "(" + to_string(x) + "," + to_string(y) + "," + key + ")";}
        void set(int x, int y, char keys, char operationMode);

        int getx(){return x;}
        int gety(){return y;}
        char getkey(){return key;}
        char geto(){return operationMode;}

        bool operator==(Data i);
        bool operator<=(Data i);
        bool operator>=(Data i);
        bool operator>(Data i);
        bool operator<(Data i);
};
Data::Data(){
    this->x = 0;
    this->y = 0;
    this->key = 'X';
    this->operationMode = 'z';
}
void Data::copy(Data &p){
    x = p.x;
    y = p.y;
    key = p.key;
    operationMode = p.operationMode;
}
Data::Data(const Data &p){
    x = p.x;
    y = p.y;
    key = p.key;
    operationMode = p.operationMode;
}

void Data::set(int x, int y, char key, char operationMode){
    this->x = x;
    this->y = y;
    this->key = key;
    this->operationMode = operationMode;
}


//Operator Overloding
bool Data::operator==(Data i){
    if(operationMode == 'x'){
        return x == i.x;
    }else if(operationMode == 'y'){
        return y == i.y;
    }else if(operationMode == 'z'){
        return key == i.key;
    }
    cout << "error"<< endl;
    return false;
}

bool Data::operator<=(Data i){
    if(operationMode == 'x'){
        return x <= i.x;
    }else if(operationMode == 'y'){
        return y <= i.y;
    }else if(operationMode == 'z'){
        return key <= i.key;
    }
    cout << "error"<< endl;
    return false;
}

bool Data::operator>=(Data i){
    if(operationMode == 'x'){
        return x >= i.x;
    }else if(operationMode == 'y'){
        return y >= i.y;
    }else if(operationMode == 'z'){
        return key >= i.key;
    }
    cout << "error"<< endl;
    return false;
}

bool Data::operator>(Data i){
    if(operationMode == 'x'){
        return x > i.x;
    }else if(operationMode == 'y'){
        return y > i.y;
    }else if(operationMode == 'z'){
        return key > i.key;
    }
    cout << "error"<< endl;
    return false;
}

bool Data::operator<(Data i){
    if(operationMode == 'x'){
        return x < i.x;
    }else if(operationMode == 'y'){
        return y < i.y;
    }else if(operationMode == 'z'){
        return key < i.key;
    }
    cout << "error"<< endl;
    return false;
}

class Node{

    private:
        char *keys; //The array of keys
        int *x;
        int *y;
        Data *data;

        int degree; //Minumum degree
        bool leaf; // If this is true, this node is leaf and end point,
        Node **childs; // Array of pointer to this nodes children
        int size; // Size of keys 
    public:
        Node(); //Normal Constructor
        Node(int degree, bool isLeaf); //

        void insertNonFull(int x,int y, char k);
        void insertNonFull(Data x);
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
    x = new int[2*degree-1];
    y = new int[2*degree-1];

    data = new Data[2*degree-1];

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
        cout << data[i].get();
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

//NEW
void Node::insertNonFull(Data k){
    int i = size - 1;

    if(leaf == true){
        while(i>= 0 && data[i]>k){
            data[i+1] = data[i];
            i--;
        }

        data[i+1] = k;
        size = size + 1;
    }else{

        while(i>= 0 && data[i] > k){
            i--;
        }

        if(childs[i+1]->size == 2*degree-1){
            splitChild(i+1,childs[i+1]);

            if(data[i+1] < k){
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
        z->data[j] = y->data[j+degree];
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
        data[j+1] = data[j];
    }


    data[i] = data[degree-1];
    size = size + 1;

}

class Tree{
    private:
        Node *root; //root of node (pointer)
        int degree; //Minumum degree
        char operationChar;
    
    public:
        Tree(int degree, char operation);
        void traverse();
        Node* search(char k);
        void insert(int x, int y, char k);

};


Tree::Tree(int degree, char operation){
    root = NULL; 
    this->degree = degree;
    operationChar = operation;
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

void Tree::insert(int _x, int _y, char k){

    //check tree is empty or not
    if(root == NULL){

        //Inisilizate the tree
        root = new Node(degree, true);
        root->keys[0] = k;
        root->x[0] = _x;
        root->y[0] = _y;
        root->data[0].set(_x,_y,k,operationChar);
        root->size = 1;
        
    }else{

        //check if the root is full, resize it
        if(root->size == 2*degree-1){

            Node *s = new Node(degree,false);

            s->childs[0] = root;

            s->splitChild(0,root);

            int i = 0;
            Data newData;
            newData.set(_x,_y,k,operationChar);
            if(s->data[0] < newData){
                i++;
            }
            newData.set(_x,_y,k,operationChar);
            s->childs[i]->insertNonFull(newData);

            root = s;
        }else{
            Data newData;
            newData.set(_x,_y,k,operationChar);
            root->insertNonFull(newData);
        }

    }
}