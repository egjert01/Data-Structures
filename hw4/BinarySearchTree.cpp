/*
 * BinarySearchTree.cpp
 * COMP15
 * Spring 2020
 *
 * Implementation of the Binary Search Tree class.
 * Behaves like a standard BST except that it handles multiplicity
 * If you insert a number twice  and then remove it once, then it will
 * still be in the data structure
 */

#include <cstring>
#include <iostream>
#include <limits>

#include "BinarySearchTree.h"

using namespace std;

/*
* Purpose : Default constructor, sets the root to a nullptr
* Arguments : None 
* Returns : None 
* Effects : None
*/
BinarySearchTree::BinarySearchTree(){
        root = nullptr;        
        
}

BinarySearchTree::~BinarySearchTree(){
        // walk tree in post-order traversal and delete
        post_order_delete(root);
        root = nullptr;  // not really necessary, since the tree is going
                         // away, but might want to guard against someone
                         // using a pointer after deleting
}

/*
* Purpose : Delete the Binary Search Tree below the given node
* Arguments : A pointer to the starting node, below which everything will 
* be deleted
* Returns : None 
* Effects : Frees the memory that was allocated for the Binary Search Tree
*/
void BinarySearchTree::post_order_delete(Node *node) {
    if (node == nullptr){
        return;
    }
    post_order_delete(node->left);
    post_order_delete(node->right);
    delete(node);
    node = nullptr;
}

/*
* Purpose : Copy constructor
* Arguments : The object that the function is copying, passed by reference
* Returns : None 
* Effects : creates a new object that is the same as the object that was passed
*/
BinarySearchTree::BinarySearchTree(const BinarySearchTree &source) {
        // use pre-order traversal to copy the tree
        root = pre_order_copy(source.root);
}

/*
* Purpose : Assignment overload
* Arguments : The object that the function is copying, passed by reference
* Returns : the object that the function was called from 
* Effects : Frees the memory that was allocated for the current object, then 
copies all the values from the object passed in to the current object
*/
BinarySearchTree &BinarySearchTree::operator=(const BinarySearchTree &source){
        // check for self-assignment
        if (this == &source){
            return *this;
        }
        
        // delete current tree if it exists
        post_order_delete(root);

        // use pre-order traversal to copy the tree
        root = pre_order_copy(source.root);


        // don't forget to "return *this"
        return *this;
}

/*
* Purpose : Copies the entire tree under a given node
* Arguments : a node, under which everything will be copied to another tree 
* Returns : A pointer to the root of a new tree with the same values as the 
* on pointed to 
* Effects : None
*/
BinarySearchTree::Node *BinarySearchTree::pre_order_copy(Node *node) const {
        if (node == nullptr){
            return node;
        }
        
        return makeNode(node->data, node->count, pre_order_copy(node->right), 
                        pre_order_copy(node->left));
                                
}
/*  PUBLIC FUNCTION
* Purpose : Returns the minimum of the binary search tree
* Arguments : None
* Returns : An integer representing the smallest number in the tree
* Effects : Calls the private find_min() function
*/
int BinarySearchTree::find_min() const {
        if (root == nullptr)
                return numeric_limits<int>::max(); // INT_MAX

        return find_min(root)->data;
}
/*
* Purpose : return a node pointer to the node in the tree with the smallest 
* value.
* Arguments : A pointer to a node where the search will start
* Returns : A pointer to the node in the tree with the smallest value.
* Effects : None
*/
BinarySearchTree::Node *BinarySearchTree::find_min(Node *node) const {
    if(node->left == nullptr){
        return node;
    }
    return find_min(node->left);
}
/* PUBLIC FUNCTION
* Purpose : Returns the maximum of the binary search tree
* Arguments : None
* Returns : An integer representing the largest number in the tree
* Effects : Calls the private find_max() function
*/
int BinarySearchTree::find_max() const {
    if (root == nullptr){
        return numeric_limits<int>::min(); // INT_MIN
    }
    return find_max(root)->data;
}
/*
* Purpose : return a node pointer to the node in the tree with the largest 
* value.
* Arguments : A pointer to a node where the search will start
* Returns : A pointer to the node in the tree with the largest value.
* Effects : None
*/
BinarySearchTree::Node *BinarySearchTree::find_max(Node *node) const {
        if(node->right == nullptr){
            return node;
        }
        return find_max(node->right);
}
/* PUBLIC FUNCTION
* Purpose : traverses the tree and returns true if the given value is found 
* and false if it is not found
* Arguments : the value that the client wants to check if it's in the tree
* Returns : a boolean, true if it is in the tree, false if it is not
* Effects : Calls the private contains() function
*/
bool BinarySearchTree::contains(int value) const {
        if (contains(root, value)){
            return true;
        } else {
            return false;
        }
}
/*  
* Purpose : traverses the tree and returns true if the given value is found 
* and false if it is not found
* Arguments : the value that the client wants to check if it's in the tree
* Returns : a boolean, true if it is in the tree, false if it is not
* Effects : none
*/
bool BinarySearchTree::contains(Node *node, int value) const {
        if (node == nullptr){
            return false;
        }
        if (node->data == value){
            return true;
        }
        if (value > node->data){
            return contains(node->right, value);
        } else {
            return contains(node->left, value);
        }
}
/*  PUBLIC FUNCTION
* Purpose : insert the given value into the binary search tree while maintaining
* the binary search tree invariants
* Arguments : the current node, the node on the level above that points to the 
* current node, and the value that is to be inserted
* Returns : void
* Effects : Adds a node to the tree and increases the count if it already exists
* in the tree. Calls the private insert() function to do this.
*/
void BinarySearchTree::insert(int value){
        insert(root, nullptr, value);

}
/* 
* Purpose : insert the given value into the binary search tree while maintaining
* the binary search tree invariants
* Arguments : the current node, the node on the level above that points to the 
* current node, and the value that is to be inserted
* Returns : void
* Effects : Adds a node to the tree and increases the count if it already exists
* in the tree
*/
void BinarySearchTree::insert(Node *node, Node *parent, int value){
    (void) parent;
    if (tree_height(node) == -1){
        root = makeNode(value);
        return;
    }
    
    if (value == node->data){
        node->count += 1;
    }
    
    if (value > node->data){
        if (node->right != nullptr){
            insert(node->right, nullptr, value);
        } else {
            node->right = makeNode(value);
            return;
        }
    
    } else if (value < node->data){
        if (node->left != nullptr){
            insert(node->left, nullptr, value);
        } else {
            node->left = makeNode(value);
            return;
        }
    }
}

/* 
* Purpose : Create a new node with the given value (will always make a leaf)
* Arguments : the value that the new node should hold
* Returns : A pointer to the new node that was created
* Effects : none
*/
BinarySearchTree::Node *BinarySearchTree::makeNode(int value){
    Node *newNode = new Node;
    newNode->data = value;
    newNode->count = 1;
    newNode->right = nullptr;
    newNode->left = nullptr;
    return newNode;
}
/* 
* Purpose : Create a new node with the given value, the given count, and the 
* given right and left pointers (creates a new node that can be inserted into 
* the tree)
* Arguments : the value and count that the new node should hold, plus the left 
* and right pointers that it should have
* Returns : A pointer to the new node that was created
* Effects : none
*/
BinarySearchTree::Node *BinarySearchTree::makeNode(int value, 
                                                  int count, Node *right,
                                                  Node *left) const{
    Node *newNode = new Node;
    newNode->data = value;
    newNode->count = count;
    newNode->right = right;
    newNode->left = left;
    return newNode;
}

//PUBLIC: remove the node with the given value and return true, but if it is not
//found in the tree or if it was not removed return false
bool BinarySearchTree::remove(int value){
        return remove(root, value);
}
void BinarySearchTree::removeSingleChildLeft(Node *node, Node *parent,
                                            Node *deleter, bool left){
    if (left == true){
        parent->left = node->left;
    } else {
        parent->right = node->left;
    }
    node->left = nullptr;
    deleter = node;
    delete deleter;
}
void BinarySearchTree::removeSingleChildRight(Node *node, Node *parent, 
                                                Node *deleter, bool left){
    if (left == true){
        parent->left = node->right;
    } else {
        parent->right = node->right;
    }
    node->right = nullptr;
    deleter = node;
    delete deleter;
}
/* 
* Purpose : Remove the current node while maintaining the 
* Binary Search Tree invariants
* Arguments : a pointer to the current node, a pointer to the node pointing to 
* the current node, and a boolean representing if the current node is the right 
* or left child of the parent (true if it is the left child, false if not)
* Returns : A pointer to the new node that was created
* Effects : deletes the current node while maintaining binary search tree 
* invariants
*/
void BinarySearchTree::removeHelper(Node *parent, Node *node, bool left){
    Node *deleter = nullptr; 
    //0 children
    if (node->left == nullptr && node->right == nullptr){
        cout << "LEAF REMOVAL" << endl;
        deleter = node;
        if(left == true){
            parent->left = nullptr;
        } else {
            parent->right = nullptr;
        }
        delete deleter;
    }
    // 1 child on the Right
    else if (node->left == nullptr && node->right != nullptr){
        removeSingleChildRight(node, parent, deleter, left);
    }
    // 1 child on the left
    else if (node->right == nullptr && node->left != nullptr){
        removeSingleChildLeft(node, parent, deleter, left);
    }
    // 2 children
    else {
        int minRight = find_min(node->right)->data;
        int counter = find_min(node->right)->count;
        remove(node, minRight);
        node->data = minRight;
        node->count = counter-1;
    }
}
/* 
* Purpose : If the value that needs to be removed is in the root, then remove 
* the root and replace it with the node that has the smallest value in the right
* subtree
* Arguments : none
* Returns : none
* Effects : removes the root and replaces it with the node that has the smallest
* value in the right subtree
*/
void BinarySearchTree::removeRoot(){
    Node *deleter = root;
    
    //0 children
    if (root->left == nullptr && root->right == nullptr){
        root = nullptr;
        delete deleter;
    }
    // 1 child on the right
    else if (root->left == nullptr && root->right != nullptr){
        root = root->right;
        deleter->right = nullptr;
        delete deleter;
    }
    // 1 child on the left 
    else if (root->right == nullptr && root->left != nullptr){
        root = root->left;
        deleter->left = nullptr;
        delete deleter;
    }
    // 2 children
    else {
        int minRight = find_min(root->right)->data;
        int counter = find_min(root->right)->count;
        remove(root, minRight);
        root->data = minRight;
        root->count = counter-1;
    }
}
bool BinarySearchTree::findRemoveLeft(Node *node, int value){
    if (node->left->data == value){
        if (node->left->count > 1){
            node->left->count--;
            return false;
        } else {
            removeHelper(node, node->left, true);
            return true;
        }
    } else {
        return remove(node->left, value);
    }    
}
bool BinarySearchTree::findRemoveRight(Node *node, int value){
    if (node->right->data == value){
        if (node->right->count > 1){
            node->right->count--; 
            return false;
        } else {
            removeHelper(node, node->right, false);
            return true;
        }
    } else {
        return remove(node->right, value);
    }
}
/* 
* Purpose : Remove the node with the given value
* Arguments : the value that should be removed from the tree and a pointer to 
* the node from which the search should start
* Returns : a boolean - true if the node is removed, and false if not
* Effects : removes a node, but if it has a count of greater than 1 decrease the
* count 
*/
bool BinarySearchTree::remove(Node *node, int value){
    if (root == nullptr){
        cout << "EMPTY TREE" << endl;
        return false;
    }
    if (root->data == value){
        removeRoot();
        return true;
    } else {
        //go left if you can
        if (value < node->data && node->left != nullptr){
            return findRemoveLeft(node, value);
        //go right if you can
        } else if (value > node->data && node->right != nullptr){
            return findRemoveRight(node, value);
        } else {
            return false;
        }

    }  
}


int BinarySearchTree::tree_height() const {
        return tree_height(root);
}
/* 
* Purpose : Traverse the tree and count the length from the root to the farthest
* node (i.e. the height of the given node, which unless changed in the public 
* function call will be the root).
* Arguments : the node that the height is being calculated for (root)
* Returns : an integer representing the height
* Effects : none
*/
int BinarySearchTree::tree_height(Node *node) const {
        if (node == nullptr){
            return -1;
        }
        int leftDepth = tree_height(node->left) + 1;
        int rightDepth = tree_height(node->right) + 1;
        int depth =  maximum(leftDepth, rightDepth);
        return depth;
}

// returns the total number of nodes
int BinarySearchTree::node_count() const {
        return node_count(root);
}
/* 
* Purpose : count the number of nodes in the entire tree
* Arguments : A pointer to the node at which the counting is starting (the root)
* Returns : an integer representing the number of nodes
* Effects : none
*/
int BinarySearchTree::node_count(Node *node) const {
        // TODO: Students write code here
        int total = 0;
        
        if (node == nullptr){
            return total;
        }
        total++;
        return (total + node_count(node->left) + node_count(node->right));
        
        
}

// return the sum of all the node values (including duplicates)
int BinarySearchTree::count_total() const {
        return count_total(root);
}
/* 
* Purpose : Return the sum of all the node values (including duplicates)
* Arguments : a pointer to the node at which the counting is starting (the root)
* Returns : An integer representing the sum of all the node values
* Effects : none
*/
int BinarySearchTree::count_total(Node *node) const {
    
        // TODO: Students write code here:
        int counter = 0;
        if (node == nullptr){
            return counter;
        }
        for (int i = 0; i < node->count; i++){
            counter = counter + node->data;
        }

        return (counter + count_total(node->left) + count_total(node->right));
}
/* 
* Purpose : Calculates the maximum of two values
* Arguments : the two values that are being compared
* Returns : an integer that is the bigger of the two values that were passed in
* Effects : none
*/
int BinarySearchTree::maximum(int value, int value2) const {
    if (value > value2){
        return value;
    } else {
        return value2;
    }
}

BinarySearchTree::Node *BinarySearchTree::find_parent(Node *node,
                                                      Node *child) const {
        if (node == nullptr)
                return nullptr;

        // if either the left or right is equal to the child,
        // we have found the parent
        if (node->left == child or node->right == child) {
                return node;
        }

        // Use the binary search tree invariant to walk the tree
        if (child->data > node->data) {
                return find_parent(node->right, child);
        } else {
                return find_parent(node->left, child);
        }
}

// use the printPretty helper to make the tree look nice
void BinarySearchTree::print_tree() const {
        size_t      numLayers  = tree_height() + 1;
        size_t      levelWidth = 4;
        const char *rootPrefix = "-> ";

        // Need numLayers * levelWidth characters for each layer of tree.
        // Add an extra levelWidth characters at front to avoid if statement
        // 1 extra char for nul character at end
        char *start = new char[(numLayers + 1) * levelWidth + 1];

        print_tree(root, start + levelWidth, start + levelWidth, rootPrefix);
        delete[] start;
}

// Logic and Output Reference: 
// https://www.techiedelight.com/c-program-print-binary-tree/
void BinarySearchTree::print_tree(Node *node, char *const currPos,
                                  const char *const fullLine,
                                  const char *const branch) const
{
        if (node == nullptr)
                return;

        // 4 characters + 1 for nul terminator
        using TreeLevel                    = char[5];
        static const int       levelLength = sizeof(TreeLevel) - 1;
        static const TreeLevel UP = ".-- ", DOWN = "`-- ", EMPTY = "    ",
                               CONNECT = "   |";
        // Copies prev into dest and advances dest by strlen(prev)
        auto set = [](char *dest, const char *prev) {
                size_t p = strlen(prev);
                return (char *)memcpy(dest, prev, p) + p;
        };

        print_tree(node->right, set(currPos, EMPTY), fullLine, UP);

        // Clear any characters that would immediate precede the "branch"
        // Don't need to check for root (i.e start of array),fullLine is padded
        set(currPos - levelLength, EMPTY);

        // Terminate fullLine at current level
        *currPos = '\0';

        std::cerr << fullLine << branch << node->data
                  << (node->count > 1 ? "*" : "") << endl;

        // Connect upper branch to parent
        if (branch == UP)
                set(currPos - levelLength, CONNECT);

        // Connect lower branch to parent
        print_tree(node->left, set(currPos, CONNECT), fullLine, DOWN);
}
