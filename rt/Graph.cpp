 /**********************************************************
 * Project 2: Road Trip!
 * Filename: Graph.cpp 
 * Contains: Implementation of the Graph class. Creates graph 
 *      data structures that can be filled by the client
 * Part of: Lab assignment "Graph Traversal" for Comp 15, written by comp15 
 *          staff
 * Modified by: Emily Gjertsson (Egjert01) April 2020
 *
 *********************************************************/
 
#include <iostream>
#include <stack>
#include <iomanip>
#include <vector>
#include "Graph.h"
#include "Location.h"
using namespace std;

/* Function: constructor
* Parameters: none
* Returns: nothing
* Does: default constructor. Initializes with zero vertices
*/
Graph::Graph(){
    curr_vertex = pIndex = curr_vertex = num_vertices = 0;
    num_paths = 1;

    edges       = nullptr;
    path        = nullptr;
    vertices    = nullptr;
    marks       = nullptr;
}
/* Function: parametrized constructor
* Parameters: integer (size of graph)
* Returns: nothing
* Does: default constructor. Initializes with num_v vertices
*/
Graph::Graph(int num_vertices){
    initialize_graph(num_vertices);
}
/* Function: destructor
* Parameters: none 
* Returns: none
* Does: deletes all dynamically allocated memory
*/
Graph::~Graph(){
    delete[] vertices;
    delete[] marks;
    delete[] path;
    //Free each sub-array
    for(int i = 0; i < num_vertices; ++i) {
            delete[] edges[i];   
    }
    //Free the array of pointers
    delete[] edges;
    
    path = NULL;
    marks = NULL;
    vertices = NULL;
    edges = NULL;
}
/* Function: copy constructor
* Parameters: reference to another Graph object
* Returns: none
* Does: copies everything from the reference of the other Graph
*       object to the current object
*/
Graph::Graph(const Graph &source){
    reassign(source);

    copyArray<Node>(source.vertices, vertices, num_vertices);
    copyArray<int>(source.path, path, num_vertices);
    copyArray<bool>(source.marks, marks, num_vertices); 
    
    for (int i = 0; i < num_vertices; i++){
        for (int j = 0; j < num_vertices; j++){
            edges[i][j] = source.edges[i][j];
        }
    }
}


/* Function: copyArray
* Parameters: the array we're copying from and the one we're copying to, and 
*             the length of the arrays
* Returns: void
* Does: copies all the contents from one array to another
* Note: is a template function so will accept any type
*/
template<typename t>
void Graph::copyArray(t from[], t to[], int length){
    for (int i = 0; i < length; i++){
        to[i] = from[i];
    }
}

/*Function: reassign
* Paramters: a separate Graph object 
* Returns: void 
* Does: An extension of the copy constructor and the assignment operator 
*       reassigns all elements from the source to this graph object
*/
void Graph::reassign(const Graph &source){
    num_paths = source.num_paths;
    pIndex = source.pIndex;
    num_vertices = source.num_vertices;
    curr_vertex  = source.curr_vertex;
    
    vertices = new Node[num_vertices];
    path = new int[num_vertices];
    marks = new bool[num_vertices];
    edges = new int*[num_vertices];
    
    for (int i = 0; i < num_vertices; i++){
        edges[i] = new int[num_vertices];
    }
}

/* Function: initialize_graph
* Input: integer, number of vertices
* Returns: void
* Does: dynamically allocates all memory
*       for a graph of num_v vertices 
*       without any vertices
*       and prepares all DFS, BFS variables
*/
void Graph::initialize_graph(int numNums){
    this->curr_vertex  = 0;
    this->num_paths = 1;
    this->num_vertices = numNums;
    this->vertices     = new Node[numNums];
    this->marks        = new bool[numNums];
    this->path         = new int[numNums];
    this->edges        = new int *[numNums];

    for (int i = 0; i < numNums; i++)
        edges[i] = new int[numNums];

    for (int i = 0; i < numNums; i++) {
        marks[i] = false;
        path[i]  = NULL_PRED;
        for (int j = 0; j < numNums; j++)
            edges[i][j] = NULL_EDGE;
    }
}
/* Function: add_vertex
* Parameters: Vertex, by value
* Returns: void
* Does: Add a new vertex to the end of the 2d array
*       Initializes every from/to edge to be nullptr
*/
void Graph::add_vertex (Node v){
     vertices[curr_vertex] = v;
     for (int i = 0; i < num_vertices; i++)
     {
         edges[curr_vertex][i] = NULL_EDGE;
         edges[i][curr_vertex] = NULL_EDGE;
     }
     curr_vertex++;
 }
/* Function: add_edge
* Parameters: Two vertices, and integer (weight)
* Returns: void
* Does: Adds an edge between the two vertices and 
*       assigns their weight equal to the given integer
*       (in case the edge did not exist) 
*/
 void Graph::add_edge (Node from, Node to) {
     int row;
     int col;

     row = index_is(vertices, from);
     col = index_is(vertices, to);
     if (edges[row][col] == NULL_EDGE)
         edges[row][col] = 1;
 }

/* Function: find_vertex
* Parameters: string (name of city we're looking for), doubles representing 
*      the longitutde and latitude of that city
* Returns: Nothing, directly (parameters are passed by reference so they will
*      be changed)
* Does: find a vertex of the graph with the given city name
*      convert the coordinates of the city into two decimals
*      If no city with that name is found, warn the user
*/
void Graph::convertCoords(string city, double &decLat, double &decLon){
    for (int i = 0; i < num_vertices; i++){
        if (vertices[i].city == city){
            // converts decLat and decLon to forms which the location class 
            // can interpret
            decLat = convertCoordsToDec(vertices[i].lat, vertices[i].latMins);
            decLon = convertCoordsToDec(vertices[i].lon, vertices[i].lonMins);
            
            return;
        }
    }
    cout << "ERROR: unknown city" << endl;
}

/* Function: findVertex
* Parameters: a string representing a city member of a struct 
* Returns: The node that contains the string as a member of its struct
* Does: Finds the corresponding node
*       Returns that node 
*       If no node is found inform the user, and return a dummy node
*/
Node Graph::findVertex(string vName){
    for (int i = 0; i < num_vertices; i++){
        if (vertices[i].city == vName){
            return vertices[i];
        }
    }
    cout << "ERROR: unknown city" << endl;
    Node not_found = { "not found", -1, -1, -1, -1};
    return not_found;
    
}

/* Function: pathQ (PUBLIC)
* Parameters: a starting node, a string representing the target, and 
*       an integer representing the desired number of paths printed
* Returns: void
* Does: calls the DFS function to perform depth first search recursively 
*       on the graph until either the desired number of paths are printed 
*       or until no more paths are found 
*       DFS function prints these paths
*/
void Graph::pathQ(Node start, string end, int count){
    pIndex = 0;
    pathFound = false;
    if (DFS(start, end, count) == count){
        cout << "ERROR: no-path-possible" << endl;
    }

}
/* Function: DFS (called from pathQ)
* Parameters: a starting node, a string representing the target, and 
*       an integer representing the desired number of paths printed
* Returns: an integer representing how many paths are left to print
* Does: Perform depth first search recursively 
*       on the graph until either the desired number of paths are printed 
*       or until no more paths are found 
*       Prints these paths
*/
int Graph::DFS(Node v, string target, int count){
    mark_vertex(v);
    path[pIndex] = findIndex(v); 
    pIndex++;

    if (v.city == target){ // Found a path
        pathFound = true;
        report_path();
        cout << endl;
        count--;
    }
    
    // Recurse on the neighbors
    vector<int> neighbors = findNeighbors(v);
    for (size_t i = 0; i < neighbors.size(); i++){ 
        if (count == 0){
            break;
        }
        if (!is_marked(vertices[neighbors.at(i)])){
            update_predecessor(v, vertices[neighbors.at(i)]);
            count = DFS(vertices[neighbors.at(i)], target, count);
        }
    }
    pIndex--;
    int currIndex = findIndex(v);
    marks[currIndex] = false;
    return count;
}

/* Function: convert given coordinates to a double
* Parameters: integer representing a Latitude or Longitude degree, and int 
*      representing the corresponding latitude/longitude minutes.
* Returns: a double representing the given coordinates in a decimal
* Does: convert given coordinate to a double number 
*/
double Graph::convertCoordsToDec(int latLon, int mins){
    if (latLon > 0){
        return ((mins/60.0) + latLon);
    } else {
        return (latLon - (mins/60.0));
    }
}

/* Function: is_vertex
* Parameters: vertex
* Returns: bool
* Does: Returns true if vertex exists in the graph, false otherwise
*/
bool Graph::is_vertex (string v) {
    for (int i = 0; i < num_vertices; i++) {
        if (vertices[i].city == v)
            return true;
    }
    return false;
}

/* Function: findNeighbors
* Parameters: A Node struct
* Returns: A vector holding all the neighbors to the Node
* Does: Creates a vector to hold neighbors 
*       uses the adjacency matrix to populate the vector
*/
vector<int> Graph::findNeighbors(Node vertex){
    vector<int> neighborsIndex;
    neighborsIndex.clear();
    int index = findIndex(vertex);
    for (int i = 0; i < num_vertices; i++){
        if (edges[index][i] == 1){
            neighborsIndex.push_back(i);
        }
    }
    return neighborsIndex;
}

/* Function: findIndex  
* Parameters: a Node struct
* Returns: an int representing the index of the 
*       vertices array where the Node is
* Does: cycles through the vertices array until 
*       the desired Node is found
*/
int Graph::findIndex(Node v){
    int index = 0;
    while (not (v.city == vertices[index].city)){
        index++;
    }
    return index;   
}
/* Function: stringToNode
* Parameters: a string holding a city name
* Returns: a node
* Does: finds the node in the vertices array that 
*       has the same city name
*       if no such node exists return a dummy node
*/
Node Graph::stringToNode(string v){ 
    for (int i = 0; i < num_vertices; i++){
        if (v == vertices[i].city){
            return vertices[i];
        }
    }
    
    Node not_found = { "not found", -1, -1, -1, -1};
    return not_found;

}

/* Function: print_vertices
* Parameters: none
* Returns: void
* Does: prints the whole vertices array
*/
void Graph::print_vertices() const {
    for (int i = 0; i < num_vertices; i++){
        cout << vertices[i].city << endl;
    }
}

/* Function: initialize_path
* Parameters: none
* Returns: none
* Does: sets every value in the predecessor path to be NULL edge
*/
void Graph::initialize_path(){
    for (int i = 0; i < num_vertices; i++)
        path[i] = NULL_PRED;
}
/* Function: update_predecessor
* Parameters: Two vertices
* Returns: None
* Does: sets pred as the predecessor of curr in the path
*       (in case that curr did not have any predecessor)
*       Nothing otherwise.
*/
void Graph::update_predecessor (Node pred, Node curr){
    int pred_index, curr_index;
    for (int i = 0; i < num_vertices; i++)
    {
        if (vertices[i].city == pred.city)
            pred_index = i;
        if (vertices[i].city == curr.city)
            curr_index = i;
    }
    if (path[curr_index] == NULL_PRED)
        path[curr_index] = pred_index;
}
/* Function: report_path
* Parameters: none
* Returns: void
* Does: prints the stored path
*       uses the information stored on predecessor path 
*/
void Graph::report_path(){
    double decLat1, decLon1, decLat2, decLon2;
    Node curr = vertices[path[0]];
    Node prev = vertices[path[0]];
    
    convertCoords(curr.city, decLat2, decLon2);
    
    cout << "PATH " << num_paths << " :: " << 0 << " " << vertices[path[0]].city
         << " " << setprecision(2) << fixed << decLat2 << " "  
         << setprecision(2) << fixed << decLon2 << " ";

    for (int i = 1; i < pIndex; i++){
        curr = vertices[path[i]];
        convertCoords(prev.city, decLat1, decLon1);
        convertCoords(curr.city, decLat2, decLon2);
        Location from(decLat1, decLon1);
        Location to(decLat2, decLon2);
        int distance = from.distance_to(to);
        
        cout << distance << " ";
        cout << curr.city << " " << setprecision(2) << fixed << decLat2 << " "  
        << setprecision(2) << fixed << decLon2 << " ";
        prev = curr;
    }
    num_paths++;
}

/* Function: clear_marks
* Parameters: none
* Returns: none
* Does: sets all the marks to be false
*       For algorithms that need to mark vertices (BFS, DFS)
*/
void Graph::clear_marks(){
    for (int i = 0; i < num_vertices; i++) {
        marks[i] = false;
    }
}
/* Function: mark_vertex
// Parameters: Vertex
// Returns: none
// Does: sets the mark of the given vertex to true
*/
void Graph::mark_vertex (Node v){
    for (int i = 0; i < num_vertices; i++) {
        if (vertices[i].city == v.city)
            marks[i] = true;
    }
}
/* Function: is_marked
// Parameters: Vertex
// Returns: bool
// Does: returns true if the vertex is marked
//       false otherwise
*/
bool Graph::is_marked (Node v) const{
    for (int i = 0; i < num_vertices; i++) {
        if (vertices[i].city == v.city)
            return marks[i];
    }
    return false;
}


/* wrapper function definitions
// Function: index_is
// Parameters: array of vertices, Vertex
// Returns: integer
// Does: Finds the target vertex in the list of vertices
//       returns the index of v
*/
int index_is (Node *vertices, Node v){
    int index = 0;
    while (not (v.city == vertices[index].city))
        index++;
    return index;
}

