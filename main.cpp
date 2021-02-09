#include "BTreeNode.h"
using namespace std;

int main (){
    

    Tree mytree(3, 'z');
    //Tree mytree(3);
    mytree.insert(56,34,'G');

    
    mytree.insert(71,6,'M');
    mytree.insert(68,0,'P');
    mytree.insert(123,-666,'T');
    mytree.insert(999,4,'X');
    mytree.insert(41,33,'A');

    
    mytree.insert(-66,8,'B');
    mytree.insert(748,54,'C');
    mytree.insert(99,978,'D');
    mytree.insert(400,23,'E');
    mytree.insert(98,66,'J');
    mytree.insert(0,43,'K');


    mytree.insert(66,12,'N');
    mytree.insert(45,1,'O');
    mytree.insert(11,-34,'Q');
    mytree.insert(67,-36,'R');
    mytree.insert(40,7,'S');
    mytree.insert(85,3,'U');

    mytree.insert(8,2,'V');
    mytree.insert(62,9,'Y');
    mytree.insert(9,5,'Z');

    mytree.traverse();
    cout << endl << endl;
    cout << "**----------------------------**" << endl << endl;

    char removeData = 'G';
    Data removeObject(0,0,removeData,mytree.getOperationMode());
    mytree.remove(removeObject);

    mytree.traverse();
    
    return 0;
}