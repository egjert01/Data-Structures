/**********************************************************
* Project 2: Road Trip!
* Filename: Driver.cpp
* Contains: main driver of the Graph class: 
*          Takes care of the running of the program -- i.e. 
*          making the graph objects, reading in from the file, 
*          and recieving input as queries
* Created by: Emily Gjertsson (Egjert01) April 2020
*
*********************************************************/

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <iomanip>

#include "Graph.h"
#include "locationStruct.h"
#include "Location.h"
#include "Driver.h"

using namespace std;

int Driver::run(char *argv[]){
    
    int length = lengthOfFile(argv[1]);
    Graph g(length);
    
    readVertexFile(argv[1], length, g);
    length = lengthOfFile(argv[2]);
    readAdjFile(argv[2], length, g);
    
    readInQueries(g);
    
    return 0;                   
}

// Function: readInQueries
// Parameters: graph object 
// Returns: void 
// Does: Reads in the queries that the user inputs
//       deals with queries (calls corresponding functions)
void Driver::readInQueries(Graph g){
    string query, first, city1, city2;
    int max;
    istringstream linestream;
    getline(cin, query);
    
    while(query != "quit"){
        if (query == "list"){
            g.print_vertices();
        }else {
            linestream.str(query);
            linestream >> first;
            if (first == "dist"){
                linestream >> city1 >> city2;
                distanceQuery(g, city1, city2);
            } else if (first == "path"){
                linestream >> city1 >> city2 >> max;
                pathQuery(g, city1, city2, max);
            }
        }
        cout << "-EOT-" << endl;
        linestream.clear();
        getline(cin, query);
    }
}

// Function : pathQuery
// Parameters: Graph object, two strings representing the cities, and an int 
//          holding number of desired paths if they exist
// Returns: void 
// Does: calls verify cities function to ensure both cities are valid 
//      calls the graph function that outputs the desired number of paths
void Driver::pathQuery(Graph g, string city1, string city2, int max){
    if (!verifyCities(city1, city2, g)){
        cout << "ERROR: unknown city" << endl;
        return;
    }

    Node start = g.findVertex(city1);
    g.pathQ(start, city2, max);
}

// Function: distanceQuery
// Parameters: Graph object, two strings representing the cities the distance is
//      being calculated for 
// Returns: void
// Does: Creates two location objects
//      prints the distance between the given cities        
void Driver::distanceQuery(Graph g, string city1, string city2){
    if (!verifyCities(city1, city2, g)){
        cout << "-1.00" << endl;
        return;
    }
    
    double decLat1, decLon1, decLat2, decLon2;
    g.convertCoords(city1, decLat1, decLon1);
    g.convertCoords(city2, decLat2, decLon2);
    Location from(decLat1, decLon1);
    Location to(decLat2, decLon2);
    cout << setprecision(2) << fixed << from.distance_to(to) << endl;
}

// Function: verifyCities
// Parameters: Graph object, two strings representing cities 
// Returns: bool representing if the cities are valid
// Does: checks to make sure that the cities are present in the graph 
//       if cities are not present it informs the user
bool Driver::verifyCities(string city1, string city2, Graph g){
    
    if (!g.is_vertex(city1)){
        return false;
    }
    if (!g.is_vertex(city2)){
        return false;
    }
    
    return true;
}

// Function: readFile
// Parameters: a string holding the name of the file being read from, an integer
//      holding the length of the file (how many vertices there will be), and 
//      a reference to the graph object
// Returns: void 
// Does: opens the file
//      checks for errors opening the file 
//      Populate the graph with data read from the file
//      closes the file
void Driver::readVertexFile(string filename, int length, Graph &g){
    ifstream infile(filename);
    if (infile.fail()){
        cerr << "Unable to open " << filename << endl;
    }
    Node places[length];
    string city;
    for (int i = 0; i < length; i++){
        Node aPlace;
        infile >> aPlace.city >> aPlace.lat >> aPlace.latMins 
                              >> aPlace.lon >> aPlace.lonMins;
        places[i] = aPlace;
        g.add_vertex(aPlace);
    }
    infile.close();
}

// Function: readAdjFile
// Parameters: A string holding the name of the file being read from, an integer
//      holding the length of the file (how many edges there will be), and a 
//      reference to the graph object
// Returns: void
// Does: opens the file 
//      checks for errors opening the file 
//      populate the adjacency matrix in the Graph class with information 
//          from the file 
//      close the file
void Driver::readAdjFile(string filename, int length, Graph &g){
    ifstream infile(filename);
    if (infile.fail()){
        cerr << "unable to open " << filename << endl;
    }
    for (int i = 0; i < length; i++){
        string fromS, toS;
        Node from, to;
        infile >> fromS >> toS;
        from = g.findVertex(fromS);
        to = g.findVertex(toS);
        
        g.add_edge(from, to);
    }
    infile.close();
}

// Function: lengthOfFile
// Parameters: a string holding the name of the file
// Returns: an integer holding the length of the file
// Does: opens the file 
//      checks for errors, if file is unable to open tell the user
//      counts the number of lines, and then closes the file
int Driver::lengthOfFile(string filename){
    ifstream infile(filename);
    if (infile.fail()){
        cerr << "Unable to open " << filename << endl;
        exit(1);
    }
    int length = 0;
    string junk;
    while (getline(infile, junk)){
        length++;
    }
    infile.close();
    return length;
    
}