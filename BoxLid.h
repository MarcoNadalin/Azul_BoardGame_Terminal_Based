#ifndef COSC_ASS_TWO_BOXLID
#define COSC_ASS_ONE_BOXLID
/*
* When the round is over, all tiles on the Floor go into the box lid. 
    When a row is completed on the PatternLines board, 1 tile goes to the corresponding
    row on the wall, the other tiles move to the box lid. Only are recycled into TileBag
    once the TileBag is completely empty.
*/
#include "Tile.h"
#include <vector>
#include "Types.h"
#include <iostream>
#include <fstream>

class BoxLid{
    public:
        /*
        * Box Lid Constructor
        */
        BoxLid();
        ~BoxLid();

        /*
        * Takes in a C style array of tile pointers. Puts 
        * all tiles within this array into the box lid tile vector
        */
        void addTiles(Tile* tile, int length);

        /*
        * Returns a c style array of tiles which returns all tiles
        */
        Tile* getTiles();

        /*
        *
        */
        bool removeTiles();

        /*
        * Returns the 'tiles' vector.
        */
        std::vector<Tile> getTileVector();

        /*
        * 
        */
        void saveBoxLid(std::ofstream& printToFile);

        /*
        * 
        */
        void loadBoxLid(std::string boxLidString);

        /*
        * Takes an integer and returns the character of its corresponding colour.
        */
        char convertIntToColourChar(int colour);

        /*
        * Takes a character and returns an int of its corresponding colour.
        */
        int convertCharToColourInt(char c);

    private:
        std::vector<Tile> tiles;
};


#endif // COSC_ASS_TWO_BOXLID