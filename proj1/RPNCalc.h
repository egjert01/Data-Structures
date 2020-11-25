/*
*
*  COMP 15 Project1: CalcYouLater
*
*  RPNCalc.h
*
*  Created By (UTLN): egjert01
*          On       : February 26, 2020
*
* Purpose: Interface of RPNCalc class
* 
*/
#include "DatumStack.h" 

class RPNCalc {
public:
    RPNCalc();
    ~RPNCalc();
    
    void run();
    
    private:
        DatumStack stack;
        string comparisons[5] = {"<", ">", "<=", ">=", "=="};
        
        void readQueryA(istream &input, string &query);
        void readQueryB(string query);
        void bigCommands(string query);
        
        void numInput(int number);
        void trueFalse(string boolean);
        void invert();
        void print();
        void clear();
        void drop();
        void dup();
        void swap();
        
        void plusMinus(string operation);
        void quotients(string operation);
        void comparing(string comparison);
        void lessThan(int elem1, int elem2);
        void greaterThan(int elem1, int elem2);
        void lessOrEqual(int elem1, int elem2);
        void greaterOrEqual(int elem1, int elem2);
        void equals(int elem1, int elem2);
        
        void exec();
        void ifQuery();
        void file();
        
        bool verifyRString(string rString);
        string parseRString(istream &input);
        
        bool checkLength(int stackLength);
        bool areInts(int *elem1, int *elem2);
        bool isEmpty();
        void errorMessage(string code);
        bool got_int(string s, int *resultp);
};