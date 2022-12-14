#include "..\header\GameObserver.h"
#include<iostream>
//Observer
//#include"..\header\GameInitializer.h"

Observer::~Observer()
{

}

Observer::Observer()
{

}

//Subject
Subject::Subject()
{
	_observers = new list<Observer*>;
}

Subject::~Subject()
{
	for (Observer* observer : *_observers)
	{
		if (observer != nullptr)
		{
			delete observer;
			observer = nullptr;
		}
	}
	delete _observers;
}

void Subject::Attach(Observer* o)
{
	_observers->push_back(o);
}

void Subject::Detach(Observer* o)
{
	_observers->remove(o);
}

void Subject::Notify()
{
	list<Observer*>::iterator i;
	for (i = _observers->begin(); i != _observers->end(); ++i)
	{
		(*i)->Update();
	}
}

//---------------------------------------Phase class
Phase::Phase(Hand* hand, Player* p,int index) {
	this->hand = hand;
	this->p = p;
	cardIndex = index;
}

Phase::~Phase() {
	delete hand;
	hand = nullptr;
	delete p;
	p = nullptr;
}

string Phase::getPlayerName() {
	return p->GetName();
}

int Phase::getCardIndex() {
	return cardIndex;
}

Card* Phase::showCard() {
	return p->GetHandCard()[p->GetHandCard().size()-1];
}//show the last drawed card 

int Phase::getCardCost() {
	return hand->getCost(cardIndex-1);
}
void Phase::playGmae() {
	//play game here
	Notify();
}
//--------------------------------------------

//--------------------viewer class
Viewer::Viewer() {

}

Viewer::Viewer(Phase* p1) {
	_subject = p1;
	_subject->Attach(this);
}

Viewer::~Viewer() {
	_subject->Detach(this);
}

void Viewer::Update() {
	display();
}

void Viewer::display() {
	string name = _subject->getPlayerName();
	int index = _subject->getCardIndex();
	Card* card = _subject->showCard();
	int cardCost = _subject->getCardCost();//the things get updated
	cout << "*************************************************************************" << endl;
	cout<< "Player : "<<  name <<"'s Phase:\nseleted the card # "<< index << "  From the left. He will pay " << cardCost <<" coins."<<endl;
	cout << "The card information is below: \n" << *card << endl;
	cout << "******************************************" << endl;
	cout << name <<" is doing actions: " << endl;
}
//-------------------------------------------------

//--------------------Controllor class
Controller::Controller(Phase *p1,Viewer* v1) {
	this->p1 = p1;
	this->v1 = v1;
}

void Controller::controll() {
	p1->playGmae();
}

//--------------------------------Game state
State::State(Hand* hand, Player* p, Map*m1) {
	this->hand = hand;
	this->p = p;
	this->m1 = m1;
	
}
State::~State() {
	delete hand;
	hand = nullptr;
	delete p;
	p = nullptr;
	delete m1;
	m1 = nullptr;
}
Player* State::getPlayer() {
	return p;
}

//Card* State::showCard() {
	//return p->GetHandCard()[p->GetHandCard().size() - 1];
//}//show the last drawed card 

void State::showState(GameInitializer* gm) {
	
	gm->doAbility(p, p->GetHandCard()[p->GetHandCard().size() - 1]);
	gm->doAction(p, p->GetHandCard()[p->GetHandCard().size() - 1]);
	Notify();
}

Map* State::getMap() {
	return m1;
}

//------------------------------

//---------------------------------stateView class
stateViewer::stateViewer() {

}

stateViewer::stateViewer(State* s1) {
	_subject = s1;
	_subject->Attach(this);
}

stateViewer::~stateViewer() {
	_subject->Detach(this);
}

void stateViewer::Update() {
	display();
}

void stateViewer::display() {
	Player* p1 = _subject->getPlayer();
	Map* m1 = _subject->getMap();
	cout << "*************************************************************************" << endl;
	cout << " This is your state: \n";
	cout << *p1;
	cout << "*************************************************************************" << endl;
	cout << " This is map state: \n";
	cout << *m1;//check
	cout << "*************************************************************************" << endl;

}

//--------------------Controllor class
stateController::stateController(State *s1, stateViewer* v1) {
	this->s1 = s1;
	this->v1 = v1;
}

void stateController::controll(GameInitializer* gm) {
	s1->showState(gm);
}