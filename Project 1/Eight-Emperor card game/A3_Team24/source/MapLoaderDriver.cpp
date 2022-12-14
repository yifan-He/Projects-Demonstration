#include <iostream>
#include "..\header\MapLoader.h"

using namespace std;

class MapLoaderDriver
{
    void loadFile(string file)
    {

        MapLoader *mapLoader = new MapLoader(file);

        cout << "init MapLoader with file " << mapLoader->getFileName() << endl;
        cout << "current map is " << (mapLoader->getMap() == nullptr ? "empty.\n" : "loaded!\n") << endl;

        cout << "loading file... " << endl;
        if (mapLoader->readMapFile())
        {
            cout << "map loaded successfully, map name: \n" << mapLoader->getMap()->GetName() << endl;
            mapLoader->getMap()->validate();
			cout << "current map is " << (mapLoader->getMap() == nullptr ? "empty.\n" : "loaded!\n") << endl;
        }
        else
        {
            cout << " map load failed, please make sure map file is valid" << endl;
        }
        cout << "=============================================" << endl;
    }
public:
    void run()
    {
        //loadFile("mapFiles\\map1.json");
        //loadFile("mapFiles\\map2.json");
        //loadFile("mapFiles\\map3.json");
        //loadFile("mapFiles\\map4.json");
		loadFile("mapFiles\\map5.json");
    }
};