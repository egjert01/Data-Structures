/**********************************************************
* Project 2: Road Trip!
* Filename: testGraph.cpp 
*
* A separate file created in order to test that the Graph class was 
* functional, so within this testing file I created a Graph object and used many 
* of the class methods on it to make sure they worked and that I understood how 
* everything worked within the class.
*
* Created by: Emily Gjertsson (Egjert01) April 2020
*
*********************************************************/

#include "Graph.h"
#include "locationStruct.h"
#include <iostream>
#include <string>

using namespace std;
void makeGraph(Node &one, Node &two, Node &three, Graph &graph);
void makeLocations(Node &one, Node &two, Node &three, Graph &graph);
void checkGraph(Graph graph, Node one);

int main(){
    cerr << "STARTING PROGRAM" << endl;
    Graph graph(3);
    Node one, two, three;

    makeGraph(one, two, three, graph);
    
    return 0;
}

// Function: checkGraph
// Parameters: The Graph object and a node
// Returns: void 
// Does: Makes sure that the graph was populated correctly by checking if the 
//      vertex exists in the graph
void checkGraph(Graph graph, Node one){
    if (graph.is_vertex(one)){
        cout << "is vertex :)" << endl;
    } else {
        cout << "is not vertex :(" << endl;
    }
}

// Function: makeGraph
// Parameters: Three references to vertices/nodes, and a reference to a graph
//      object 
// Returns: void 
// Does: populated the graph with the nodes and edges
//      prints the matrix of edges
void makeGraph(Node &one, Node &two, Node &three, Graph &graph){
    makeLocations(one, two, three, graph);
    
    graph.add_vertex(one);
    graph.add_vertex(two);
    graph.add_vertex(three);
    graph.add_edge(one, two, 4);
    graph.add_edge(two, three, 5);
    graph.add_edge(three, one, 6);
    
    graph.print_matrix(cout);
    
    checkGraph(graph, one);
}

// Function: makeLocations
// Parameters: Three references to vertices/nodes, and a reference to a graph 
//      object 
// Returns: void 
// Does: Flushes out all three vertices/nodes 
void makeLocations(Node &one, Node &two, Node &three, Graph &graph){
    one.city = "New York";
    two.city = "Kirkland";
    three.city = "Pheonix";

    one.lat = 1;
    two.lat = 2;
    three.lat = 3;
    
    one.lon = -1;
    two.lon = -2;
    three.lon = -3;
    
}



