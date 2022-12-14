




#include <iostream>
#include <string>
#include "..\header\Cards.h"
#include "..\header\Player.h"
#include <filesystem>
#include <algorithm>
#include<string>
#include <stdio.h>
using namespace std;
#include <random>


//Card**********************************
Card::Card() {};
Card :: ~Card() {};
Card::Card(string gd, string typ, string act, string abt)
{
	good = gd;
	action[0] = act;
	ability = abt;
	andor = typ;
}

Card::Card(string gd, string typ, string act1, string act2, string abt)
{
	good = gd;
	andor = typ;
	action[0] = act1;
	action[1] = act2;
	ability = abt;
}

//Copy constructor
Card::Card(const Card& c)
{
	this->good = c.good;
	this->action[0] = c.action[0];
	this->action[1] = c.action[1];
	this->ability = ability;
}

string Card::getGood()
{
	return good;
}

string Card::getAndOr() {
	return  andor;
}

string Card::getAction1()
{
	return action[0];
}

string Card::getAction2()
{
	return action[1];
}

string Card::getAbility()
{
	return ability;
}
//print information
void Card::printCard()
{
	cout << "This is the card information: \n" << endl;
	cout << "Good: " << good << endl;
	cout << ", Ability: " << ability ;
	cout << ", Action: " << action[0] ;
	if (andor == "and") cout << " AND " ;
	if (andor == "or")cout << " OR " ;
	cout << "Action: " << action[1];

}
// toString method
ostream& operator<<(ostream& out, const Card& card) {
	
	cout << "*Information* Good: " << card.good  << ",  Action1: " << card.action[0];
	if (card.andor == "and") {
		cout << "  AND  Action2: " << card.action[1];
	}
	else if (card.andor == "or") {
		cout << "  OR  Action2: "<< card.action[1];
	}
	else {
		cout << " ";
	}
	cout<< ", Ability: " << card.ability;
	
	return out;
}

// assignment operator
Card& Card::operator=(const Card& another)
{
	if (&another == this)
		return *this;
	this->good = another.good;
	this->andor = another.andor;
	this->action[0] = another.action[0];
	this->action[1] = another.action[1];
	this->ability = another.ability;
				
	return *this;
}


//Deck****************************************


//Creates the whole deck
void Deck::generateDeck(){
	//each card with good and 2 or 1 action
	 cards[0] = Card(gd.PIXIE, "", "Move4", "",abt.Plus1Army);
    cards[1] = Card(gd.STRONGHOLD, "", "BuildCity", "",abt.Plus1VpDire);
    cards[2] = Card(gd.PhOneElinix, "", "Move5", "", abt.FYLING);
    cards[3] = Card(gd.Spirit, "", "Add4", "", abt.ThreeEli);
    cards[4] = Card(gd.WOODS, "and", "BuildCity", "Add1", abt.Plus1Army);
    cards[5] = Card(gd.SAGE, "", "Move3", "", abt.Plus1VpAncient);
    cards[6] = Card(gd.CB, "", "Move6", "", abt.TwoEli);
    cards[7] = Card(gd.GAR, "", "Move5", "", abt.FYLING);
    cards[8] = Card(gd.KING, "or", "Add3", "Move4", abt.OneEli);
    cards[9] = Card(gd.MAUSOLEUM, "", "BuildCity", "", abt.Plus1Move);
    cards[10] = Card(gd.TOWER, "", "BuildCity", "", abt.Plus1VpFlying);
    cards[11] = Card(gd.DRAGON, "and", "Add3", "Destory", abt.FYLING);
    cards[12] = Card(gd.GIANT, "and", "Add3", "Destory", abt.Attack);
    cards[13] = Card(gd.EYE, "", "Add4", "", abt.FYLING);
    cards[14] = Card(gd.GOB, "", "Move4", "", abt.OneEli);

    cards[15] = Card(gd.OGRE, "", "Move2", "", abt.Plus1TwoCoin);
    cards[16] = Card(gd.LAKE, "or", "Add2", "Move3", abt.Plus1VpForest);
    cards[17] = Card(gd.ELF, "or", "Add3", "Move2", abt.Plus1Army);
    cards[18] = Card(gd.GNOME, "", "Move2", "", abt.ThreeEli);
    cards[19] = Card(gd.TOWN, "", "BuildCity", "", abt.Plus1Move);
    cards[20] = Card(gd.GRAVEYARD, "", "Add2", "", abt.Plus1VpCursed);
    cards[21] = Card(gd.HILLS, "", "Add3", "", abt.All3Eli5VP);
    cards[22] = Card(gd.KNIGHT, "and", "Add4", "Destory", abt.Plus1Move);
    cards[23] = Card(gd.UNICORN, "and", "Move4", "Add1", abt.Plus1Move);
    cards[24] = Card(gd.HYDRA, "and", "Move4", "Destory", abt.Plus1Army);
    cards[25] = Card(gd.VILLAGE, "", "BuildCity", "", abt.Plus1Army);
    cards[26] = Card(gd.WIZARD, "and", "Add4", "Destory", abt.Plus1VpNight);

    //3 Player cards
    if (Deck::numberP >= 3) {
        cards[27] = Card(gd.SPHINX, "or", "Add3", "Move4", abt.FYLING);
        cards[28] = Card(gd.MANTI, "and", "Add4", "Destory", abt.Plus1Move);
        cards[29] = Card(gd.TwoEliMPLE, "", "Move3", abt.Plus1VpArcaine);
        cards[30] = Card(gd.DWARF, "and", "Add2", "Destory", abt.Win3TwoMountain);
        cards[31] = Card(gd.TREASURY, "", "Move3", abt.OneEliAndTwoCoin);
    }
    //4 Player cards
    if (Deck::numberP >= 4) {
        cards[32] = Card(gd.CASTLE, "or", "Add4", "BuildCity", abt.OneEli);
        cards[33] = Card(gd.CASTLE2, "and", "Move3", "BuildCity", abt.OneEli);
    }


}

Deck::Deck()
{
	topCard = &cards[0];
	numberP = 2;
}

//CopyConstructor
Deck::Deck(const Deck& d)
{
	topCard = d.topCard;
	for (int i = 0; i < 34; i++)
	{
		cards[i] = d.cards[i];
	}
}

Deck::Deck(int numPlay) {
	topCard = &cards[0];
	numberP = numPlay;
}

//Deconstructor
Deck ::~Deck()
{

	topCard = nullptr;
}
//Displays all deck
void Deck::printDeck()
{
	for (int i = 0; i < getNumCards(); i++)
	{
		cout << "This is the whole card information: " << i + 1 << endl;
		cout << "Card number: " << i + 1 << endl;
		cards[i].printCard();
		cout << endl;
	}
}
int Deck::getNumCards() {
	if (this->numberP == 2) return 27;
	if (this->numberP == 3) return 32;
	if (this->numberP == 4) return 34;
}

int Deck::myRandomGenerator(int number) {
	return rand() % number;
}

void  Deck::shuffleDeck() {
	srand(unsigned(time(NULL)));
	/*for (int i = 0; i < getNumCards(); i++) {
		int index = rand() % getNumCards();
		Card* temp =& cards[i];
		cards[i] = cards[index];
		cards[index] = *temp;	
	}*/

	//_Random_shuffle1(&cards[0], &cards[getNumCards()], myRandomGenerator);


	Card a[27];
	for (int i = 26; i >= 0; i--) {
		a[i] = cards[26 - i];
	}

	_Random_shuffle1(&cards[0], &cards[getNumCards()], myRandomGenerator);

	for (int i = 0; i < 14; i++) {
		Card* temp = &cards[i];
		cards[i] = a[13 + i];
		a[i] = *temp;
	}

	for (int i = 14; i < 27; i++) {
		Card* temp = &cards[i];
		cards[i] = a[i - 14];
		a[i] = *temp;
	}





}





//draw card 
Card* Deck::draw()
{
	Card* card = topCard;
	topCard++;
	return card;
}

// toString Deck
ostream& operator<<(ostream& out, const Deck& deck)
{
	for (int i = 0; i < ((new Deck())->getNumCards()); i++) {
		cout << "Card " << i + 1 << ": " << deck.cards[i] << endl;
	}
	cout<<"\nWe have "<<deck.numberP<<" Players and play with "<<(new Deck())->getNumCards() <<" piece of cards for this term.\n"<<endl;
	return out; 

}


// Assignment operator.
Deck& Deck::operator=(const Deck& anotherDeck)
{
	if (&anotherDeck == this)
		return *this;
	for (int i = 0; i < 34; i++)
	{
		cards[i] = anotherDeck.cards[i];
	}
	topCard = &cards[0];
	return *this;
}


//hand*******************************************************
Hand::Hand() {

}

Hand::Hand(Deck* dk)
{
	deck = dk;
	//draw 6 cards from deck
	for (int i = 0; i < 6; i++)
	{
		cards[i] = deck->draw();
	}
}

//CopyConstructor
Hand::Hand(const Hand& h)
{
	deck = new Deck(*(h.deck));
	for (int i = 0; i < 6; i++)
	{
		cards[i] = deck->draw();
	}
}

Hand::~Hand() {
	deck = nullptr;
}

//Returns the cost of a card 
int Hand::getCost(int index)
{
	if (index == 0)
		return 0;
	else if (index == 1)
		return 1;
	else if (index == 2)
		return 1;
	else if (index == 3)
		return 2;
	else if (index == 4)
		return 2;
	else if (index == 5)
		return 3;
	else
		return -1;
}

//Shifts cards left with the index number
void Hand::shiftCards(int index)
{
	for (int i = index; i < 6; i++)
	{
		cards[i] = cards[i + 1];
	}
}

//choose card and get the cost

Card* Hand::exchange(int cardIndex) {

	int cost = getCost(cardIndex);

	Card* pickedCard = (cards[cardIndex]);

	shiftCards(cardIndex);

	cards[5] = deck->draw();

	return pickedCard;
}

//print the content of hand
void Hand::printHand()
{
	//get the goods for each card
	for (int i = 0; i < 6; i++)
	{	
		cout << "This is the information of hand cards: index  " << i <<" "<< cards[i]->getGood() << endl;
		cout << "Good: " << cards[i]->getGood() << endl;
		cout << "Action 1: " << cards[i]->getAction1() << " " << cards[i]->getAndOr() << " Action 2: " << cards[i]->getAction2() << endl;
		cout << "Ability: " << cards[i]->getAbility() << endl<<endl;
	}
}

// toString method
ostream& operator<<(ostream& out, const Hand& hand)
{
	cout<< "These are 6 cards in hand";
	for (int i = 0; i < 6; i++) {
		cout << hand.cards[i];
	}
	return out; 

}
Hand& Hand::operator=(const Hand& anotherHand)
{
	if (&anotherHand == this)
		return *this;
	if (anotherHand.deck)
	{
		deck = new Deck(*anotherHand.deck);
		for (int i = 0; i < 6; i++)
		{
			cards[i] = deck->draw();
		}
	}
	else
		deck = nullptr;
	return *this;
}






