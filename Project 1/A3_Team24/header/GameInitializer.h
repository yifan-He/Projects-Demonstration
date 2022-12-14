#pragma once
#include "Map.h"
#include "MapLoader.h"
#include "Player.h"
#include "Cards.h"
#include "Bidding.h"
#include <vector>
#include "Score.h"
#include "..\header\PlayerStrategies.h"
#include <ctime>
#include<iostream>
#include"GameObserver.h"

using namespace std;



class GameInitializer{

public:
	const string mapFileFolder = "../mapFiles";
	MapLoader* mapLoader;
	Map* map;
	vector<Player*> players;
	int pool;
    GameInitializer();
	~GameInitializer();
	void game_Show();
	void show_Menu();
    vector<string> getGameMapFiles();
	Map* getCurrentMap();
    void loadMap(string mapFileName);
    void addPlayer(string playerName);
    string getMapFileFolder();
	void printMapInRectangleShape(Map*m);
	void printMapInRectangleShape2(Map* m1);
	void printMapInLShape(Map* m);
	void printMapInLShape2(Map* m1);
	Map * choose_Map();
	vector<Player*>& choose_Player();
	void exitSystem();
	
	void assignCoin();
	//string bidPhase();
	void playGame(int playerNumber, Hand* hand, Deck* deck,GameInitializer* gm);
	void SetInitialRegion(int winnerIndex);
	void doAction(Player* p, Card* c1);
	void actions(Player* p, string action);
	Territory*IDtoTerri(int id);
	


	vector<Territory*> transferNearTerri(Territory* currentTerri);
	vector<Territory*> removeDuplicates(vector<Territory*> vec);
	vector<Territory*> ReachableTerritoryInner(Territory* startTerri, int step, Player* p);
	//vector<Territory*> ReachableTerritoryouter(Territory* outerStartTerri, int step)

	vector<Territory*> NotPlayerName(vector<Territory*> list, Player* p);
	vector<Territory*> transferNearTerriOverSea(Territory* currentTerri);// transfer id to territory for NearTerritory
	vector<Territory*>  overseaTwice(Territory* outerStartTerri);

	vector<Territory*> ReachableTerritoryouter(Territory* outerStartTerri, int step, Player* p);
	vector<Territory*> merge(vector<Territory*> inner, vector<Territory*> outer);

	void doAbility(Player* p, Card* c1);
};
