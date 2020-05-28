#include "Tile.h"
Tile::Tile(){
    //DEFAULT CONSTRUCTOR
}

Tile::Tile(int c){
    //cast integer c as a Colour. Sets colour of tile.
    this->colour = Colour(c);   
}

Tile::~Tile(){
    
}

int Tile::getColour() {
    return this->colour;
}

void Tile::setColour(int col) {
    this->colour = Colour(col);
}