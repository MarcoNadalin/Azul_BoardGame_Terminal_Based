#include "Driver.h"

//TEST INCLUDES

/*
    BUILT COMMAND:
    g++ -Wall -Werror -std=c++14 -O -o azul Driver.cpp ADTs/BoxLid.cpp ADTs/Factory.cpp ADTs/Mosaic.cpp ADTs/Player.cpp ADTs/Tile.cpp ADTs/TileBag.cpp Game.cpp Menu.cpp
*/
int main(int argc, char *argv[]);

int main(int argc, char *argv[]){

    int unsigned seed;
    Menu* menu = new Menu();
    if(argc > 2 && std::string(argv[1]) == "-s"){
        //converts seed from ascii into int
        seed = atoi(argv[2]);
        menu->run(seed);
    } else {
        std::cout << "You entered no seed. The seed has been set to default which is 5. If you want to enter a seed, " << std::endl;
        std::cout << "run the game using this command: \"./azul -s [seed]\" " << std::endl;
        seed = 5;
        menu->run(seed);
    }
    delete menu;
    return EXIT_SUCCESS;
}