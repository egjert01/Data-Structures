/*
*
*  COMP 15 HW 2 Cheshire ConCATenation - Time to linked up in hur
*
*  testCharLinkedList.cpp
*  Testing File for your sequence CharLinkedList class
*
*  Written by: 
*        UTLN:
*          on:
*/

#include "CharLinkedList.h"
#include <iostream>

using namespace std;
void testEmptyList(CharLinkedList &list);
void testCharList(CharLinkedList &list);
void testArrayList(CharLinkedList &list);

void checkFirstLast(CharLinkedList &list);
void checkInsertion(CharLinkedList &list);
void checkRemoving(CharLinkedList &list);
void checkFind(CharLinkedList list);
void checkReplace(CharLinkedList &list);
void checkInsertInOrder(CharLinkedList &list);
void checkElementAt(CharLinkedList list);

int main(){
    //Create an array
    char howdy[5] = {'h','o','w','d','y'};
    char *arrayCopy = howdy;
    char partner[7] = {'p','a','r','t','n','e','r'};
    char *arrayCopy2 = partner;
    
    CharLinkedList emptyList;
    CharLinkedList arrayList(arrayCopy, 5);
    CharLinkedList arrayList2(arrayCopy2, 7);
    CharLinkedList charList('a');


    cout << endl << endl << "ARRAY LIST TESTS" << endl;
    testArrayList(arrayList);
    cout << endl << endl << "CHAR LIST TESTS" << endl;
    testCharList(charList);
    cout << endl << endl <<  "EMPTY LIST TESTS" << endl;
    testEmptyList(emptyList);
    
    CharLinkedList *arrayCopy3 = &arrayList2;
    arrayList.concatenate(arrayCopy3);
    arrayList.print();
        
    
}

/* Contains all the function calls pertaining to the Linked List that used the
 constructor initializing an array*/
void testArrayList(CharLinkedList &list){
    list.print();
    checkInsertion(list);
    checkFirstLast(list);
    checkElementAt(list);
    checkRemoving(list);
    //checkFind(list);
    checkReplace(list);
    checkInsertInOrder(list);

}
/* Contains all the function calls pertaining to the linked list that used
the constructor initializing a single char */
void testCharList(CharLinkedList &list){
    list.print();
    checkInsertion(list);
    checkFirstLast(list);
    checkRemoving(list);
    //checkFind(list);
    checkReplace(list);
}
/* Contains all the function calls pertaining to the linked list that used 
the default constructor */
void testEmptyList(CharLinkedList &list){
    list.print();
    checkInsertion(list);
    checkFirstLast(list);
    //checkFind(list);
}

void checkElementAt(CharLinkedList list){
    list.print();
    cout << "ELEMENT AT 0: " << list.elementAt(0) << endl;
    cout << "ELEMENT AT 2: " << list.elementAt(2) << endl;
    cout << "ELEMENT AT 4: " << list.elementAt(4) << endl;

}
void checkInsertInOrder(CharLinkedList &list){
    cout << "INSERTING IN ORDER" << endl;
    list.popFromFront();
    list.print();
    list.insertInOrder('j');
    list.print();
    list.insertInOrder('m');
    list.print();
    list.insertInOrder('z');
    list.print();
}
void checkReplace(CharLinkedList &list){
    cout << "REPLACING FUNCTION" << endl;   
    list.print();
    list.replaceAt('r', 0);
    list.print();
}
void checkFind(CharLinkedList list){
    if (list.find('h')){
        cout << "FOUND H" << endl;
    } else {
        cout << "H NOT FOUND" << endl;
    }
    if (list.find('q')){
        cout << "FOUND Q" << endl;
    } else {
        cout << "Q NOT FOUND" << endl;
    }
    
}
void checkFirstLast(CharLinkedList &list){
    cout << "FIRST: " << list.first() << endl;
    cout << "LAST: " << list.last() << endl;
}
void checkInsertion(CharLinkedList &list){
    list.pushAtBack('b');
    list.pushAtBack('c');
    list.print();
    list.pushAtFront('z');
    list.pushAtFront('t');
    list.print();
    list.insertAt('0', 0);
    list.print();
    list.insertAt('2', 2);
    list.print();
    
    //Testing clear function
    // list.clear();
    // list.pushAtFront('x');
    // list.print();
    
    //Tests for errors:
    // list.insertAt('4', 4);
    // list.print();

    
}
void checkRemoving(CharLinkedList &list){

    list.popFromFront();
    list.popFromBack();
    list.print();
    cout << "removing at 2" << endl;
    list.removeAt(2);
    cout << "removing at 0" << endl;
    list.removeAt(0);
    list.print();

}

