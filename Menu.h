#ifndef COSC_ASS_TWO_MENU
#define COSC_ASS_TWO_MENU

#include <iostream>
#include <string>

#include "Game.h"

class Menu {

public:
    /*
    * the menu constructor which instantiates the game.
    */
    Menu();
    ~Menu();

    /*
    * Prints out the main menu and handles all user input. If the user inputs "1", the startGame method is called.
    * is called.
    * @param seed The seed the user has selected from the command line arguments.
    */
    void run(unsigned int seed);

    /*
    * Prints out the menu
    */
    void printMenu();

    /*
    * Prints out the credits.
    */
    void printCredits(); 

    /*
    * calls the startGame method on the Game object.
    * @param seed The seed the user has selected from the command line arguments.
    */
    void startGame(unsigned int seed);

    /*
    * 
    */
    void loadGame(std::string filename);

private:
    Game* game;
};

#endif