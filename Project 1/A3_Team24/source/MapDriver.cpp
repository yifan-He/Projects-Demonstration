#include <iostream>
#include "..\header\Map.h"
using namespace std;

class MapDriver
{
    public : 
    void run()
    {
        // valid map
        Map *map1 = new Map("map1", 2,false);
        Territory *territory1 = new Territory("territory1", "continent1", 1, 1, false, "", false, 0);
        Territory *territory2 = new Territory("territory2", "continent2", 2, 2, false, "", false, 0);
        Continent *continent1 = new Continent("continent1", 1, 1);
        Continent *continent2 = new Continent("continent2", 2, 1);

        territory2->nearTerritory.push_back(territory1->GetID());
        territory1->nearTerritory.push_back(territory2->GetID());

        continent1->territorys.push_back(territory1);
        continent2->territorys.push_back(territory2);
        continent1->reachableContinents.insert(continent2->id);
        continent2->reachableContinents.insert(continent1->id);

        map1->continents.push_back(continent1);
        map1->continents.push_back(continent2);

        map1->validate();
    }
};