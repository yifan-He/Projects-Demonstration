#include "..\header\Map.h"
#include <iostream>
#include <iomanip>
#include <stack>
#include <typeinfo>

using namespace std;

Territory::Territory()
{
    name = "";
    id = 0;
    continentName = "";
    continentID = 0;
    player = "";
    armyNum = 0;
    connected = false;
}
Territory::Territory(string name, string continentName, int id, int continentID)
{
    this->name = name;
    this->id = id;
    this->continentName = continentName;
    this->continentID = continentID;
    this->armyNum = 0;
    this->connected = false;
}
Territory::Territory(string name, string continentName, int id, int ContinentId, vector<int> nearTerritory, vector<int> nearTerritorySameContinent) {
	this->name = name;
	this->id = id;
	this->continentName = continentName;
	this->continentID = continentID;
	this->nearTerritory = nearTerritory;
	this->nearTerritorySameContinent = nearTerritorySameContinent;
}

Territory::Territory(string name, string continentName, int id, int continentID, bool connectedForeignContient, string player, bool buildCity, int armyNum)
{
    this->name = name;
    this->continentName = continentName;
    this->id = id;
    this->continentID = continentID;
    this->connected = connectedForeignContient;
    this->player = player;
    this->armyNum = armyNum;
    this->buildCity = buildCity;
}

Territory::Territory(const Territory &other)
{
    this->name = other.name;
    this->continentName = other.continentName;
    this->id = other.id;
    this->continentID = other.continentID;
    this->connected = other.connected;
    this->player = other.player;
    this->armyNum = other.armyNum;
    this->buildCity = other.buildCity;
}

Territory &Territory::operator=(const Territory &other)
{
    this->name = other.name;
    this->continentName = other.continentName;
    this->id = other.id;
    this->continentID = other.continentID;
    this->connected = other.connected;
    this->player = other.player;
    this->armyNum = other.armyNum;
    this->buildCity = other.buildCity;
    return *this;
};

Territory::~Territory()
{
}

string Territory::GetName()
{
    return name;
}

int Territory::GetID()
{
    return id;
}

string Territory::GetContinentName()
{
    return continentName;
}

int Territory::GetContinentID()
{
    return continentID;
}

string Territory::GetPlayer()
{
    return player;
}



int Territory::GetArmyNum()
{
	return armyNum;
}

void Territory::SetArmyNum(int num)
{
	this->armyNum = num;
}






bool Territory::GetConnected()
{
    return connected;
}

vector<int> Territory::GetNearTerritory()
{
    return nearTerritory;
}
vector<int> Territory::GetNearTerritorySameContinent()
{
    return nearTerritorySameContinent;
}

void Territory::SetTerritoryName(string name)
{
    name = name;
}

void Territory::SetTerritoryID(int id)
{
    id = id;
}

void Territory::SetConnected(bool canGoOut)
{
    connected = canGoOut;
}

void Territory::DisplayTerritorys(vector<int> v)
{
    if (v.size() != 0)
    {
        int len = v.size();
        for (int i = 0; i < len; i++)
        {
            cout << "DisplayTerritorys: " << v[i];
        }
    }
    else
    {
        cout << " No Territory Element! ";
    }
}

bool Territory::GetBuildCity()
{
    return buildCity;
}

string Territory::GetTokenName() {
	return tokenName;
}

bool Territory::GetIsToken() {
	return isToken;
}

void Territory::SetTokenName(string name) {
	this-> tokenName = name;
}

void Territory::SetIsToken(bool isToken) {
	this->isToken = isToken;
}

void Territory::AddArmy(int armyNum)
{
    this->armyNum += armyNum;
}

void Territory::SetBuildCity()
{
    buildCity = true;
}

void Territory::SetPlayer(string player)
{
    this->player = player;
}

ostream &operator<<(ostream &output, const Territory &other)
{
    string temp;
	//if buildCity is false
    if (other.buildCity == 0)
        temp = "No";
    else
        temp = "Yes";

    output << "Territory Name: " << other.name << ", Player: " << other.player << ", Build City: " << temp << ", Army: " << other.armyNum << endl;
    return output;
}

Continent::Continent()
{
    name = "";
    id = 0;
    territoryCount = 0;
}

Continent::Continent(string name, int id, int territoryCount)
{
    this->name = name;
    this->id = id;
    this->territoryCount = territoryCount;
}
Continent::Continent(string name, int id, int territoryCount, set<int> reachableContinents) {
	this->name = name;
	this->id = id;
	this->territoryCount = territoryCount;
	this->reachableContinents = reachableContinents;
}

Continent::Continent(const Continent &other)
{
    this->name = other.name;
    this->id = other.id;
}

Continent &Continent::operator=(const Continent &other)
{
    this->name = other.name;
    this->id = other.id;
	this->territoryCount = other.territoryCount;
	for (int i = 0; i < other.territoryCount; i++) {
		this->territorys[i] = other.territorys[i];
	}
	this->reachableContinents = other.reachableContinents;
    return *this;
}

Continent::~Continent()
{
}

ostream &operator<<(ostream &output, const Continent &other)
{
    output << "Continent name: " << other.name << "id: " << other.id << endl;
    return output;
}

string Continent::GetName()
{
    return name;
}
int Continent::GetID()
{
    return id;
}
vector<Territory *> Continent::GetTerritory()
{
    return territorys;
}

int Continent::getTerritoryCount() {
	return territoryCount;
}

bool Continent::CheckGraph()
{
    int len = this->territorys.size();
	//vector to hold the territories id
    vector<int> visited;

    for (int i = 0; i < len; i++)
    {
        if (visited.empty())
        {
            visited.push_back(this->territorys[i]->GetID());
        }
		// get the size of the territories are connected over land of territory[i]
        int len1 = this->territorys[i]->nearTerritorySameContinent.size();
        for (int j = 0; j < len1; j++)
        {
			//the neighbour territory of territory[i]
            int temp = this->territorys[i]->nearTerritorySameContinent[j];
            int len2 = visited.size();

            for (int k = 0; k < len2; k++)
            {
                if (temp == visited[k])
                {
                    break;
                }
                if (k == (len2 - 1))
                {
                    if (temp != visited[k])
                    {
                        visited.push_back(temp);
                    }
                }
            }
        }
    }
    if (visited.size() != len)
    {
        return false;
    }
    return true;
}

set<int> Continent::GetReachableContinent()
{
    return reachableContinents;
}

Map::Map()
{
    name = "";
    continentCount = 0;
	validateMap = false;                   
}

Map::Map(string name, int continentCount, bool validateMap)
{
    this->name = name;
    this->continentCount = continentCount;
	this->validateMap=validateMap;
}

Map::Map(const Map &other)
{
    this->name = other.name;
    this->continentCount = other.continentCount;
    this->continents = other.continents;
	this->validateMap = other.validateMap;
}

Map &Map::operator=(const Map &other)
{
    this->name = other.name;
    this->continentCount = other.continentCount;
	for (int i = 0; i < other.continentCount; i++) {
		this->continents[i] = other.continents[i];
	}
	this->validateMap = other.validateMap;
    return *this;
}

Map::~Map()
{
}

ostream &operator<<(ostream &output, const Map & m)
{	

	cout << "Current Map name is:\n" << m.name << endl;
	cout << "Current Map has " << m.continentCount << " Continents and " << endl;
	for (int i = 0; i < m.continentCount; i++) {
		cout << m.continents[i]->name<< " has reachable continent is: ";
		for (set<int>::iterator it = m.continents[i]->reachableContinents.begin();it != m.continents[i]->reachableContinents.end(); it++) {
			cout << "   " << *it << "   ";
		}
		cout << endl;
		cout << "Contient " << i + 1 << " has " <<m.continents[i]->getTerritoryCount() << " Territories." << endl;
		for (int j = 0; j < m.continents[i]->getTerritoryCount(); j++) {
			cout << "Territory" << j + 1 << " Name is: " << m.continents[i]->territorys[j]->GetName() << " ; the owner is: "<< m.continents[i]->territorys[j]->GetPlayer()<< "\n";
		}
		int count = 0;
		int count1 = 0;
		string name1 = "";
		string name2 = "";
		for (int j = 0; j < m.continents[i]->getTerritoryCount(); j++) {
			if (m.continents[i]->territorys[j]->GetPlayer() != "") {
				if(name1=="")
					name1 = m.continents[i]->territorys[j]->GetPlayer();
				if (m.continents[i]->territorys[j]->GetPlayer() != name1) {
					name2 = m.continents[i]->territorys[j]->GetPlayer();
					break;
				}
			}
		}
		for (int j = 0; j < m.continents[i]->getTerritoryCount(); j++) {
			if (name1 == "" ) {
				count = 0;
			}
			else {
				if (m.continents[i]->territorys[j]->GetPlayer() == name1)
					count++;
			}
			if (name2 == "")
				count1 = 0;
			else {
				if (m.continents[i]->territorys[j]->GetPlayer() == name2)
					count1++;
			}
			
		}
		if(count1>count)
			cout<<m.continents[i]->GetName() << ": the owner is: " << name2 << "\n";
		else if (count1<count)
			cout << m.continents[i]->GetName() << ": the owner is: " << name1 << "\n";
		else
			cout << m.continents[i]->GetName() << ": has no onwer. "<< "\n";
		cout << endl;
	}
	return output;
	
}

string Map::GetName()
{
    return name;
}


int Map::GetContinentCount()
{
    return continentCount;
}

void Map::SetName(string name)
{
    name = name;
}

void Map::DisplayAllContinent()
{
    cout << continents.size() << endl;
}

void Map::validate()
{
    int len = this->continents.size();
    set<int> visitedContinent;
    set<int>::const_iterator iter;

    // check if continent connected
    for (int i = 0; i < len; i++)
    {
        if (this->continents[i]->CheckGraph())
        {
            cout << "Map's Continent->" << this->continents[i]->GetName() << " is connected." << endl;
        }
        else
        {
            cout << "Map's Continent->" << this->continents[i]->GetName() << " is not connected." << endl;
            cout << "Map is invalid because at least one continent subgraph is not connected." << endl;
            break;
        }
    }

    // check if map connected
    for (int j = 0; j < len; j++)
    {
        for (iter = this->continents[j]->reachableContinents.begin(); iter != this->continents[j]->reachableContinents.end(); ++iter)
        {
            visitedContinent.insert(*iter);
        }
    }

    if (visitedContinent.size() != len)
    {
        cout << "Map is not valid!" << endl;
    }
    else
    {
        cout << "Map is valid, enjoy the game.\n" << endl;
		this->validateMap = true;
    }

    // check if territory belongs to single continent
    cout << "By design, a territory can only reference one continent \n\n\n";


}


vector<Territory*> Map::GetAllTerritorys()
{
	vector<Territory*> territories;
	for (int i = 0; i < continentCount; i++) {
		for (int j = 0; j < continents[i]->getTerritoryCount(); j++) {
			territories.push_back(continents[i]->territorys[j]);
		}
	}
	return territories;
}
