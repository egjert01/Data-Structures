/*
*
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "MetroSim.h"
#include "Passenger.h"
#include "PassengerQueue.h"

using namespace std;

void readStations(string fileName, MetroSim &m);
void readCin(MetroSim &m, int &id, string outputFile);
void readComFile(MetroSim &m, string comFile, int &id, string outputFile);
Passenger newPassenger(int onLoad, int offLoad, int &id);

int main(int argc, char *argv[]){
	if (argc < 2 || argc > 4){
		// Incorrect number of argument, inform the user then quit the program
		cerr << "Usage: ./MetroSim stationsFile outputFile [commandsFile]" << endl;
		exit(EXIT_FAILURE);
	} else {
		
		string fileName = argv[1];
		string outputFile = argv[2];
		//cout << outputFile << endl;
		int id = 0;
		MetroSim m;
		
		readStations(fileName, m);
		m.openFile(outputFile);
		m.makeTrainQ();
		m.print();
		
		cout << "Command? ";
		
		if (argc == 3){
			// Getting commands from user via cin >> 
			readCin(m, id, outputFile);
			
		} else if (argc == 4){
			// Getting commands from a file 
			string comFile = argv[3];
			cout << "ERRROR" << endl;
			readComFile(m, comFile, id, outputFile);
			
		} 
	}
	return 0;
}

void readCin(MetroSim &m, int &id, string outputFile){
	string query, junk;
	int onLoad, offLoad;
	istringstream lineStream;
	getline(cin, query);
	
	while (query != "m f"){
		if (query == "m m" || query == " m m " || query == " m m" || query == "m m "){
			m.moveMetro(outputFile);
		} else {
			lineStream.str(query);
			
			lineStream >> junk;
			if (junk == "p"){
				lineStream >> onLoad >> offLoad;
				Passenger newPass = newPassenger(onLoad, offLoad, id);
				m.addPassenger(newPass);
				m.print();
			}
		}
		cout << "Command? ";
		lineStream.clear();
		getline(cin, query);
	}
	cout << "Thanks for playing MetroSim. Have a nice day!" << endl;
}
void readComFile(MetroSim &m, string comFile, int &id, string outputFile){
	cout << "READING" << endl;
	// Try to open the file
	ifstream infile(comFile.c_str());
	if (infile.fail()) {
		cerr << "ERROR: could not open file "<< comFile;
		exit(EXIT_FAILURE);
	}
	cout << "TEST" << endl;
	string query, junk;
	int onLoad, offLoad;
	istringstream lineStream;
	getline(infile, query);
	while (!infile.eof()){
		while (query != "m f"){
			if (query == "m m" || query == " m m " || query == " m m" || query == "m m "){
				m.moveMetro(outputFile);
			} else {
				cout << "MAKING PASSENGER" << endl;
				
				lineStream.str(query);
				
				lineStream >> junk;
				if (junk == "p"){
					lineStream >> onLoad >> offLoad;
					Passenger newPass = newPassenger(onLoad, offLoad, id);
					m.addPassenger(newPass);
					m.print();
				}
			}
			cout << "Command? ";
			lineStream.clear();
			getline(infile, query);
		}
		cout << "Thanks for playing MetroSim. Have a nice day!" << endl;
	}
	
}

Passenger newPassenger(int onLoad, int offLoad, int &id){
	Passenger newPassenger;
	id++;
	newPassenger.id = id;
	newPassenger.from = onLoad;
	newPassenger.to = offLoad;
	return newPassenger;
}

void readStations(string fileName, MetroSim &m){
	// Try to open the file
	string stationName;
	ifstream infile(fileName.c_str());
	if (infile.fail()) {
		cerr << "ERROR: could not open file "<< fileName << endl;
		exit(EXIT_FAILURE);
	}
	int counter = 1;
	while (getline(infile, stationName)){
		Station *newStation = new Station;
		newStation->stopNum = counter;
		newStation->stopName = stationName;
		m.addStation(newStation);
		counter++;
	}
	m.setNumStations(counter);
	
}

