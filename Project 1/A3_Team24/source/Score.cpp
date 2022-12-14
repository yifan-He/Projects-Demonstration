#include "../header/Score.h"




Score::Score() {

}
Score::~Score() {

}

// victory point for region: player has a territory -> +1;
int Score:: computeScoreForRegion(Player* player) {
    return (player -> GetTerritorys()).size();
}

// victory point for continent: a player controls most part of the continent -> +1; (4 continents)
int Score::computeScoreForContinent(Player *player, Map *map) {
    int score = 0;
    // get the four continents
	vector<Continent*> continents = map -> continents;
    vector<Territory*> territories = player -> GetTerritorys();
    for (int i = 0; i < continents.size(); i++) {
        int totalTerritories = continents[i] -> getTerritoryCount();
        string continentName = continents[i] -> GetName();
        int controlledTerritories = 0;
        for (int j = 0; j < territories.size(); j++) {
            if (continentName == territories[j] -> GetContinentName()) {
                controlledTerritories++;
            }
        }

        if (controlledTerritories * 2 > totalTerritories) {
            score++;
        }
    }
    return score;
} 

// returns the number of ancient cards in the given handcard
int Score::getAncientCards(vector<Card*> handCard) {
    int count = 0;
    for (int i = 0; i < handCard.size(); i++) {
        Card *card = handCard[i];
        if ((card -> getGood()).find("Ancient") != std::string::npos) {
            count++;
        }
    }
    return count;
}

// returns the number of arcane cards in the given handcard
int Score::getArcaneCards(vector<Card*> handCard) {
    int count = 0;
    for (int i = 0; i < handCard.size(); i++) {
        Card *card = handCard[i];
        if ((card -> getGood()).find("Arcane") != std::string::npos) {
            count++;
        }
    }
    return count;
}

// returns the number of forest cards in the given handcard
int Score::getForestCards(vector<Card*> handCard) {
    int count = 0;
    for (int i = 0; i < handCard.size(); i++) {
        Card *card = handCard[i];
        if ((card -> getGood()).find("Forest") != std::string::npos) {
            count++;
        }
    }
    return count;
}

// returns the number of cursed cards in the given handcard
int Score::getCursedCards(vector<Card*> handCard) {
    int count = 0;
    for (int i = 0; i < handCard.size(); i++) {
        Card *card = handCard[i];
        if ((card -> getGood()).find("Cursed") != std::string::npos) {
            count++;
        }
    }
    return count;
}

// returns the number of night cards in the given handcard
int Score::getNightCards(vector<Card*> handCard) {
    int count = 0;
    for (int i = 0; i < handCard.size(); i++) {
        Card *card = handCard[i];
        if ((card -> getGood()).find("Night") != std::string::npos) {
            count++;
        }
    }
    return count;
}

// returns the number of dire cards in the given handcard
int Score::getDireCards(vector<Card*> handCard) {
    int count = 0;
    for (int i = 0; i < handCard.size(); i++) {
        Card *card = handCard[i];
        if ((card -> getGood()).find("Dire") != std::string::npos) {
            count++;
        }
    }
    return count;
}

// returns the number of flying cards in the given handcard
int Score::getFlyingCards(vector<Card*> handCard) {
    int count = 0;
    for (int i = 0; i < handCard.size(); i++) {
        Card *card = handCard[i];
        if (card -> getAbility() == "Flying") {
            count++;
        }
    }
    return count;
}

// returns true if the given handCard has the three noble cards, or otherwise false
bool Score::hasThreeNobleCards(vector<Card*> handCard) {
    bool containsNobleNight = false;
    bool containsNobleHills = false;
    bool containsNobleUnicorn = false;
    for (int i = 0; i < handCard.size(); i++) {
        if (handCard[i] -> getGood() == "Noble Knight") {
            containsNobleNight = true;
        } else if (handCard[i] -> getGood() == "Noble Hills") {
            containsNobleHills = true;
        } else if (handCard[i] -> getGood() == "Noble Unicorns") {
            containsNobleUnicorn = true;
        }
    }

    return containsNobleNight && containsNobleHills && containsNobleUnicorn;
}

// returns true if the given handCard has the two mountain cards, or otherwise false
bool Score::hasTwoMountainCards(vector<Card*> handCard) {
    bool containsMountainTreasury = false;
    bool containsMountainDwarf = false;
    for (int i = 0; i < handCard.size(); i++) {
        if (handCard[i] -> getGood() == "Mountain Treasury") {
            containsMountainTreasury = true;
        } else if (handCard[i] -> getGood() == "Mountain Dwarf") {
            containsMountainDwarf = true;
        }
    }
    return containsMountainTreasury && containsMountainDwarf;
}

// Computes the score gained by cards with abilities
int Score::computeScoreForCardsWithAbilities(Player *player) {
    int score = 0;
    vector<Card*> handCard = player -> GetHandCard();
    for (int i = 0; i < handCard.size(); i++) {
        Card* card = handCard[i];
        string ability = card -> getAbility();

        if (ability == "+1 VP per Arcaine card") {
            score += getArcaneCards(handCard);
        } else if (ability == "+1 VP per Ancient card") {
            score += getAncientCards(handCard);
        } else if (ability == "+1 VP per Flying card") {
            score += getFlyingCards(handCard);
        } else if (ability == "+1 VP per Forest card") {
            score += getForestCards(handCard);
        } else if (ability == "+1 VP per Cursed card") {
            score += getCursedCards(handCard);
        } else if (ability == "+1 VP per Night card") {
            score += getNightCards(handCard);
        } else if (ability == "All ThreeElie noble cards = 5 VP") {
            if (hasThreeNobleCards(handCard)) {
                score += 5;
            }
        } else if (ability == "+3 If you have 2 Mountain cards") {
            if (hasTwoMountainCards(handCard)) {
                score += 3;
            }
        } else if (ability == "+1 VP per Dire card") {
            score += getDireCards(handCard);
        } else if (ability == "+1 VP per 2 coins") {
            int coins = player -> GetCoin();
            score += (coins / 2);
        }
    }

    return score;
} 

int Score::getElixers(Player *player) {
    vector<Card*> handCard = player -> GetHandCard();
    int elixer = 0;
    for (int i = 0; i < handCard.size(); i++) {
        Card* card = handCard[i];
        string ability = card -> getAbility();
        if (ability == "1 Elixer" || ability ==  "1 Elixer and 2 coins") {
            elixer += 1;
        } else if (ability == "2 Elixer") {
            elixer += 2;
        } else if (ability == "3 Elixer") {
            elixer += 3;
        }
    }
    return elixer;
}

// token: player -> territory: buildcity -> +1; isToken -> +1; comment(any of the two) 
int Score::computeScoreForToken(Player *player) {
    int score = 0;
    for (int i = 0; i < (player -> GetTerritorys()).size(); i++) {
        if ((player -> GetTerritorys())[0] -> GetIsToken()) {
            score++;
        }
        // if ((player -> GetTerritorys())[0] -> GetBuildCity()) {
        //     score++;
        // }
    }
    return score;
} 

// Determines the winner
// If players are tied by VP, the player with the most coins wins. If still tied, the player 
// with the most armies on the board wins. 
// If still tied, the player with the most controlled territories wins.
Player* Score::getWinner(Player *player1, int totalScore1, Player *player2, int totalScore2) {
    if (totalScore1 > totalScore2) {
        return player1;
    }

    if (totalScore2 > totalScore1) {
        return player2;
    }

    if (player1 -> GetCoin() > player2 -> GetCoin()) {
        return player1;
    }

    if (player2 -> GetCoin() > player1 -> GetCoin()) {
        return player2;
    }

    if(18- (player1 -> getArmy()) > (18- player2 -> getArmy())) {
        return player1;
    }

    if (18-(player2 -> getArmy()) > (18-player1 -> getArmy())) {
        return player2;
    }

    if ((player1 -> GetTerritorys()).size() > (player2 -> GetTerritorys()).size()) {
        return player1;
    }

    if ((player2 -> GetTerritorys()).size() > (player1 -> GetTerritorys()).size()) {
        return player2;
    }
}

// Computes and prints the score list of the given player
// Prints the winer
void Score::computeScores(Player *player1, Player *player2, Map *map) {
    vector<Player*> players;
    players.push_back(player1);
    players.push_back(player2);

	
    int totalScores[2];

    int elixers[2];

    for (int i = 0; i < players.size(); i++) {
        elixers[i] = getElixers(players[i]);
    }
	cout << "***************************Congragulations! You finished the game!***************************\n" << endl;
    for (int i = 0; i < players.size(); i++) {
        totalScores[i] = 0;
        int scoreForRegion = computeScoreForRegion(players[i]);
        int scoreForContinent = computeScoreForContinent(players[i], map);
        int scoreForCardsWithAbilities = computeScoreForCardsWithAbilities(players[i]);
        int scoreForToken = computeScoreForToken(players[i]);
        int scoreForElixers = 0;

        // assume there are two players
        if (elixers[i] > elixers[1 - i]) {
            scoreForElixers = 2;
        } else if (elixers[i] == elixers[1 - i]) {
            scoreForElixers = 1;
        }

        cout << "score list for player: " << players[i] -> GetName() << ":\n" << endl;
        cout << "score for all regions (+1 for each territory): " << scoreForRegion << "\n" << endl;
        cout << "score for controlled continents (+1 for each controlled continent): " << scoreForContinent << "\n" << endl;
        cout << "score for all cards with abilities: " << scoreForCardsWithAbilities << "\n" << endl;
        cout << "score for each territory that is token (+1 for each isTokenTerritory): " << scoreForToken << "\n" << endl;   
		cout << " Player "<<players[i]->GetName()<<" own " << getElixers(players[i]) << " Elixers! \n" << endl;
		cout << "score for elixers: " << scoreForElixers << "\n" << endl;


        totalScores[i] += scoreForRegion;
        totalScores[i] += scoreForContinent;
        totalScores[i] += scoreForCardsWithAbilities;
        totalScores[i] += scoreForToken;
        totalScores[i] += scoreForElixers;
		cout << "the coin is: " << players[i]->GetCoin() <<"\n"<< endl;
        cout << "victory points: " << totalScores[i] << "\n\n" << endl;
    }

    // Assume there are two players
    Player *winner = getWinner(players[0], totalScores[0], players[1], totalScores[1]);

    cout << "winner: " << winner -> GetName() << "\n" << endl;
}

