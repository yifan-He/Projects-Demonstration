#pragma once

#include <string>
#include <vector>
#include <set>
using namespace std;

class Territory
{
private:
	string name;
	int id;
	int continentID;
	string continentName;
	string player;
	int armyNum;
	bool connected;
	bool buildCity;
	string tokenName;
	bool isToken;

public:
	vector<int> nearTerritory; // territories that are connected over water 
	vector<int> nearTerritorySameContinent; // territeories that are connected over land

	Territory();
	~Territory();
	Territory(string name, string continentName, int id, int continentID);
	Territory(string name, string continentName, int id, int ContinentId, vector<int> nearTerritory, vector<int> nearTerritorySameContinent);
	Territory(string name, string continentName,int id, int continentID, bool connectedForeignContient, string player, bool buildCity, int armyNum);
	Territory(const Territory& other);

	Territory& operator = (const Territory& other);

	string GetName();
	int GetID();
	string GetContinentName();
	int GetContinentID();
	string GetPlayer();
	int GetArmyNum();
	string GetTokenName();
	bool GetIsToken();
	void SetTokenName(string name);
	void SetIsToken(bool isToken);

	void SetArmyNum(int num);
	bool GetConnected();
	void SetConnected(bool canGoOut);
	vector<int> GetNearTerritory();
	vector<int> GetNearTerritorySameContinent();
	void SetTerritoryName(string name);
	void SetTerritoryID(int id);
	void DisplayTerritorys(vector<int> v);
	bool GetBuildCity();
	void SetBuildCity();
	void AddArmy(int armyNum);
	void SetPlayer(string player);
	friend ostream& operator<<(ostream& output, const Territory& other);

};

class Continent
{
public:
	string name;
	int id;
	int territoryCount;
	vector<Territory*> territorys;
	set<int> reachableContinents;

	Continent();
	~Continent();
	Continent(string name, int id,int territoryCount);
	Continent(string name, int id, int territoryCount, set<int> reachablecontinents);
	Continent(const Continent& other);
	Continent& operator = (const Continent&);
	friend ostream& operator<<(ostream& output, const Continent& other);

	string GetName();
	int GetID();
	vector<Territory*> GetTerritory();
	int getTerritoryCount();
	bool CheckGraph();
	set<int> GetReachableContinent();
};

class Map
{
public:
	string name;
	int continentCount;
	bool validateMap ;
	vector<Continent*> continents;

	Map();
	~Map();
	Map(string name, int continentCount,bool validateMap);
	Map(const Map& other);
	Map& operator = (const Map&);

	friend ostream& operator<<(ostream& output, const Map& other);

	string GetName();
	void SetName(string name);

	//int GetTerritoryCount();
	int GetContinentCount();

	//vector<Territory*> GetTerritorys();

	//void DisplayTerritorys();
	void DisplayAllContinent();
	//print map
	
	void validate();

	vector<Territory*> GetAllTerritorys();
};








