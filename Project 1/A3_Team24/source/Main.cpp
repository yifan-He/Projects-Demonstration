#include "MapDriver.cpp"
#include "MapLoaderDriver.cpp"
#include "PlayerDriver.cpp"
#include "CardsDriver.cpp"
#include "BiddingDriver.cpp"
#include "GameInitializerDriver.cpp"



using namespace std;
// for vs code to run the code
//  g++ -std=c++17 *.cpp && ./a.out 


static vector<Player*> vPlayers;
static Map *map;
static int Pool = 0;


int main() {

	// Drivers for A1
	//(new MapDriver())->run();
	//(new MapLoaderDriver())->run();
	//(new CardsDriver())->run();
	//(new PlayerDriver())->run();
	//(new BiddingDriver())->run();


	//Test Drivers for A2
	//(new GameInitializerDriver())->run();    
	







	//Run the Entire Game


	srand((unsigned int)time(NULL));
	GameInitializer* gameInitializer = new GameInitializer();
	int choice = 0;
	while (true) {
		gameInitializer->show_Menu();
		cout << "\nPlease Insert your Choice!" << endl;
		cin >> choice;  //receive the choice from user
		switch (choice) {
		case 1:
			system("cls");
			gameInitializer->game_Show();
			map = gameInitializer->choose_Map();//1.CHOSE MAP 

			break;
		case 2:
			system("cls");
			gameInitializer->game_Show();
			vPlayers = gameInitializer->choose_Player();//2. get Players

			Pool = gameInitializer->pool;
			cout << Pool << endl;

			system("pause");
			break;
		case 3:
			system("cls");
			gameInitializer->game_Show();
			gameInitializer->exitSystem();// 3. EXIT THE GAME 
			break;
		default:
			cout << "Invalid Insert! Please insert the correct number." << endl;
			system("pause");
			system("cls"); //clean the console
			break;
		}
	}


	system("pause");
	return 0;
}






