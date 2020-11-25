 /**********************************************************
 * Project 2: Road Trip!
 * Filename: Graph.h 
 * Contains: Interface of the template Graph class 
 * Part of: Lab assignment "Graph Traversal" for Comp 15,
 *          written by comp15 staff
 * Modified by: Emily Gjertsson (Egjert01) April 2020
 *
 *********************************************************/

#include "locationStruct.h"
#include <iostream>
#include <ostream>
#include <queue>

#ifndef GRAPH_H_
#define GRAPH_H_

using namespace std;
// A good way to handle errors is with exceptions
// This class has a couple of them for common errors
// In this case we have one when there is no memory to 
// allocate and when someone does an invalid operation 
class FullGraph : public exception
{
public:
    const char *what() const throw()
    {
        return "Graph is full";
    }
};

class EmptyGraph : public exception
{
public:
    const char *what() const throw()
    {
        return "Graph is empty";
    }
};

// wrapper functions
int index_is(Node *vertices, Node v);

class Graph {
public:
    
    //Constructor functions
    Graph();
    Graph(int num_vertices);
    ~Graph();
    // Copy constructor 
    Graph(const Graph &source);
    // Assignment overload
    Graph &operator=(const Graph &source);
    
    //populate graph
    void add_vertex(Node v);
    void add_edge(Node from, Node to);
    
    bool is_vertex(string v);                      // true if exists

    // dist command
    void convertCoords(string city, double &decLat, double &decLon);
    Node findVertex(string vName);


    void pathQ(Node start, string end, int count); //path command

    void print_vertices() const; // list command

    
    
private:
    void reassign(const Graph &source);
    
    template<typename t> 
    void copyArray(t from[], t to[], int length);
    
    void initialize_graph(int num_vertices);
    
    int findIndex(Node v);
    Node stringToNode(string v);
    vector<int> findNeighbors(Node vertex);    
    
    void clear_marks();
    void mark_vertex(Node v);
    bool is_marked(Node v) const;
    
    void initialize_path();                              // clears path info
    void update_predecessor(Node pred, Node succ);   // stores predecessor
    
    double convertCoordsToDec(int latLon, int mins);
    
    int DFS(Node v, string target, int count);
    void report_path();


    static const int NULL_EDGE = -1;
    static const int NULL_PRED = -1;

    int      num_vertices;       // number of vertices of the graph
    Node     *vertices;           // stores label of vertices, if any
    int      **edges;              // weighted 2-D array to store edges 
    
    int      num_paths;
    
    int      *path;               // array used to store a path
    int       pIndex;
    bool     pathFound;

    int      curr_vertex;        // variable to track current vertex in DFS
    bool     *marks;              // used to mark that a vertex has been visited
    
};

#endif
