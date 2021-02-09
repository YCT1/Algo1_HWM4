
#include <iostream>
#include <string>
using namespace std;

//Data class is created in order to store necacary data in the store
//Data objects can be used with comparasion operators, its usage can be change with operationMode
class Data{

    private:
        char key;//Z, char data
        int x,y;//X and Y int data
        char operationMode; //Operation Mode
    
    public:
        Data(); //General Constructor
        Data(int x, int y, char keys, char operationMode); //Set mode
        Data(const Data &p);//Copy constructor
        void copy(Data &p);//Copy function
        string get(){return "(" + to_string(x) + "," + to_string(y) + "," + key + ")";}//Returns string of data
        void set(int x, int y, char keys, char operationMode); //Sets value of data
        
        int getx(){return x;}//Get X data
        int gety(){return y;}//Get Y data
        char getkey(){return key;}//Get key
        char geto(){return operationMode;}//Get Operation Mode

        //This is the where comparision operators are created
        bool operator==(Data i);
        bool operator<=(Data i);
        bool operator>=(Data i);
        bool operator>(Data i);
        bool operator<(Data i);
};
Data::Data(){
    this->x = 0;
    this->y = 0;
    this->key = '?';
    this->operationMode = 'z';
}
Data::Data(int x, int y, char key, char operationMode){
    this->x = x;
    this->y = y;
    this->key = key;
    this->operationMode = operationMode;
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
//The behavour of the comparision will be changed according to operation Mode
bool Data::operator==(Data i){
    if(operationMode == 'x'){
        return x == i.x;
    }else if(operationMode == 'y'){
        return y == i.y;
    }else if(operationMode == 'z'){
        return key == i.key;
    }
    //If there is another operation mode that have not been writien print error
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
    //If there is another operation mode that have not been writien print error
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
    //If there is another operation mode that have not been writien print error
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
    //If there is another operation mode that have not been writien print error
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
    //If there is another operation mode that have not been writien print error
    cout << "error"<< endl;
    return false;
}



class Node{

    private:
        Data *data; //The array of data
        int degree; //Minumum degree
        bool leaf; // If this is true, this node is leaf and end point,
        Node **childs; // Array of pointer to this nodes children
        int size; // Size of keys 

    public:
        Node(); //Normal Constructor
        Node(int degree, bool isLeaf); //With degree and isLeaf constructor

        void insertNonFull(Data k); //Insert Non Full Function
        void splitChild(int i, Node*y); //Split child funciton

        void traverse(); //Traverse function with pre-fix printing
        Node *search(Data k); //Returns the adress of node with desired data in it
friend class Tree;
};

Node::Node(int degree, bool isLeaf){

    //Getting nececary data 
    this->degree = degree;
    this->leaf = isLeaf;

    //Doing nececary memory allocation
    data = new Data[2*degree-1];
    childs = new Node* [2*degree];

    //Number of data at this point
    size = 0;

}

void Node::traverse(){
    //Prints current node data
    for(int i = 0; i < size; i++){
        cout << data[i].get();
        
    }
    //If this leaf has children, recursively call children nodes
    if(leaf == false){
        for(int i = 0; i<size+1;i++){
            cout << endl;
            childs[i]->traverse();
        }
    }

}

Node* Node::search(Data k){
    int  i = 0;
    while (i < degree && k > data[i]){
        i++;
    }

    if(data[i] == k){
        return this;
    }
    //If there is nothing left, end of the tree, return NULL
    if(leaf == true){
        return NULL;
    }
    //Continue with recursively search
    return childs[i]->search(k);

}

void Node::insertNonFull(Data k){
    // Initialize index as rightmost element 
	int i = size-1; 

	// If this is a leaf node 
	if (leaf == true) 
	{ 

		while (i >= 0 && data[i] > k) 
		{ 
			data[i+1] = data[i]; 
			i--; 
		} 

		data[i+1] = k; 
		size = size+1; 
	} 
	else
	{ 

		while (i >= 0 && data[i] > k){ 
			i--;
        } 

		if (childs[i+1]->size == 2*degree-1) 
		{ 

			splitChild(i+1, childs[i+1]); 
			if (data[i+1] < k){ 
				i++; 
            }
		} 
		childs[i+1]->insertNonFull(k); 
	} 
}


void Node::splitChild(int i, Node *y){

    //Creating temporary node
	Node *z = new Node(y->degree, y->leaf); 
	z->size = degree - 1; 

    //Copying data
	for (int j = 0; j < degree-1; j++){ 
		z->data[j] = y->data[j+degree];
    } 

	if (y->leaf == false) 
	{ 
		for (int j = 0; j < degree; j++){ 
			z->childs[j] = y->childs[j+degree];
        } 
	} 

	y->size = degree - 1; 

	for (int j = size; j >= i+1; j--){ 
		childs[j+1] = childs[j];
    } 

	childs[i+1] = z; 

	for (int j = size-1; j >= i; j--){ 
		data[j+1] = data[j];
    } 

	data[i] = y->data[degree-1]; 
	size++; 

}

class Tree{
    private:
        Node *root; //root of node (pointer)
        int degree; //Minumum degree
		char operationMode; //Operation mode (x for X data, y for Y data, Z for char data)
    
    public:
        Tree(int degree); //Creating tree with data defult operation mode is x
		Tree(int degree, char operation); //Creating tree with degree and its operation mode
        void traverse(); //Tree traverse function
        Node* search(Data k); //Search function
        void insert(int x, int y, char k); //Insert function

};


Tree::Tree(int degree){
    root = NULL; 
    this->degree = degree;
}
Tree::Tree(int degree, char operation){
    root = NULL; 
    this->degree = degree;
	operationMode = operation;
}

void Tree::traverse(){
   if (root != NULL) {
       root->traverse();
    }
}


Node* Tree::search(Data k){
    return (root == NULL)? NULL : root->search(k);
}


void Tree::insert(int x, int y, char k){
    //Creating tempory data object with desired inputs
	Data newData(x, y, k, operationMode);
	
    // If tree is empty 
	if (root == NULL) 
	{ 
		// Creating new data and inilization for root 
		root = new Node(degree, true); 
		root->data[0] = newData; // Insert data object to root node
		root->size = 1; // Update number of data in root node 
	} 
	else
	{ 
		
		if (root->size == 2*degree-1) 
		{ 
			//Inilization of memory for new root 
			Node *s = new Node(degree, false); 
			s->childs[0] = root; 
			s->splitChild(0, root); 
			int i = 0; 
			if (s->data[0] < newData){ 
				i++;
            } 
			s->childs[i]->insertNonFull(newData); 

			//Root change
			root = s; 
		} 
		else{ // call insertNonFull for root 
			root->insertNonFull(newData);
        } 
	} 
}