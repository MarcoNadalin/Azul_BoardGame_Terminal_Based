#include "BoxLid.h"

BoxLid::BoxLid() {
    
}

BoxLid::~BoxLid() {
    tiles.clear();
}

void BoxLid::addTiles(Tile* tile, int length){
    for(int i = 0; i<length; ++i){
        if(tile[i].getColour() != E){
            tiles.insert(tiles.begin(), *new Tile(tile[i].getColour()));
            tile[i].setColour(E);
        }
    }
}

Tile* BoxLid::getTiles(){
    //TODO
    return nullptr;
}

std::vector<Tile> BoxLid::BoxLid::getTileVector(){
    //TODO
    return this->tiles;
}

void BoxLid::saveBoxLid(std::ofstream& printToFile){
    std::vector<Tile> boxLidTiles = getTileVector();
    if(boxLidTiles.at(0).getColour())
        printToFile << '_';
    else {
        for(unsigned int i = 0; i < boxLidTiles.size(); ++i){
            int colour = boxLidTiles.at(i).getColour();
            printToFile << convertIntToColourChar(colour);
        }
    }
    printToFile << std::endl;
}

void BoxLid::loadBoxLid(std::string boxLidString) {
    for(unsigned int i = 0; i<boxLidString.size(); ++i){
        char colour = boxLidString[i];
        int colourInt = convertIntToColourChar(colour); 
        if(colourInt != E){
            tiles.insert(tiles.begin(), *new Tile(colourInt));
        }
    }
}

char BoxLid::convertIntToColourChar(int colour) {
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

int BoxLid::convertCharToColourInt(char c) {
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

