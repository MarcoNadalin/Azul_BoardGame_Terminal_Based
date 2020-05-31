#ifndef COSC_ASS_TWO_GAME
#define COSC_ASS_TWO_GAME

#include "Player.h"
#include "Types.h"

#include <iterator>
#include <sstream>

#include "Factory.h"

class Game{
    private:

        
        //Player* players;

        BoxLid* boxLid;
        TileBag* bag;

        
        /*
        * The numbers of players. Set to 2 by default.
        */
        int numPlayers = 2;

        /*
        * The numbers of players. Set to 5 by default.
        */
        int numFactories = 5;

        /*
        * The numbers of colours. Set to 5 by default.
        */
        int numColours = 5;


        /*
        * An array which holds all the players. (MAX 2 players since NUMPLAYERS is equal to 2 in Types.h).
        */
        std::vector<Player*> players;


        /*
        * Factory number 0 is the center of the game
        */
        std::vector<Factory*> factories;

        /*
        * If the quit command has been used, this will be set to true.
        */
        bool quit = false;
    public:

        /*
        * Initialises the TileBag and the BoxLid.
        */
        Game();
        ~Game();

        /*
        * Fills tile bag with tiles and shuffles the bag according to the seed entered.
        * Initialises the factories.
        * Prints input instructions
        * Initialises each player
        * calls match() method.
        */
        void startGame(unsigned int seed, int numPlayers, int numFactories);
        
        /*
        * Creates each factory and populates them with tiles from the tilebag.
        */
        void initFactories();

        /*
        * Used to repopulate each factory at the end of each round.
        * If there are not enough tiles within the tile bag to refil the factories,
        * tiles are moved from the boxlid to the tilebag, then the factories are repopulated.
        */
        void repopulateFactoriesAfterRound();
        
        /*
        * Called each turn for each player.
        */
        void playerTurn(Player* player);

        /*
        * Called each turn for each player.
        */
        void playerAITurn(Player* player, int* factoryId, int* row, int* colourInt);

        /*
        * 
        */
        void match();
        

        /*
        * Move selected tiles from factory to pattern line.
        * @param player The player which this method is called for.
        * @colour The colour the user has selected.
        * @factoryId The factory the user has selected to grab tiles from.
        * @row The pattern lines row the user has selected to move the tiles to.
        */
        void moveTilesFromFactoryToPlayerPatternLine(Player* player, int colour, int factoryId, int row);

        /*
        * Move all tiles from factory to centre.
        * @param factoryId The factory the user has selected to grab tiles from
        * @colour The colour the player has selected.
        */
        void moveTilesFromFactoryToCentre(int factoryId, int colour);

        /*
        * Move tiles (excet FirstPlayerToken) from floor line of player to box lid 
        * @param player The chosen player.
        */
        void moveTilesFromFloorLineToBoxLid(Player* player);

        /*
        * Moves tiles from the selected factory to the players floor line
        * @param player The player whos turn it currently is
        * @param colour the colour the player had selected
        * @param factoryId The factory the player has selected
        */
        void moveTilesFromFactoryToFloorLine(Player* player, int colour, int factoryId);

        /*
        * The while loop which handles all user input for each turn.
        * @param player the player whos turn it currently is
        * @factoryId The factory the player has selected
        * @colourInt The colour the player has selected in the form of an integer.
        * @row The patternlines row the player has selected
        */
        void userInputForPlayerTurn(Player* player, int* factoryId, int* colourInt, int* row);

        /*
        * Adds the first player token from the centre to the selected players floor line
        * @param player The player whos turn it currently is
        * @param factoryId The factory id that the player has selected.
        */
        void addFirstPlayerTokenToFloorLine(Player* player, int factoryId);

        /*
        * Checks to see if the game should end. It called before the start of each round.
        */
        bool gameEnd();

        //prints

        /*
        * Prints all the factories in a user friendly manner.
        */
        void printFactories();

        /*
        * Prints the board of a player in a user friendly manner
        * @param player The player whos board is being printed
        */
        void printBoard(Player* player);

        /*
        * Prints each board for all players. Calls the 'printBoard' method for each player.
        */
        void printBoardsForAllPlayers();
        
        /*
        * Calculates the score for each player at the end of each round, as tiles are moving
        * from the patternlines to the wall.
        */
        void scorePlayers();

        //Load/Save files
        void loadGameFile(std::string filename);
        void saveGameFile(std::string filename);

        //save player
        void savePlayer(std::ofstream& outStream, Player* player);

        //store data from file
        void loadPlayer(std::fstream& readFile, unsigned int* lineNumberPtr);
        void loadFactory(std::fstream& readFile, unsigned int* lineNumberPtr);

        //returns the next line in the text
        std::string getNextLine(std::fstream& file, unsigned int* num);

        /*
        * Checks if all factories are empty. Used to help determine the end of a round.
        */
        bool checkIfAllFactoriesEmpty();

        /*
        * Handles the moving of tiles from a players pattern line row, to a players wall.
        * @param row The specific row of a players pattern line
        * @player The selected player.
        */
        void moveTileFromPatternLineToWall(int row, Player* player);

        /*
        * Calls the 'moveTileFromPatternLineToWall' method for each pattern line row
        * @param player The selected player.
        */
        void moveAllPatternLinesPerPlayer(Player* player);

        /*
        *
        */
       void printHelp();

        /*
        * Converts a char to its corresponding colour in the form of a integer.
        * @param c 
        * @return returns the integer of the colour that the char corresponds to
        */
        int convertCharToColourInt(char c);
};

#endif
