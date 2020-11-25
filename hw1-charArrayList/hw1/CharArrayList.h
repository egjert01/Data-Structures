/*
 *
 *  COMP 15 HW 1 Cheshire ConCATenation - no strings attached
 *
 *  CharArrayList.h
 *
 *  Complete Array List Class Declaration
 *
 *  Modified By YOURNAME: Emily Gjertsson
 *           On         : January 22, 2020
 *
 */

 #include <string>

 #ifndef CHARARRAYLIST_H_
 #define CHARARRAYLIST_H_

 class CharArrayList {
     public: 
       //constructors
       CharArrayList();
       CharArrayList(char element);
       CharArrayList(char *arrayCopy, int lengthCopy);
       CharArrayList(const CharArrayList &other);
       CharArrayList &operator=(CharArrayList &rhs);
       
       //destructor
       ~CharArrayList();
       
       /* Takes no parameters and returns a
       boolean value that is true if this specific instance of the
       class is empty (has no characters) and false otherwise.*/
       bool isEmpty();
       
       /* Takes no parameters and has a void
       return type. It makes the instance into an empty array list.
       For example if you call the "clear" function and then the
       "isEmpty" function the "isEmpty" function should return true.*/
       void clear();
       
       /*Takes no parameters and returns an
       integer value that is the number of characters in the array
       list. The size of an array list is 0 if and only if it isEmpty.*/
       int size();
       
       /*Takes no parameters and returns the
       first element (char) in the array list. */
       char first();
       
       /*Takes no parameters and returns the last
       element (char) in the array list. */
       char last();
       
       /*Takes an integer index and returns
       the element (char) in the array list at that index. NOTE: Indices are
       0−based. */
       char elementAt(int index);
       
       /* Takes no parameters and has a void
       return type. It prints the array list of characters stored in
       the instance to the screen (cout).*/
       void print();
       
       /* Takes an element (char) and has a
       void return type. It inserts the given new element after the end
       of the existing elements of the array list.*/
       void pushAtBack(char element);
       
       /* Takes an element (char) and has
       a void return type. It inserts the given new element in front
       of the existing elements of the array list.*/
       void pushAtFront(char element);
       
       /* Takes an element (char) and an
       integer index as parameters and has a void return type. It
       inserts the new element at the specified index and shifts the
       existing elements as necessary. The new element is then in the
       index−th position.*/
       void insertAt(char element, int index);
       
       /*Takes an element (char),
       inserts it into the array list in alphabetical order, and
       returns nothing. When this function is called, it may assume
       the array list is correctly sorted in ascending order, and it
       should insert the element at the first correct index. */
       void insertInOrder(char element);
       
       /*Takes no parameters and has a
       void return type. It removes the first element from the
       array list.*/
       void popFromFront();
       
       /*Takes no parameters and has a
       void return type. It removes the last element from the
       array list. */
       void popFromBack();
       
       /* Takes an integer index and has a
       void return type. It removes the element at the specified
       index. */
       void removeAt(int index);
       
       /*Takes an element (char) and an integer
       index as parameters and has a void return type. It replaces the
       element at the specified index with the new element. */
       void replaceAt(char element, int index);
       
       /* Yakes a pointer to a second
       CharArrayList and has a void return type. It adds a copy of the
       array list pointed to by the parameter value to the end of the
       array list the function was called from. */
       void concatenate(CharArrayList *array2);
       
       /* Takes no parameters and has a void
       return type. It reduces the object’s memory usage to the bare
       minimum required to store its elements (i.e. it does not use any
       extra space).*/
       void shrink();
       
       //Getters
       int getCapacity();
       void expand();

     private: 
       int capacity;
       int length;
       char *array;
       
       void resize(int newSize);
 };

 #endif 

