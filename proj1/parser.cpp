/*
*
*  COMP 15 Project1: CalcYouLater
*
*  parser.cpp
*
*  Created By (UTLN): egjert01
*          On       : February 19, 2020
*
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "DatumStack.h"
#include "Datum.h"

using namespace std;

using namespace std;
string parseRString(istream &input);
bool checkLength(int stackLength);

int main(){
    string input;
    ifstream infile("fact3.cyl");
    if (infile.fail()) {
        cerr << "ERROR: could not open file fact2.cyl";
        exit(EXIT_FAILURE);
    }
    
    cout << parseRString(infile) << endl;
    return 0;
}

string parseRString(istream &input){
    int stackLength = 1;
    char search;
    string buildString = "{ ";
    while (input>>search){
        if (search == '{'){
            stackLength++;
        } else if (search == '}'){
            if (checkLength(stackLength)){
                return buildString;
            }
            stackLength--;
        }
        if (search == '}'){
            buildString += " ";
        }
        buildString += search;
        if (checkLength(stackLength)){
            return buildString;
        }
        if (search == '{'){
            buildString += " ";
        }
    }
    if (stackLength == 0){
        return buildString;
    } else {
        cerr << "NOT RIGHT" << endl;
        exit(0);
    }
}

bool checkLength(int stackLength){
    if (stackLength == 0){
        return true;
    } else {
        return false;
    }
}

