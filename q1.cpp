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
        Data(int x, int y, char keys, char operationMode);
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
        Data *data; //The array of keys
        int degree; //Minumum degree
        bool leaf; // If this is true, this node is leaf and end point,
        Node **childs; // Array of pointer to this nodes children
        int size; // Size of keys 

    public:
        Node(); //Normal Constructor
        Node(int degree, bool isLeaf); //

        void insertNonFull(Data k);
        void splitChild(int i, Node*y);

        void traverse();
        Node *search(Data k);
friend class Tree;
};

Node::Node(int degree, bool isLeaf){

    //Getting nececary data 
    this->degree = degree;
    this->leaf = isLeaf;

    //Doing nececary memory allocation
    data = new Data[2*degree-1];
    childs = new Node* [2*degree];

    //Number of keys at this point
    size = 0;

}

void Node::traverse(){

    for(int i = 0; i < size; i++){
        cout << data[i].get();
        
    }
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

    if(leaf == true){
        return NULL;
    }

    return childs[i]->search(k);

}
//THIS IS THE ISSUE
void Node::insertNonFull(Data k){
    // Initialize index as index of rightmost element 
	int i = size-1; 

	// If this is a leaf node 
	if (leaf == true) 
	{ 
		// The following loop does two things 
		// a) Finds the location of new key to be inserted 
		// b) Moves all greater keys to one place ahead 
		while (i >= 0 && data[i] > k) 
		{ 
			data[i+1] = data[i]; 
			i--; 
		} 

		// Insert the new key at found location 
		data[i+1] = k; 
		size = size+1; 
	} 
	else // If this node is not leaf 
	{ 
		// Find the child which is going to have the new key 
		while (i >= 0 && data[i] > k) 
			i--; 

		// See if the found child is full 
		if (childs[i+1]->size == 2*degree-1) 
		{ 
			// If the child is full, then split it 
			splitChild(i+1, childs[i+1]); 

			// After split, the middle key of C[i] goes up and 
			// C[i] is splitted into two. See which of the two 
			// is going to have the new key 
			if (data[i+1] < k) 
				i++; 
		} 
		childs[i+1]->insertNonFull(k); 
	} 
}

//NOT THIS FUNCTION
void Node::splitChild(int i, Node *y){
    // Create a new node which is going to store (t-1) keys 
	// of y 
	Node *z = new Node(y->degree, y->leaf); 
	z->size = degree - 1; 

	// Copy the last (t-1) keys of y to z 
	for (int j = 0; j < degree-1; j++) 
		z->data[j] = y->data[j+degree]; 

	// Copy the last t children of y to z 
	if (y->leaf == false) 
	{ 
		for (int j = 0; j < degree; j++) 
			z->childs[j] = y->childs[j+degree]; 
	} 

	// Reduce the number of keys in y 
	y->size = degree - 1; 

	// Since this node is going to have a new child, 
	// create space of new child 
	for (int j = size; j >= i+1; j--) 
		childs[j+1] = childs[j]; 

	// Link the new child to this node 
	childs[i+1] = z; 

	// A key of y will move to this node. Find the location of 
	// new key and move all greater keys one space ahead 
	for (int j = size-1; j >= i; j--) 
		data[j+1] = data[j]; 

	// Copy the middle key of y to this node 
	data[i] = y->data[degree-1]; 

	// Increment count of keys in this node 
	size = size + 1; 

}

class Tree{
    private:
        Node *root; //root of node (pointer)
        int degree; //Minumum degree
		char operationMode;
    
    public:
        Tree(int degree);
		Tree(int degree, char operation);
        void traverse();
        Node* search(Data k);
        void insert(int x, int y, char k);

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
   if (root != NULL) root->traverse();
}


Node* Tree::search(Data k){
    return (root == NULL)? NULL : root->search(k);
}


void Tree::insert(int x, int y, char k){
	Data newData(x, y, k, operationMode);
	// If tree is empty 
	if (root == NULL) 
	{ 
		// Allocate memory for root 
		root = new Node(degree, true); 
		root->data[0] = newData; // Insert key 
		root->size = 1; // Update number of keys in root 
	} 
	else // If tree is not empty 
	{ 
		// If root is full, then tree grows in height 
		if (root->size == 2*degree-1) 
		{ 
			// Allocate memory for new root 
			Node *s = new Node(degree, false); 

			// Make old root as child of new root 
			s->childs[0] = root; 

			// Split the old root and move 1 key to the new root 
			s->splitChild(0, root); 

			// New root has two children now. Decide which of the 
			// two children is going to have new key 
			int i = 0; 
			if (s->data[0] < newData) 
				i++; 
			s->childs[i]->insertNonFull(newData); 

			// Change root 
			root = s; 
		} 
		else // If root is not full, call insertNonFull for root 
			root->insertNonFull(newData); 
	} 
}
int main (){
    int N;
    cin >> N;
    
    int order;
    cin >> order;

    char type;
    cin >> type;

    Tree myTree(order,type);

    for(int i = 0; i<N; i++){
        int x,y;
        char z;
        cin >> x >> y >> z;
        myTree.insert(x,y,z);
    }
    
    myTree.traverse();
}