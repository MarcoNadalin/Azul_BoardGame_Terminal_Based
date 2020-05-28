#include "TileBag.h"

TileBag::TileBag() {
}

TileBag::~TileBag() {
    allTiles.clear();
}

void TileBag::randomise(){
    std::shuffle(allTiles.begin(), allTiles.end(), std::default_random_engine(seed));
}

Tile* TileBag::getNextTile(){
    Tile* nextTile = &allTiles.back();
    allTiles.pop_back();
    return nextTile;
}

Tile* TileBag::getTileAtIndex(int i){
    Tile* returnTile = nullptr;
    if(i < (int)allTiles.size()) {
        returnTile = &allTiles.at(i);
    }

    return returnTile;
}

void TileBag::initialiseTileBag() {
    int numberOfTiles = 100;
    int colour = 1;
    /*
        There are 100 total tiles, and 5 types of tiles. This means there are
        20 of each tile.

        If Tile.RED = 1
        and Tile.YELLOW = 2
        and Tile.Lightblue = 3

        when i%20 = 0 (when i is a multiple of 20), we increment
        colour by 1.
        This means that, every colour is created 20 times.
    */
    for(int i = 0; i < numberOfTiles; i++) {
        //Since 0 mod anything is always 0, we need to check if the value of i is 0.
        if(i != 0 && i%(numberOfTiles/5) == 0) {
            colour++;
        }
        allTiles.insert(allTiles.begin(), Tile(colour));
    }
}

void TileBag::refilTileBag(BoxLid* boxLid) {
    std::vector<Tile> boxLidTiles = boxLid->getTileVector();

    for(unsigned int i = 0; i < boxLidTiles.size(); ++i) {
        allTiles.insert(allTiles.begin(), boxLidTiles.at(i));
    }
    randomise();

    boxLidTiles.clear();
}

int TileBag::getSize() {
    return this->allTiles.size();
}

int TileBag::getSeed(){
    return seed;
}

void TileBag::setSeed(unsigned int seed){
    this->seed = seed;
}

std::vector<Tile> TileBag::getAllTiles(){
    return this->allTiles;
}

void TileBag::saveTileBag(std::ofstream& printToFile) {
    for(int i = 0; i < getSize(); i++) {
        if(getTileAtIndex(i) != nullptr){
            int colour = allTiles.at(i).getColour();
            printToFile << convertIntToColourChar(colour); 
        }
    }
    printToFile << std::endl;
}

void TileBag::loadTileBag(std::string tileBagString){
    for(unsigned int i = 0; i < tileBagString.size(); ++i){
        char colour = tileBagString[i];
        int colourInt = convertCharToColourInt(colour);
        allTiles.insert(allTiles.begin(), Tile(colourInt));
    }
}

char TileBag::convertIntToColourChar(int colour) {
    char colourChar = '.';
    if(colour == E) {
        colourChar = '.';
    } else if(colour == B) {
        colourChar = 'B';
    } else if(colour == Y) {
        colourChar = 'Y';
    } else if(colour == R) {
        colourChar = 'R';
    } else if(colour == U) {
        colourChar = 'U';
    } else if(colour == L) {
        colourChar = 'L';
    } else if(colour == F) {
        colourChar = 'F';
    }
    return colourChar;
}

int TileBag::convertCharToColourInt(char c) {
    c = toupper(c);
    int colourInt = 0;
    if(c == '.') {
        colourInt = 0;
    } else if(c == 'B') {
        colourInt = 1;
    } else if(c == 'Y') {
        colourInt = 2;
    } else if(c == 'R') {
        colourInt = 3;
    } else if(c == 'U') {
        colourInt = 4;
    } else if(c == 'L') {
        colourInt = 5;
    } else if(c == 'F') {
        colourInt = 6;
    }
    return colourInt;
}
        