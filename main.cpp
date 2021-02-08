
//#include "BTreeNode.h"
#include "BTreeNode.h"
using namespace std;

int main (){
    

    Tree mytree(3);

    mytree.insert('D');
    mytree.insert('A');
    mytree.insert('B');
    mytree.insert('X');
    mytree.insert('G');
    mytree.insert('F');
    mytree.traverse();

    
    return 0;
}