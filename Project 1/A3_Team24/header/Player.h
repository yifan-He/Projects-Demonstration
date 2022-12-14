#pragma once
#include <vector>
#include <iostream>
#include <string>
#include "Map.h"
#include "Cards.h"
#include "Bidding.h"

using namespace std;
class Player 
{

public:
	Player();
	~Player();

	Player(string name,vector<Card*> handCard,Bidding* bid);
	Player(string name, int coin, int move, vector<Territory*> territory, vector<Card*> handCard, Bidding* bid, string color);
	Player(const Player& other);
	Player& operator = (const Player& other);

	void PayCoin(int coin);
	void PlaceNewArmies(Territory* territory, int army);
	void MoveArmies(Territory* pointA, Territory* pointB, int army);
	void MoveOverLand(Territory* pointA, Territory* pointB, int army);
	void BuildCity(Territory* territory);
	void DestroyArmy(Territory* territory, int army);

	string GetName();
	void setName(string name);
	int GetMove();
	void SetMove(int move);
	int GetCoin();
	void SetCoin(int coin);
	int getArmy();
	void setArmy(int army);
	int getCity();
	void setCity(int city);
	Bidding * getBid();
	string getColor(string s);
	void setcolor(string s);


	vector<Territory*> GetTerritorys();
	void setTerritories(Territory* t);
	void setIm(bool b);

	bool getIm();
	vector<Card*> GetHandCard();
	void SetHandCard(Card* other);
	void AddArmy(int army);
	void AddTerritory(int city);
	bool CheckTerritory(Territory* other);
	void DisplayTerritory();
	void setElixer(int i);
	int getElixer();
	void setVp(int i);
	int getVp();
	
	friend ostream& operator<<(ostream& output, const Player& other);

private:
	string name;
	int coin;
	int move;
	int army;
	int city;
	vector<Territory*> territory;
	vector<Card*> handCard;
	string color;
	Bidding* bid;
	int elixer;
	int vp;
	bool immu=false;
};