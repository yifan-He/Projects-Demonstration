#pragma once
#include "../header/Cards.h"
using namespace std;


class PlayerStrategies;


class Strategy {
private:
	PlayerStrategies* playerStrategy;

public:
	Strategy();
	Strategy(PlayerStrategies* PlayerS);
	~Strategy();
	void set_strategy(PlayerStrategies* playerS);
	int pick(Hand* hand);
};




class PlayerStrategies {
public:
	virtual int pickCard(Hand* hand) = 0;
};



//Human player
class Human : public PlayerStrategies {
public:
	int pickCard(Hand* hand);
};

//Greedy Computer
class Greedy : public PlayerStrategies {
public:
	int pickCard(Hand* hand);
};

//Moderate computer
class Moderate : public PlayerStrategies {
public:
	int pickCard(Hand* hand);
};

