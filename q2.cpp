/*
Name: Yekta Can Tursun
Number: 150170105
*/
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

        //For deletion part, Allah yolumuzu açık etsin
        void remove(Data k);
        void removeFromLeaf(int idx);
        void removeFromNonLeaf(int idx);
        Data getPred(int idx); 
        Data getSucc(int idx); 
        void fill(int idx); 
        void borrowFromPrev(int idx); 
        void borrowFromNext(int idx); 
        void merge(int idx);
        int findData(Data k);

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

//Deletion functions for Node Class
int Node::findData(Data k){
 int idx=0; 
    while (idx<size && data[idx] < k){
        ++idx; 
    } 
    return idx;
    
}

void Node::remove(Data k){
    int idx = findData(k); 
    
        // The key to be removed is present in this node 
        if (idx < size && data[idx] == k) 
        { 
    
            // If the node is a leaf node - removeFromLeaf is called 
            // Otherwise, removeFromNonLeaf function is called 
            if (leaf) 
                removeFromLeaf(idx); 
            else
                removeFromNonLeaf(idx); 
        } 
        else
        { 
    
            // If this node is a leaf node, then the key is not present in tree 
            if (leaf) 
            { 
                cout << "The key "<< k.get() <<" is does not exist in the tree\n"; 
                return; 
            } 
    
            // The key to be removed is present in the sub-tree rooted with this node 
            // The flag indicates whether the key is present in the sub-tree rooted 
            // with the last child of this node 
            bool flag = ( (idx==size)? true : false ); 
    
            // If the child where the key is supposed to exist has less that t keys, 
            // we fill that child 
            if (childs[idx]->size < degree){ 
                fill(idx);
            } 
    
            // If the last child has been merged, it must have merged with the previous 
            // child and so we recurse on the (idx-1)th child. Else, we recurse on the 
            // (idx)th child which now has atleast t keys 
            if (flag && idx > size){
                childs[idx-1]->remove(k); 
            } 
            else{
                childs[idx]->remove(k);
            } 
        } 
    return; 
    
}
void Node::removeFromLeaf(int idx){
    // Move all the keys after the idx-th pos one place backward 
    for (int i=idx+1; i<size; ++i){ 
        data[i-1] = data[i];
    } 
    // Reduce the count of keys 
    size--; 
    return; 

}

void Node::removeFromNonLeaf(int idx){
     Data k = data[idx]; 
  
    // If the child that precedes k (C[idx]) has atleast t keys, 
    // find the predecessor 'pred' of k in the subtree rooted at 
    // C[idx]. Replace k by pred. Recursively delete pred 
    // in C[idx] 
    if (childs[idx]->size >= degree) 
    { 
        Data pred = getPred(idx); 
        data[idx] = pred; 
        childs[idx]->remove(pred); 
    } 
  
    // If the child C[idx] has less that t keys, examine C[idx+1]. 
    // If C[idx+1] has atleast t keys, find the successor 'succ' of k in 
    // the subtree rooted at C[idx+1] 
    // Replace k by succ 
    // Recursively delete succ in C[idx+1] 
    else if  (childs[idx+1]->size >= degree) 
    { 
        Data succ = getSucc(idx); 
        data[idx] = succ; 
        childs[idx+1]->remove(succ); 
    } 
  
    // If both C[idx] and C[idx+1] has less that t keys,merge k and all of C[idx+1] 
    // into C[idx] 
    // Now C[idx] contains 2t-1 keys 
    // Free C[idx+1] and recursively delete k from C[idx] 
    else
    { 
        merge(idx); 
        childs[idx]->remove(k); 
    } 
    return; 
}

Data Node::getPred(int idx){
    // Keep moving to the right most node until we reach a leaf 
    Node *cur=childs[idx]; 
    while (!cur->leaf){ 
        cur = cur->childs[cur->size];
    } 
  
    // Return the last key of the leaf 
    return cur->data[cur->size-1]; 
}
Data Node::getSucc(int idx){
  
    // Keep moving the left most node starting from C[idx+1] until we reach a leaf 
    Node *cur = childs[idx+1]; 
    while (!cur->leaf) 
        cur = cur->childs[0]; 
  
    // Return the first key of the leaf 
    return cur->data[0]; 

}
void Node::fill(int idx){
    // If the previous child(C[idx-1]) has more than t-1 keys, borrow a key 
    // from that child 
    if (idx!=0 && childs[idx-1]->size>=degree) 
        borrowFromPrev(idx); 
  
    // If the next child(C[idx+1]) has more than t-1 keys, borrow a key 
    // from that child 
    else if (idx!=size && childs[idx+1]->size>=degree) 
        borrowFromNext(idx); 
  
    // Merge C[idx] with its sibling 
    // If C[idx] is the last child, merge it with with its previous sibling 
    // Otherwise merge it with its next sibling 
    else
    { 
        if (idx != size) 
            merge(idx); 
        else
            merge(idx-1); 
    } 
    return; 
}

void Node::borrowFromPrev(int idx){
    Node *child=childs[idx]; 
    Node *sibling=childs[idx-1]; 
  
    // The last key from C[idx-1] goes up to the parent and key[idx-1] 
    // from parent is inserted as the first key in C[idx]. Thus, the  loses 
    // sibling one key and child gains one key 
  
    // Moving all key in C[idx] one step ahead 
    for (int i=child->size-1; i>=0; --i) 
        child->data[i+1] = child->data[i]; 
  
    // If C[idx] is not a leaf, move all its child pointers one step ahead 
    if (!child->leaf) 
    { 
        for(int i=child->size; i>=0; --i) 
            child->childs[i+1] = child->childs[i]; 
    } 
  
    // Setting child's first key equal to keys[idx-1] from the current node 
    child->data[0] = data[idx-1]; 
  
    // Moving sibling's last child as C[idx]'s first child 
    if(!child->leaf) 
        child->childs[0] = sibling->childs[sibling->size]; 
  
    // Moving the key from the sibling to the parent 
    // This reduces the number of keys in the sibling 
    data[idx-1] = sibling->data[sibling->size-1]; 
  
    child->size += 1; 
    sibling->size -= 1; 
  
    return; 
}
void Node::borrowFromNext(int idx){
    Node *child=childs[idx]; 
    Node *sibling=childs[idx+1]; 
  
    // keys[idx] is inserted as the last key in C[idx] 
    child->data[(child->size)] = data[idx]; 
  
    // Sibling's first child is inserted as the last child 
    // into C[idx] 
    if (!(child->leaf)) 
        child->childs[(child->size)+1] = sibling->childs[0]; 
  
    //The first key from sibling is inserted into keys[idx] 
    data[idx] = sibling->data[0]; 
  
    // Moving all keys in sibling one step behind 
    for (int i=1; i<sibling->size; ++i) 
        sibling->data[i-1] = sibling->data[i]; 
  
    // Moving the child pointers one step behind 
    if (!sibling->leaf) 
    { 
        for(int i=1; i<=sibling->size; ++i) 
            sibling->childs[i-1] = sibling->childs[i]; 
    } 
  
    // Increasing and decreasing the key count of C[idx] and C[idx+1] 
    // respectively 
    child->size += 1; 
    sibling->size -= 1; 
  
    return; 
}
void Node::merge(int idx){
    Node *child = childs[idx]; 
    Node *sibling = childs[idx+1]; 
  
    // Pulling a key from the current node and inserting it into (t-1)th 
    // position of C[idx] 
    child->data[degree-1] = data[idx]; 
  
    // Copying the keys from C[idx+1] to C[idx] at the end 
    for (int i=0; i<sibling->size; ++i) 
        child->data[i+degree] = sibling->data[i]; 
  
    // Copying the child pointers from C[idx+1] to C[idx] 
    if (!child->leaf) 
    { 
        for(int i=0; i<=sibling->size; ++i) 
            child->childs[i+degree] = sibling->childs[i]; 
    } 
  
    // Moving all keys after idx in the current node one step before - 
    // to fill the gap created by moving keys[idx] to C[idx] 
    for (int i=idx+1; i<size; ++i) 
        data[i-1] = data[i]; 
  
    // Moving the child pointers after (idx+1) in the current node one 
    // step before 
    for (int i=idx+2; i<=size; ++i) 
        childs[i-1] = childs[i]; 
  
    // Updating the key count of child and the current node 
    child->size += sibling->size+1; 
    size--; 
  
    // Freeing the memory occupied by sibling 
    delete(sibling); 
    return; 
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
        void remove(Data k);
        char getOperationMode(){return operationMode;}

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

//Tree class deletion function
void Tree::remove(Data k){
    if (!root) 
    { 
        cout << "The tree is empty\n"; 
        return; 
    } 
  
    // Call the remove function for root 
    root->remove(k); 
  
    // If the root node has 0 keys, make its first child as the new root 
    //  if it has a child, otherwise set root as NULL 
    if (root->size==0) 
    { 
        Node *tmp = root; 
        if (root->leaf) 
            root = NULL; 
        else
            root = root->childs[0]; 
  
        // Free the old root 
        delete tmp; 
    } 
    return; 
}
//Main function
int main (){
    //Gets first input
    int N;
    cin >> N;
    
    //Gets second input for order
    int order;
    cin >> order;

    //Gets third input for operation mode for comparision of data objects
    char type;
    cin >> type;

    //Creating tree with order and operation mode type
    Tree myTree(order,type);

    //Inserting data to tree
    for(int i = 0; i<N; i++){
        int x,y;
        char z;
        cin >> x >> y >> z;
        myTree.insert(x,y,z);
    }

    char userCharDeletionInput;
    int userIntDeletionInput;
    Data deletionData;
    if(type == 'z'){
        cin >> userCharDeletionInput;
        deletionData.set(0,0,userCharDeletionInput,myTree.getOperationMode());
        myTree.remove(deletionData);

    }else if(type == 'x'){
        cin >> userIntDeletionInput;
        deletionData.set(userIntDeletionInput,0,'?',myTree.getOperationMode());
        myTree.remove(deletionData);
        
    }else if(type == 'y'){
        cin >> userIntDeletionInput;
        deletionData.set(0,userIntDeletionInput,'?',myTree.getOperationMode());
        myTree.remove(deletionData);
        
    }
    //printig with desired strcutre of print
    myTree.traverse();
}