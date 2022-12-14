#pragma once
#include <string>
#include <vector>
using namespace std;

class Bidding
{
private:
    string name;
    int bid;

public:
    Bidding();
    Bidding(string name, int bid);
    Bidding(const Bidding &other);
    Bidding &operator=(const Bidding &other);
    void SetBid();
    int GetBid();
    void DisplayBid();
    static string CompareBid(vector<Bidding *> bidList);
    friend ostream &operator<<(ostream &output, const Bidding &other);

    //Destructor
    ~Bidding();
};