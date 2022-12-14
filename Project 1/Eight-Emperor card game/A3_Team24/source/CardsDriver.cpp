//#include <iostream>
//#include "..\header\Cards.h"
//
//using namespace std;
//
//class CardsDriver
//{
//    public:
//    void run()
//    {
//        Deck *deck = new Deck();
//
//        Card *card1 = new Card("card1", "good1", "action1");
//
//
//
//
//
//
//        deck->SetDeck(card1);
//
//        cout << "deck set done, total cards: " << deck->GetDeck().size() << endl;
//
//        Hand *hand = new Hand();
//        hand->SetHand(deck->draw());
//        cout << "deck draw, total cards:" << deck->GetDeck().size() << endl;
//        cout << "hand setup done, total cards:" << hand->GetHand().size() << endl;
//    }
//};
//
//
//



#include <iostream>
#include "..\header\Cards.h"
using namespace std;


class CardsDriver
{
public:
	void run()
	{


		Deck* deck = new Deck(2);

		// print cards information
		deck->generateDeck();
		cout << "Deck Object\n" << endl;
		deck->printDeck();

		deck->shuffleDeck();
		deck->printDeck();
		cout << "Hand card information\n" << endl;
		Hand* hand = new Hand(deck);
		int index = 0;

		hand->printHand();
		cout << "Choose an index number \n";
		cin >> index;
		cout << "After exchange: \n" << endl;
		hand->exchange(index);
		hand->printHand();
	}
};


