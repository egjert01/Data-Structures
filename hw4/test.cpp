/*
 * test.cpp
 * COMP15
 * Spring 2020
 *
 * Test driver for the BinarySearchTree class
 */

#include <iostream>

#include "BinarySearchTree.h"

using namespace std;

void testDelete();
void testContains(BinarySearchTree bst);
void testAssignmentOperator(BinarySearchTree bst);
void testNodeCount(BinarySearchTree bst);
void testCountTotal();
void testMaxMin(BinarySearchTree bst);
void testRemoveSmall();
void testRemove(BinarySearchTree bst);

int main(){
    BinarySearchTree bst;
    int values[]  = {4, 2, 11, 15, 9, 1, -6, 5, 3, 15, 2, 5, 13, 14};
    int numValues = sizeof(values) / sizeof(int);
    
    for (int i = 0; i < numValues; i++) {
            bst.insert(values[i]);
    }

    bst.print_tree(); //testing print
    BinarySearchTree bst2 = bst; //testing Copy Constructor
    bst2.print_tree();
    cout << "COUNTING: " << bst.count_total() << endl;

    testAssignmentOperator(bst);
    testDelete();
    testContains(bst);  
    testNodeCount(bst);
    testCountTotal();
    testMaxMin(bst);
    testRemoveSmall();
    testRemove(bst);
    
}
/* 
* Purpose : tests my remove functions on a large scale (a big tree is passed in)
* Arguments : the big binary search tree created in main
* Returns : void
* Effects : removes the element i specify (for testing I often changed this 
* value. Here the node containing 4 will be removed - the root). Will also 
* print the tree before and after removal
*/
void testRemove(BinarySearchTree bst){
    cout << "big--BEFORE REMOVING: " << endl;
    bst.print_tree();
    cout << "big--AFTER REMOVING: " << endl;
    bst.remove(4);
    bst.print_tree();
    
}
/* 
* Purpose : tests my remove functions on a small scale. Create a new binary 
* search tree object, and insert objects one at a time for testing purposes to 
* make sure all of my functions are working as expected and when nodes are 
* removed that the binary search tree invariants are maintained
* Arguments : none
* Returns : void
* Effects : insert and remove the element i specify (for testing I often changed
* this value. Here the node containing 4 will be removed - the root). Will also 
* print the tree before and after removal
*/
void testRemoveSmall(){
    BinarySearchTree bst;
    bst.insert(25);
    bst.insert(15);
    bst.insert(30);
    bst.insert(26);
    bst.insert(27);
    cout << "small--BEFORE REMOVING: " << endl;
    bst.print_tree();
    bst.remove(25);
    cout << "small--AFTER REMOVING: " << endl;
    bst.print_tree();
}
/* 
* Purpose : test my find_min() and find_max() functions. Also test to make sure 
* they work if I pass in a subtree -> which requires private elements, and is 
* used in the remove functions.
* Arguments : the binary search tree created in main
* Returns : void
* Effects : prints out the minimum and maximum of the entire tree, as well as 
* the minimum on the right.
*/
void testMaxMin(BinarySearchTree bst){
    cout << "max: " << bst.find_max() << endl;
    cout << "min: " << bst.find_min() << endl;
    
    //cout << "min on right: " << bst.find_min(bst.root->right)->data << endl;
}
/* 
* Purpose : tests my count_total function
* Arguments : none
* Returns : void
* Effects : creates a new tree and inserts in three values and then prints out 
* the sum of all of the values in the tree.
*/
void testCountTotal(){
    BinarySearchTree testing;
    testing.insert(1);
    testing.insert(2);
    testing.insert(3);
    testing.print_tree();
    cout << "Sum: " << testing.count_total() << endl;
    
}
/* 
* Purpose : tests my contains funcrtion
* Arguments : the binary search tree created in main
* Returns : void
* Effects : prints a message telling the user if the given element was found in 
* the tree or not
*/
void testContains(BinarySearchTree bst){
    if (bst.contains(-6)){
        cout << "CONTIANS!" << endl;
    } else {
        cout << "doesn't contain :(" << endl;
    }
    
}
/* 
* Purpose : test the assignment operator 
* Arguments : the binary search tree created in main
* Returns : void
* Effects : create a new binary search tree and insert elements into it. Print 
* the tree I created, and then use the assignment operator to override all the 
* values in the tree i created with those of the binary search tree that i 
* passed to the function, and finally print out the tree i create in this 
* function to make sure it has all new values
*/
void testAssignmentOperator(BinarySearchTree bst){
    BinarySearchTree aoo;
    int values2[] = {-4, -6, -2, -5, -4, -7};
    int numValsToo = sizeof(values2) / sizeof(int);
    for (int i = 0; i < numValsToo; i++){
        aoo.insert(values2[i]);
    }
    cout << "AOO BEFORE" << endl;
    aoo.print_tree();
    aoo = bst;
    cout << "AOO AFTER" << endl;
    aoo.print_tree();
}
/* 
* Purpose : tests my post_order_delete function
* Arguments : none
* Returns : void
* Effects : creates a new object inserts an elements then deletes that element.
* prints messages to the terminal if the root is a nullptr and if the tree is 
* empty
* Notes: I was also having issues with this at first, so I was doing a lot of 
* tests within this function. Turned out to be the issue of resetting the 
* root = nullptr.
*/
void testDelete(){
    // BinarySearchTree test;
    // test.insert(1);
    // test.print_tree();
    // test.post_order_delete(test.root);
    // test.root = nullptr;
    // if (test.root == nullptr){
    //     cout << "it's a nullptr" << endl;
    // }
    // 
    // cout << test.tree_height() << endl;
    // //bst.post_order_delete(bst.root);
    // if (test.tree_height() == -1){
    //     cout << "empty tree" << endl;
    // } else {
    //     test.print_tree();
    // }
}
/* 
* Purpose : tests my node_count function
* Arguments : the binary search tree created in the main function
* Returns : void
* Effects : prints the number of nodes in the tree
*/
void testNodeCount(BinarySearchTree bst){
    (void)bst; //STUB: remove when running
    //cout << "NODE COUNT: " << bst.node_count(bst.root) << endl;
}





