#pragma once
#include <list>
#include <iostream>
#include <vector>
#include "GameInitializer.h"
class GameInitializer;

using namespace std;
//class GameInitializer;
//Observer class
class Observer
{
public:
	virtual ~Observer();
	virtual void Update() = 0;
protected:
	Observer();
};

//  subject Class
class Subject {
public:
	virtual void Attach(Observer* o);
	virtual void Detach(Observer* o);
	virtual void Notify();
	Subject();
	virtual ~Subject();
private:
	list<Observer*>* _observers;

};

//Model class
class Phase :public Subject{
public:
	Phase(Hand* hand,Player* p,int index);
	~Phase();
	string getPlayerName();
	int getCardIndex();
	Card* showCard();
	void playGmae();
	int getCardCost();
private:
	Hand * hand;
	Player * p;
	int cardIndex;
};

//view class
class Viewer :public Observer {
public:
	Viewer();
	Viewer(Phase* p);
	~Viewer();
	void Update();
	void display();
private:
	Phase *_subject;
};

class Controller {
private:
	Phase *p1;
	Viewer *v1;
public:
	Controller(Phase*p1,Viewer*v1);
	void controll();
};

//state class
class State :public Subject {
public:
	State(Hand* hand, Player* p,Map*m1);
	~State();
	Player* getPlayer();
	//Card* showCard();
	void showState(GameInitializer* gm);
	Map* getMap();
private:
	Hand * hand;
	Player * p;
	Map* m1;
	
};


//stateViewer class
class stateViewer :public Observer {
public:
	stateViewer();
	stateViewer(State* s1);
	~stateViewer();
	void Update();
	void display();
private:
	 State *_subject;
};

class stateController {
private:
	State *s1;
	stateViewer *v1;
public:
	stateController(State*s1, stateViewer*v1);
	void controll(GameInitializer* gm);
};