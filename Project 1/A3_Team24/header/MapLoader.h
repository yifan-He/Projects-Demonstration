#pragma once

#include <string>
#include <vector>
#include <set>
#include "Map.h"

using namespace std;

class MapLoader {
	friend ostream &operator<<(ostream &out, MapLoader &mapLoader);
private: 
	string fileName;							            //input file 
    Map* map;                                               // generated map object

public:
	MapLoader();								            //default constructor	
	MapLoader( string newFileName);	                        //constructor with two parameter
	MapLoader(const MapLoader * maploader);		            //copy constructor
	MapLoader& operator=(const MapLoader & maploader);		//assignment operator
	

	//accessor
	string getFileName();                                   // get current file name
    Map* getMap();                                          // get current map object

	//mutator
	void setFileName(string newFileName);                   // set current file name 
    void clearMap();                                        // clear current map object

	//to generate Territory
    bool readMapFile();                                     // reads the map file, if valid, return true and map object is set , else return false and map object is cleared; 

	//deconstructor
	~MapLoader();								
};
