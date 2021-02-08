
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
//THIS IS THE ISSUE
void Node::insertNonFull(char k){
    // Initialize index as index of rightmost element 
	int i = size-1; 

	// If this is a leaf node 
	if (leaf == true) 
	{ 
		// The following loop does two things 
		// a) Finds the location of new key to be inserted 
		// b) Moves all greater keys to one place ahead 
		while (i >= 0 && keys[i] > k) 
		{ 
			keys[i+1] = keys[i]; 
			i--; 
		} 

		// Insert the new key at found location 
		keys[i+1] = k; 
		size = size+1; 
	} 
	else // If this node is not leaf 
	{ 
		// Find the child which is going to have the new key 
		while (i >= 0 && keys[i] > k) 
			i--; 

		// See if the found child is full 
		if (childs[i+1]->size == 2*degree-1) 
		{ 
			// If the child is full, then split it 
			splitChild(i+1, childs[i+1]); 

			// After split, the middle key of C[i] goes up and 
			// C[i] is splitted into two. See which of the two 
			// is going to have the new key 
			if (keys[i+1] < k) 
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
		z->keys[j] = y->keys[j+degree]; 

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
		keys[j+1] = keys[j]; 

	// Copy the middle key of y to this node 
	keys[i] = y->keys[degree-1]; 

	// Increment count of keys in this node 
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

//NOT THIS FUNCTION
void Tree::traverse(){
   if (root != NULL) root->traverse();
}

//NOT THIS FUNCTION
Node* Tree::search(char k){
    return (root == NULL)? NULL : root->search(k);
}

//NOT THIS FUNCTION
void Tree::insert(char k){

    // If tree is empty 
	if (root == NULL) 
	{ 
		// Allocate memory for root 
		root = new Node(degree, true); 
		root->keys[0] = k; // Insert key 
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
			if (s->keys[0] < k) 
				i++; 
			s->childs[i]->insertNonFull(k); 

			// Change root 
			root = s; 
		} 
		else // If root is not full, call insertNonFull for root 
			root->insertNonFull(k); 
	} 
}