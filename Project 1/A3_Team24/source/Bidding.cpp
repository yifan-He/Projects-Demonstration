#include "..\header\Bidding.h"
#include <iostream>
#include <string>
using namespace std;

Bidding::Bidding()
{
}

Bidding::Bidding(string name, int bid)
{
	this->name = name;

	this->bid = bid;
}


Bidding::Bidding(const Bidding &other)
{
     this->name = other.name;
	 this->bid = other.bid;
}

Bidding &Bidding::operator=(const Bidding &other)
{
    if (&other == this)
        return *this;
	 this->name = other.name;
   
	 this->bid = other.bid;
    return *this;
}

ostream &operator<<(ostream &output, const Bidding &bid)
{
    output << "Name: " << bid.name << " Bid: " << bid.bid<< endl;
    return output;
}

void Bidding::SetBid()
{
    cout << "Enter the amount you wanna bid: ";
    cin >> bid;
    while (bid < 0)
    {
        cout << "You can't bid less than 0";
        cin.clear();
        cin >> bid;
    }
}

int Bidding::GetBid()
{
    return bid;
}

string Bidding::CompareBid(vector<Bidding *> bidList)
{
    int max = 0;
    string maxName = bidList[0]->name;
    size_t len = sizeof(bidList) / sizeof(bidList[0]);
    bool beSame = false;

    for (size_t i = 0; i < bidList.size(); i++)
    {
        cout << bidList[i]->name << " has bid " << bidList[i]->bid << endl;
        if (bidList[i]->bid > max)
        {
            max = bidList[i]->bid;
            maxName =bidList[i]->name;
        }
    }

    for (int i = 0; i < bidList.size(); i++)
    {

        if ((bidList[i]->bid) == max && (bidList[i]->name).compare(maxName) < 0)
        {
            maxName = (bidList[i]->name);
            beSame = true;
        }
    }
    if (max == 0)
        cout << "\nThe bid of all player are 0 so " << maxName << " will go first in alphabetical order " << endl;
    else
    {
		if (beSame)
			cout << "\nTwo or more players have the same bid but " << maxName << " will go first in alphabetical order \n" << endl;
		else
			cout << "\n"
			<< maxName << " will go first due to highest bid( * " << max << " * )\n" << endl;
    }
	return maxName;
}



Bidding::~Bidding()
{
    
}