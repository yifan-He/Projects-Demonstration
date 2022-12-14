#include "../header/Map.h"
#include "../header/Cards.h"
#include "../header/Player.h"
#include <vector>
#include <iostream>

using namespace std;

class Score
{

public:

	Score();
	~Score();
	void computeScores(Player* player1, Player* player2, Map* map);

private:

	int computeScoreForRegion(Player* player);

	// victory point for continent: a player controls most part of the continent -> +1; (4 continents)
	int computeScoreForContinent(Player* player, Map* map);

	// returns the number of ancient cards in the given handcard
	int getAncientCards(vector<Card*> handCard);

	// returns the number of arcane cards in the given handcard
	int getArcaneCards(vector<Card*> handCard);

	// returns the number of forest cards in the given handcard
	int getForestCards(vector<Card*> handCard);

	// returns the number of cursed cards in the given handcard
	int getCursedCards(vector<Card*> handCard);

	// returns the number of night cards in the given handcard
	int getNightCards(vector<Card*> handCard);

	// returns the number of dire cards in the given handcard
	int getDireCards(vector<Card*> handCard);

	// returns the number of flying cards in the given handcard
	int getFlyingCards(vector<Card*> handCard);

	// returns true if the given handCard has the three noble cards, or otherwise false
	bool hasThreeNobleCards(vector<Card*> handCard);

	// returns true if the given handCard has the two mountain cards, or otherwise false
	bool hasTwoMountainCards(vector<Card*> handCard);

	// Computes the score gained by cards with abilities
	int computeScoreForCardsWithAbilities(Player* player);

	int getElixers(Player* player);

	// token: player -> territory: buildcity -> +1; isToken -> +1; comment(any of the two) 
	int computeScoreForToken(Player* player);

	// Determines the winner
	// If players are tied by VP, the player with the most coins wins. If still tied, the player 
	// with the most armies on the board wins. 
	// If still tied, the player with the most controlled territories wins.
	Player* getWinner(Player* player1, int totalScore1, Player* player2, int totalScore2);
};