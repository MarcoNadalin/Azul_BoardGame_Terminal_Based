#ifndef COSC_ASS_TWO_TILEBAG
#define COSC_ASS_ONE_TILEBAG
//Contains all tiles and randomises them so that taking tiles out each time doesn't have to randomise
#include <vector>
#include "Tile.h"
#include "Types.h"
#include "BoxLid.h"

#include <algorithm>
#include <cstdlib>  
#include <random>
#include <iostream>
#include <fstream>

class TileBag{ 
    public: 
        TileBag();
        ~TileBag();

        //Creates all the tiles and puts them in the tile vector.
        void initialiseTileBag();

        void randomise();

        /*
        * Returns the last tile in the allTiles vector.
        * Deleted the last tile in the allTiles vector. 
        */
        Tile* getNextTile();

        /*
        * Returns tile at specified index.
        */
        Tile* getTileAtIndex(int i);

        void refilTileBag(BoxLid* boxLid);

        /*
        * Returns the amount of tiles currently in the Tile Bag.
        */
        int getSize();

        int getSeed();
        void setSeed(unsigned int seed);

        std::vector<Tile> getAllTiles();

        void saveTileBag(std::ofstream& printToFile);
        void loadTileBag(std::string tileBagString);

        char convertIntToColourChar(int colour);
        int convertCharToColourInt(char c);
        
    private: 
        int unsigned seed;
        

        //There are 100 tiles. 20 Of each colour.
        std::vector<Tile> allTiles;
};

#endif 