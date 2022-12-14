#include <iostream>
#include "..\header\Bidding.h"
#include <vector>

using namespace std;

class BiddingDriver
{
public:
    void run()
    {
        // test for highest coin
        Bidding *bidding1 = new Bidding("Abidding1",  50);
        Bidding *bidding2 = new Bidding("Bbidding1",  60);
        Bidding *bidding3 = new Bidding("Cbidding1", 70);
        vector<Bidding *> bids1;
        bids1.push_back(bidding1);
        bids1.push_back(bidding2);
        bids1.push_back(bidding3);

        Bidding::CompareBid(bids1);

        // test for a tie
        Bidding *bidding4 = new Bidding("Dbidding1",  70);
        Bidding *bidding5 = new Bidding("Ebidding1", 70);
        vector<Bidding *> bids2;
        bids2.push_back(bidding4);
        bids2.push_back(bidding5);

        Bidding::CompareBid(bids2);

        // test for 0 biding
        Bidding *bidding6 = new Bidding("Fbidding1",  0);
        Bidding *bidding7 = new Bidding("Gbidding1", 0);
        vector<Bidding *> bids3;
        bids3.push_back(bidding6);
        bids3.push_back(bidding7);

        Bidding::CompareBid(bids3);
    }
};