#include "..\header\MapLoader.h"
#include <iostream>
#include <fstream>
#include "..\lib\json.hpp"
// ref https://github.com/nlohmann/json

// for convenience
using json = nlohmann::json;

//default constructor
MapLoader::MapLoader()
{
    this->fileName = "No file Name yet.";
    this->map = nullptr;
}

//constructor with three parameter
MapLoader::MapLoader(string newFileName)
{
    this->fileName = newFileName;
    this->map = nullptr;
}

//copy constructor
MapLoader::MapLoader(const MapLoader *maploader)
{
    this->fileName = maploader->fileName;
    this->map = maploader->map;
}

//assignment operator
MapLoader &MapLoader::operator=(const MapLoader &maploader)
{
    this->fileName = maploader.fileName;
    this->map = maploader.map;

    return *this;
}

ostream &operator<<(ostream &out, MapLoader &mapLoader) {
	cout << "File Name is " << mapLoader.fileName << "map Name is " << mapLoader.map->name;
	return out;
}

//accessor
string MapLoader::getFileName()
{
    return this->fileName;
}

Map *MapLoader::getMap()
{
    return this->map;
}

//mutator
void MapLoader::setFileName(string newFileName)
{
    this->fileName = newFileName;
}

void MapLoader::clearMap()
{
    this->map = nullptr;
}


bool MapLoader::readMapFile()
{
    map = nullptr;
    ifstream ifs(this->fileName);
    if (!ifs.is_open())
    {
        cout << "Failed to open the file...  " << endl;
        return false;
    }

    json mapJson;
    ifs >> mapJson;
    ifs.close();
    cout << "Read Map from ...json File :\n" << mapJson << endl;

    // load map object
    Map *map = new Map(mapJson["name"], mapJson["continentCount"],false);

    // process continent
    if (mapJson["continentCount"] != mapJson["continents"].size())
    {
        cout << "continentCount does not match continents array, expected " << mapJson["continentCount"] << ", found " << mapJson["continents"].size() << endl;
        map = nullptr;
        return false;
    }


	
    for (int i = 0; i < mapJson["continentCount"]; i++)
    {
        json continentJson = mapJson["continents"][i];

        Continent *cont = new Continent(
            continentJson["name"],
            continentJson["id"],
            continentJson["territoryCount"]
				
		);
		
		for (int r = 0; r < continentJson["reachableContinents"].size(); r++) {
			int s = continentJson["reachableContinents"][r].get<int>();
			cont->reachableContinents.insert(s);
		}

        // process territory
        if (continentJson["territoryCount"] != continentJson["territorys"].size())
        {
            cout << "territoryCount does not match territorys array , expected " << continentJson["territoryCount"] << ", found " << continentJson["territorys"].size() << endl;
            map = nullptr;
            return false;
        }

        for (int j = 0; j < continentJson["territoryCount"]; j++)
        {
            json territoryJson = continentJson["territorys"][j];
            if (territoryJson["continentId"] != cont->GetID())
            {
                cout << "territory refrenced an invalid continent id: " << territoryJson["continentId"] << endl;
                map = nullptr;
                return false;
            }
			
			
            Territory *territory = new Territory(
				territoryJson["name"], 
				territoryJson["continentName"],
				territoryJson["id"], 
				territoryJson["continentId"]
			);
			
		
			for (int r = 0; r < territoryJson["nearTerritory"].size(); r++) {
				int s = territoryJson["nearTerritory"][r].get<int>();
				territory->nearTerritory.push_back(s);
			}

			for (int r = 0; r < territoryJson["nearTerritorySameContinent"].size(); r++) {
				int s = territoryJson["nearTerritorySameContinent"][r].get<int>();
				territory->nearTerritorySameContinent.push_back(s);
			}
				

            cont->territorys.push_back(territory);
        }
        map->continents.push_back(cont);
    }

    this->map = map;
	cout << endl;

    return true;
}


//deconstructor
MapLoader::~MapLoader()
{
    if (this->map != NULL)
    {
        delete map;
		map = NULL;
    }
}
