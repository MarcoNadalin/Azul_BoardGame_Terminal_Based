#ifndef COSC_ASS_TWO_FACTORY
#define COSC_ASS_ONE_FACTORY

#include "LinkedList.h"
#include "TileBag.h"
#include <iostream>
#include <fstream>

class Factory{
    public:
        /*
        * Constructor for Factory. 
        * @param id An integer id which sets the id for the factory.
        */
        Factory(int id);
        ~Factory();
        
        /*
        * Fills the factory with tiles taken from the tilebag.
        * @param tilebag A TileBag object where the tiles are taken from
        */
        void populateFactory(TileBag* tilebag);

        /*
        * If the factory has an ID of 0, indicating its the centre factory,
        * fill it with only 1 tile which is the First Player Token
        */
        void populateCentreFactory();

        /*
        * @return the id of the factory
        */
        int getId();
        
        /*
        * Returns the number of tiles of a specific colour within the tiles linked list
        * @param colour The colour of tiles within the linked list
        * @return the number of tiles within the linked list that has the same colour as the parameter colour.
        */
        int getNumberTilesOfColour(int colour);

        /*
        * Returns all the tiles of a specific colour in the form of a 1D array of tile pointers.
        * @param colour The colour of the tiles within the linked list.
        * @return A 1D array of tile pointers.
        */
        Tile* getTilesOfColour(int colour);

        /*
        * Removes all the tiles of a specific colour within the linked list.
        * @param colour the colour of the tiles to remove from the linked list.
        */
        void removeTilesOfColour(int colour);

        /*
        * Returns the 'tiles' object which is a linked list.
        * @return a LinkedList pointer.
        */
        LinkedList* getTiles();

        void printFactory();

        //SAVE STATE
        void saveFactory(std::ofstream& printToFile);

        //LOAD FILE STATE
        void loadFactory(std::string factoryString);
        char convertIntToColourChar(int colour);
        int convertCharToColourInt(char c);

    private:
        LinkedList* tiles;
        //If factoryId is 0, this means it's the center
        int factoryId;

};

#endif //COSC_ASS_ONE_FACTORY