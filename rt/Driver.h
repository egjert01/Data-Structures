/**********************************************************
* Project 2: Road Trip!
* Filename: Driver.h 
* Contains: Interface of the template Driver class.
*          Takes care of the running of the program -- i.e. 
*          making the graph objects, reading in from the file, 
*          and recieving input as queries
* Created by: Emily Gjertsson (Egjert01) April 2020
*
*********************************************************/

#include "Graph.h"

#ifndef DRIVER_H_
#define DRIVER_H_

class Driver{
public:
    int run(char *argv[]);
    
private:
    bool verifyCities(string city1, string city2, Graph g);
    
    void readInQueries(Graph g);
    void distanceQuery(Graph g, string city1, string city2);
    void pathQuery(Graph g, string city1, string city2, int max);
    
    int lengthOfFile(string filename);
    void readVertexFile(string filename, int fileLength, Graph &g);
    void readAdjFile(string filename, int fileLength, Graph &g);    
};


#endif