//#pragma once
//#include <string>
//#include <iostream>
//#include <vector>
//#include <stdio.h>
//
//using namespace std;
//
//class Player;
//
//class Card
//{
//public:
//	Card();
//	Card(string name, string good, string action);
//	Card(const Card& other);
//	Card& operator = (const Card& other);
//	~Card();
//	friend ostream& operator<<(ostream& output, const Card& other);
//private:
//	string name;
//	string good;
//	string action;
//};
//
//class Deck 
//{
//public:
//	Deck();
//	Deck(const Deck& other);
//	Deck& operator = (const Deck& other);
//	~Deck();
//	friend ostream& operator<<(ostream& output, const Deck& other);
//	Card* draw();
//	vector<Card*> GetDeck();
//	void SetDeck(Card* other);
//private:
//	vector<Card*> cards;
//};
//
//class Hand 
//{
//
//public:
//	Hand();
//	Hand(const Hand& other);
//	Hand& operator = (const Hand& other);
//	~Hand();
//	friend ostream& operator<<(ostream& output, const Hand& other);
//	void exchange(int index, Player* player);
//	vector<Card*> GetHand();
//	void SetHand(Card* other);
//private:
//	vector<Card*> cards;
//};
//
//











#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>
#include <ctime>
#include<cstdlib>
#include<iterator>
#include<algorithm>
#include<numeric>
using namespace std;
struct Good
{
public:
	//2 players cards(27)	
	string PhOneElinix = "Ancient PhOneElinix";
	string Spirit = "Ancient Tree Spirit";
	string CB = "Cursed Banshee";
	string KING = "Cursed King";
	string TOWER = "Cursed Tower";
	string EYE = "Dire Eye";
	string GOB = "Dire Goblin";
	string ELF = "Forest Elf";
	string PIXIE = "Forest Pixie";
	string GRAVEYARD = "Graveyard";
	string HYDRA = "Night Hydra";
	string WIZARD = "Night Wizard";
	string KNIGHT = "Noble Knight";
	string STRONGHOLD = "Stronghold";
	string SAGE = "Ancient Sage";
	string WOODS = "Ancient Woods";
	string GAR = "Cursed Gargoyles";
	string MAUSOLEUM = "Cursed Mausoleum";
	string DRAGON = "Dire Dragon";
	string GIANT = "Dire Giant";
	string OGRE = "Dire Ogre";
	string GNOME = "Forest Gnome";
	string TOWN = "Forest Tree Town";
	string LAKE = "Lake";
	string VILLAGE = "Night Village";
	string HILLS = "Noble Hills";
	string UNICORN = "Noble Unicorn";
	//3 players cards(32)
	string MANTI = "Arcane Manticore";
	string TwoEliMPLE = "Arcane TwoElimple";
	string TREASURY = "Mountain Treasury";
	string SPHINX = "Arcane Sphinx";
	string DWARF = "Mountain Dwarf";
	//4 player cards(34)
	string CASTLE = "Castle";
	string CASTLE2 = "Castle 2";
};

struct Ability {
public:
	string Plus1Move = "+1 Move";
	string Plus1Army = "+1 Army";
	string FYLING = "Flying";
	string OneEli = "1 Elixer";
	string TwoEli = "2 Elixer";
	string ThreeEli = "3 Elixer";
	string OneEliAndTwoCoin = "1 Elixer and 2 coins";
	string Plus1VpArcaine = "+1 VP per Arcaine card";
	string Plus1VpAncient = "+1 VP per Ancient card";
	string Plus1VpFlying = "+1 VP per Flying card";
	string Plus1VpForest = "+1 VP per Forest card";
	string Plus1VpCursed = "+1 VP per Cursed card";
	string Plus1VpNight = "+1 VP per Night card";
	string All3Eli5VP = "All ThreeElie noble cards = 5 VP";
	string Win3TwoMountain = "+3 If you have 2 Mountain cards";
	string Plus1VpDire = "+1 VP per Dire card";
	string Attack = "Immune to attack";
	string Plus1TwoCoin = "+1 VP per 2 coins";
};


//card
class Card
{
public:
	//constructor
	string good;
	string action[2];
	string ability;
	string andor;
	Card();

	~Card();
	//copy constructor
	Card(const Card& c);
	Card(string good, string andor, string action, string ability);
	Card(string good, string andor ,string firstAction, string secondAction,  string ability);
	Card& operator = (const Card& c);
	string getGood();
	string getAndOr();
	string getAction1();
	string getAction2();
	string getAbility();
	void printCard();
	friend ostream& operator<<(ostream&, const Card&);
};

//deck
class Deck {
	friend ostream& operator<<(ostream&, const Deck&);
public:

	//Constructor
	Deck();//Default
	Deck(int numPlayer);
	//Copy constructor
	Deck(const Deck& d);
	//Deconstructor
	~Deck();
	void generateDeck();
	void printDeck();
	void shuffleDeck();
	Card* draw();
	Deck& operator=(const Deck&);

	static int  myRandomGenerator(int number);
	int getNumCards();
	Good gd;
	Ability abt;
	
	
private:
	int numberP;
	Card* topCard;
	Card cards[34];	
};

//hand
class Hand {
private:
	Deck* deck;
	Card* cards[6];
public:
	Hand();
	Hand(Deck* deck);
	Hand(const Hand& h);
	~Hand();
	int getCost(int indexOfcard);
	Card* exchange(int cardIndex);
	void printHand();
	void shiftCards(int index);

	friend ostream& operator<<(ostream&, const Hand&);
	Hand& operator=(const Hand&);
	
	Card* getCard(int i) { return cards[i]; };
};
