#include "Factory.h"
// LinkedList* tiles;
// If factoryId is 0, this means it's the center
// int factoryId;

Factory::Factory(int id){
    this -> tiles = new LinkedList();
    this -> factoryId = id;
}

Factory::~Factory(){
    delete tiles;  
}
// TileBag* tilebag
void Factory::populateFactory(TileBag* tilebag){
    for(int i = 0; i < FACTORYSIZE; ++i){
        tiles->addFront(tilebag->getNextTile());
    }
}

//Create the centre factory
void Factory::populateCentreFactory() {
    tiles->addFront(new Tile(F));
}

int Factory::getId(){
     return this->factoryId;
}

//Returns the number of tiles of colour in the factory
int Factory::getNumberTilesOfColour(int colour){
    int count = 0;
     for(unsigned int i = 0; i < tiles->size(); ++i){
         if(tiles->get(i)->getColour() == colour){
            ++count;
         }
     } 
     return count;
}

Tile* Factory::getTilesOfColour(int colour) {
    //Creates a tile array which has a size set to the number
    //of tiles of that colour that exist within the factory.
    Tile* tilesOfColour = new Tile[getNumberTilesOfColour(colour)];
    int index = 0;

    for(unsigned int i = 0; i < tiles->size(); ++i) {
        if(tiles->get(i)->getColour() == colour) {
            tilesOfColour[index] = *tiles->get(i);
            ++index;
        }
    }

    return tilesOfColour;
}

void Factory::removeTilesOfColour(int colour) {
    int count = getNumberTilesOfColour(colour);

    for(int i = 0; i < count; i++) {
        bool removed = false;
        for(unsigned int i = 0; i < this->tiles->size(); i++) {
            if((tiles->get(i)->getColour() == colour) && removed == false) {
                tiles->remove(i);
                removed = true;
            }
            
        }

    }

}

void Factory::printFactory(){
    std::cout << this->factoryId << ": ";
    for(unsigned int i = 0; i< tiles->size(); ++i){
        //std::cout << tiles->get(i)->getColour() << " ";
        int colour = tiles->get(i)->getColour();
        if(colour == R) {
            std::cout << RED << 'R' << RESET << " ";
        } else if(colour == Y) {
            std::cout << YELLOW << 'Y' << RESET << " ";
        } else if(colour == B) {
            std::cout << BLUE << 'B' << RESET << " ";
        } else if(colour == L) {
            std::cout << CYAN << 'L' << RESET << " ";
        } else if(colour == U) {
            std::cout << BLACK << 'U' << RESET << " ";
        } else if(colour == F) {
            std::cout << WHITE << 'F' << RESET << " ";
        }
    }
    std::cout << std::endl;
}

//Saves the tiles to the file
void Factory::saveFactory(std::ofstream& printToFile){
    for(unsigned int i = 0; i< tiles->size(); ++i){
        if(tiles->get(i) != nullptr){
            int colour = tiles->get(i)->getColour();
            printToFile << convertIntToColourChar(colour);
        }
    }
    int emptyTiles = FACTORYSIZE - tiles->size();
    if(emptyTiles == 4)
        printToFile << '_' << std::endl;
    else if(emptyTiles < 1)
        printToFile << std::endl;
    else
        printToFile << std::string(emptyTiles, '.') << std::endl;
}
//Creates tiles from the file
void Factory::loadFactory(std::string data){
    for(unsigned int i = 0; i < data.size(); ++i){
        char factoryColour = data[i];
        if(factoryColour != '.'){
            int tileColour = convertCharToColourInt(factoryColour);
            tiles->addFront(new Tile(tileColour));
        }
    }
}

LinkedList* Factory::getTiles() {
    return this->tiles;
}

char Factory::convertIntToColourChar(int colour) {
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

int Factory::convertCharToColourInt(char c) {
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

bool Factory::getIsCentre() {
    return this->isCentreFactory;
}

void Factory::setCentre(bool isCentre) {
    this->isCentreFactory = isCentre;
}