/*
*
*  COMP 15 Project1: CalcYouLater
*
*  main.cpp
*
*  Created By (UTLN): egjert01
*          On       : February 16, 2020
*
* Purpose: The file from which the program will be run. Holds only the main 
* function and a call to the only public function in the RPNCalc which simply 
* starts running the program.
*/
#include "DatumStack.h"
#include "RPNCalc.h"

using namespace std;

int main(){
    RPNCalc calc;
    calc.run();

    return 0;
}
