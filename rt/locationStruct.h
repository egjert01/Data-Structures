/**********************************************************
* Project 2: Road Trip!
* Filename: locationStruct.h
* Contains: the Node struct, holding the name and coordinates of a city
* Written by: Emily Gjertsson (Egjert01) April 2020
*
*********************************************************/

#ifndef LOCATIONSTRUCT_H_
#define LOCATIONSTRUCT_H_

#include <string>
using namespace std;

struct Node{
    string city;
    int lat, latMins;
    int lon, lonMins;
};

#endif