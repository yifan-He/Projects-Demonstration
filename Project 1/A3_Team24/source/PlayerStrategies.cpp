

#include "../header/PlayerStrategies.h"



Strategy::Strategy() {

}


Strategy::Strategy(PlayerStrategies* otherStrategy) {
	this->playerStrategy = otherStrategy;
}

Strategy::~Strategy() {
	delete this->playerStrategy;
	playerStrategy = NULL;
}


void Strategy::set_strategy(PlayerStrategies* otherStrategy) {
	this->playerStrategy = otherStrategy;
}


int Strategy::pick(Hand *hand) {
	return this->playerStrategy->pickCard(hand);
}


int Human::pickCard(Hand* hand) {
	int index;
	cout << "  what index of card do u want, please insert 0-5 please!";
	cin >> index;
	return index;
}

int Greedy::pickCard(Hand* hand) {


	for (int i = 0; i < 6; i++)
	{
		if (hand->getCard(i)->getAction1() == "BuildCity" || hand->getCard(i)->getAction2() == "Destory") {
			return i;
		}
	}

	return 0;
}

int Moderate::pickCard(Hand* hand) {


	for (int i = 0; i < 6; i++)
	{
		if (hand->getCard(i)->getAction1().substr(0, 4) == "Move" || hand->getCard(i)->getAction2().substr(0, 3) == "Add" 
			|| hand->getCard(i)->getAction2().substr(0, 4) == "Move" || hand->getCard(i)->getAction1().substr(0, 3) == "Add") {
			return i;
		}
	}
	return 0;
}









