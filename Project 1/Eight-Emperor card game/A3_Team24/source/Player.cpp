#include "..\header\Player.h"


using namespace std;

Player::Player()
{
	move = 0;
	coin = 0;
	army = 18;
	city = 3;
	name = "Player";
	bid = new Bidding();
}

Player::Player(string name,vector<Card*> handCard,Bidding* bid){
    this->move = 0;
	this->coin = 0;
	this->army = 18;
	this->city = 3;
	this->name = name;
	this->bid=bid;
    this->handCard=handCard;
}


Player::Player(string name, int coin, int move, vector<Territory*> territory, vector<Card*> handCard, Bidding* bid,string color)
{
	this->name = name;
	this->coin = coin;
	this->move = move;
	this->army = 18;
	this->city = 3;
	this->territory = territory;
	this->handCard = handCard;
	this->bid = bid;
	this->color = color;
}


Player::Player(const Player& other)
{
	this->name = other.name;
	this->coin = other.coin;
	this->move = other.move;
	this->army = other.army;
	this->city = other.city;
	for (int i = 0; i < other.handCard.size(); i++)
	{
		this->handCard[i] = new Card(*other.handCard[i]);
	}
	for (int i = 0; i < other.territory.size(); i++) 
	{
		this->territory[i] = new Territory(*other.territory[i]);
	}
	this->bid = new Bidding(*(other.bid));
}


Player& Player::operator=(const Player& other) 
{
	this->name = other.name;
	this->coin = other.coin;
	this->move = other.move;
	this->army = other.army;
	this->city = other.city;
	for (int i = 0; i < other.handCard.size(); i++) 
	{
		this->handCard[i] = new Card(*other.handCard[i]);
	}
	for (int i = 0; i < other.territory.size(); i++) 
	{
		this->territory[i] = new Territory(*other.territory[i]);
	}
	this->bid = new Bidding(*(other.bid));
	return *this;
}


Player::~Player()
{
	name = "";
	coin = 0;
	move = 0;
	army = 0;
	city = 0;

	for (int i = 0; i < handCard.size(); i++)
	{
		delete handCard.at(i);
		handCard[i] = nullptr;
	}

	for (int i = 0; i < territory.size(); i++) 
	{
		delete territory.at(i);
		territory[i] = nullptr;
	}

	territory.clear();
	handCard.clear();

	delete bid;
	bid = nullptr;
};






int Player::getArmy() {
	return this->army;
}
void Player::setArmy(int army) {
	this->army = army;
}
int Player::getCity() {
	return this->city;

}
void Player::setCity(int city) {
	this->city = city;
}

void Player::SetCoin(int coin)
{
	this->coin = coin;
}

int Player::GetCoin()
{
	return this->coin;
}

string Player::GetName()
{
	return name;
}

void Player::setVp(int i) {
	vp = i;
}
int Player::getVp() {
	return vp;
}

void Player::setName(string name) {
	this->name = name;
}
int Player::GetMove()
{
	return move;
}

void Player::setElixer(int i) {
	elixer = i;
}
int Player::getElixer() {
	return elixer;
}


string Player:: getColor(string s) {
	return this->color;
}
void Player::setcolor(string s) {
	this->color = s;
}

Bidding *Player:: getBid() {
	return this->bid;
}





vector<Territory*> Player::GetTerritorys()
{
	return territory;
}
void Player:: setTerritories(Territory* t) {
	this->territory.push_back(t);
}

vector<Card*> Player::GetHandCard()
{
	return handCard;
}

void Player::SetHandCard(Card* other)
{
	this->handCard.push_back(other);
}


void Player::PayCoin(int coin) 
{
	this->coin = this->coin - coin;
}

void Player::BuildCity(Territory* territory) 
{	
	
	if(this->city>0){
		territory->SetBuildCity();
		city = city - 1;
	}
	else {
		cout << " you have no city left on your hand." << endl;
	}//plyaers only have  3 cities
}
void Player::setIm(bool b) {
	this->immu = b;
}
bool Player::getIm() {
	return this->immu;
}

void Player::PlaceNewArmies(Territory* territory, int army) 
{
	if (this->getArmy() > 0) {
		territory->AddArmy(army);
		this->AddArmy(-army);
	}
	else {
		cout << "you have no army left to place!" << endl;
	}
		
	
}


void Player::MoveArmies(Territory* pointA, Territory* pointB, int army)
{
	if (pointB->GetPlayer().empty()) 
	{
		pointA->AddArmy(-army);
		pointB->AddArmy(army);
		pointB->SetPlayer(GetName());
		territory.push_back(pointB);
		SetMove(-army);
	}
	else if (pointB->GetPlayer().compare(GetName()) == 0) 
	{
		pointA->AddArmy(-army);
		pointB->AddArmy(army);
		SetMove(-army);
	}
	else 
	{
		cout << "Your destination has been occupied by other players." << endl;
	}
}

void Player::MoveOverLand(Territory* pointA, Territory* pointB, int army) 
{

	if (pointA->GetContinentName().compare(pointB->GetContinentName()) != 0) 
	{
		if (GetMove() > 3) 
		{
			if (pointB->GetPlayer().empty()) 
			{
				pointA->AddArmy(-army);
				pointB->AddArmy(army);
				pointB->SetPlayer(GetName());
				territory.push_back(pointB);
				SetMove(-army - 3);
			}
			else if (pointB->GetPlayer().compare(GetName()) == 0) 
			{
				pointA->AddArmy(-army);
				pointB->AddArmy(army);
				SetMove(-army - 3);
			}
			else 
			{
				cout << "Your destination has been occupied by other players." << endl;
			}
		}
		else 
		{
			cout << "You need more than three movement to cross continent." << endl;
		}
	}
	else 
	{
		cout << "You destination is in the same continent." << endl;
	}
}



void Player::DestroyArmy(Territory* territory, int num) 
{
	
	territory->AddArmy(-num);
}


void Player::AddArmy(int army)
{
	this->army += army;
}

void Player::AddTerritory(int city) {
	this->city += city;
}

void Player::SetMove(int move) 
{
	this->move = move;
}



bool Player::CheckTerritory(Territory* other) 
{
	for (int i = 0; i < territory.size(); i++) 
	{
		if (territory[i]->GetPlayer().compare(other->GetPlayer()) == 0) {
			return false;
		}
	}
	return true;
}

void Player::DisplayTerritory()
{
	for (int i = 0; i < territory.size(); i++) 
	{
		cout << *territory[i];
	}
}

ostream& operator<< (ostream& output, const Player& other) 
{
	output << "Player name: " << other.name  << " coin: " << other.coin << " army: " 
		<< other.army << " city: " << other.city << " Color: "<<other.color<<endl;
	if (other.handCard.size() != 0) 
	{
		output << "Player hand card : ";
		output << endl;
		for (int i = 0; i < other.handCard.size(); i++) 
		{
			output << i + 1;
			output << ": " << *(other.handCard[i]) << endl;
		}
	}
	if (other.territory.size() != 0) 
	{
		cout<<"" <<endl;
		output << "Player Territory : ";
		output << endl;
		for (int i = 0; i < other.territory.size(); i++) 
		{
			output << i + 1;
			output << ": " << *(other.territory[i]);
		}
		
	}
	return output;
}