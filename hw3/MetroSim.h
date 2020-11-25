/*
*
*  COMP 15 HW 3: A Metro Simulator
*
*  MetroSim.h
*  
*  Created By (UTLN): egjert01
*          On       : February 5, 2020
*
*/

#ifndef _METROSIM_H_
#define _METROSIM_H_

#include <vector>
#include <string>
#include <iostream>
#include "Passenger.h"
#include "PassengerQueue.h" 

using namespace std;

struct Station{
    int stopNum;
    string stopName;
    PassengerQueue stationQ;
};

class MetroSim {
    
public:
    //constructor
    MetroSim();
    //destructor
    ~MetroSim();
    
    void pickUp();
    void board(Passenger passenger);
    void dropOff(string outputFile);
    
    void makeTrainQ();

    void print();
    void moveMetro(string outputFile);
    void addStation(Station *newStation);
    
    void addPassenger(Passenger passenger);
    
    void setNumStations(int counter);
    int getNumStations();
    
    void openFile(string outputFile);
    
private:
    vector<Station> stations;
    vector<PassengerQueue> trainQ;
    
    int trainLocation;
    int numStations;
    
    int getNextIndex();
    void streamToFile(string outputFile);
    void printTrain();
    
    ofstream output;


};

#endif
