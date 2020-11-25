/*
*
*  COMP 15 HW 3: A Metro Simulator
*
*  MetroSim.cpp
*  
*  Created By (UTLN): egjert01
*          On       : February 5, 2020
*
*/

#include <iostream>
#include <fstream>

#include "MetroSim.h"
#include "PassengerQueue.h"
#include "Passenger.h"

MetroSim::MetroSim(){
    trainLocation = 1;
}
MetroSim::~MetroSim(){
    output.close();
}

void MetroSim::makeTrainQ(){
    for (int i = 0; i < numStations; i++){
        PassengerQueue q;
        trainQ.push_back(q); 
    }
}

void MetroSim::moveMetro(string outputFile){
    pickUp();
    dropOff(outputFile);
    trainLocation = getNextIndex();
    print();
}

void MetroSim::dropOff(string outputFile){
    int size = trainQ[trainLocation-1].size();
    while (size != 0){
        size = trainQ[trainLocation-1].size();
        if (size == 0){
            break;
        }
        output << "Passenger " << trainQ[trainLocation-1].front().id << 
        " left train at station " << stations[trainLocation-1].stopName << endl;
        trainQ[trainLocation-1].dequeue();
    }
}

void MetroSim::openFile(string outputFile){
    output.open(outputFile);

}

void MetroSim::pickUp(){
    int size = stations.at(trainLocation-1).stationQ.size();
    while (size != 0 ){
        size = stations.at(trainLocation-1).stationQ.size();

        //stations.at(trainLocation-1).stationQ.print();
        if (size == 0){
            break;
        }
        board(stations.at(trainLocation-1).stationQ.front());
        stations.at(trainLocation-1).stationQ.dequeue();
    }
}

void MetroSim::board(Passenger passenger){
    trainQ[passenger.id].enqueue(passenger);
}

int MetroSim::getNextIndex(){
    trainLocation++;
    
    trainLocation = trainLocation%numStations;
    if (trainLocation == 0){
        trainLocation = 1;
    }
    return trainLocation;
}

void MetroSim::print(){
    cout << "Passengers on the train: {"; 
    printTrain(); 
    cout << "}" << endl;

    for (int i = 0; i < numStations-1; i++){
        if (trainLocation == i+1){
            cout << "TRAIN: ";
        } else {
            cout << "       ";
        }
        
        cout << "[" << stations.at(i).stopNum << "] " << stations.at(i).stopName;
        cout << " {";
        stations.at(i).stationQ.print(); 
        cout << "}";
        cout << endl;
    }
}

void MetroSim::printTrain(){
    for (int i = 0; i < numStations; i++){
        trainQ[i].print();
    }
}

void MetroSim::addPassenger(Passenger passenger){
    for (int i = 0; i < numStations; i++){
        if (stations.at(i).stopNum == passenger.from){
            stations.at(i).stationQ.enqueue(passenger);
            break;
        }
    }

}

void MetroSim::setNumStations(int counter){
    numStations = counter;
}
int MetroSim::getNumStations(){
    return numStations;
} 

void MetroSim::addStation(Station *newStation){
    stations.push_back(*newStation);
}