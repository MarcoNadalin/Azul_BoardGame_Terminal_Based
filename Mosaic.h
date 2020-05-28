#ifndef COSC_ASS_TWO_MOSAIC
#define COSC_ASS_ONE_MOSAIC


#include "Tile.h"
#include "Types.h"
#include <iostream>
#include <fstream>

/*
* The board for each player. Holds the Wall, PatternLines and Floor Line.
*/
class Mosaic{
    private:
        /*
        * A c-style 2D array of Tile Pointers to represent the pattern lines.
        */
        Tile** patternLines;

        /*
        * A c-style 2D array of Tile Pointers to represent the wall.
        */
        Tile** wall;

        /*
        * A c-style 1D array of Tile Pointers to represent the floor line.
        */
        Tile* floorLine;

    public:
        Mosaic();
        ~Mosaic();
        /*
        * Initialises the Pattern Line with tiles which have the colour E (empty).
        */
        void initPatternLines();
        /*
        * Initialises the Wall with tiles which have the colour E (empty).
        */
        void initWall();
        /*
        * Initialises the floor line with thiles which have th colour E (empty).
        */
        void initFloorLine();

        //FOR PRINTING

        /*
        * Prints a wall row.
        * @param row The row to be printed.
        */
        void printWallRow(int row);

        /*
        * Prints the whole wall at once.
        */
        void printWall();        

        /*
        * Prints a pattern line row
        * @param row The row to be printed.
        */
        void printPatternLineRow(int row);

        /*
        * Prints the whole pattern line at once.
        */
        void printPatternLines();

        /*
        * Prints the floor line.
        */
        void printFloorLine();

        /*
        * Converts an int to a char 
        * @param colour The integer to be converted
        * @return returns a char whose colour corresponds to the integer passed through.
        */
        char convertIntToColourChar(int colour);   

        /*
        * Converts a char to an int 
        * @param c The char to be converted
        * @return returns an int whose colour corresponds to the char passed through.
        */ 
        int convertCharToColourInt(char c);

        /*
        * Adds a tile to the pattern lines
        * @param tile The tile to be added
        * @row the row to add it to
        */
        void addTileToPatternLines(Tile* tile, int row);

        /*
        * Returns the number of free spaces available on a pattern line row
        * @param row The specific row
        * @return The number of free spaces
        */
        int numberOfFreeSpacesOnPatternLineRow(int row);

        /*
        * Returns the colour of tiles currently in a pattern line row.
        * Each row can only have 1 colour of tiles.
        * @param row The specific row
        */
        int getColourOfTilesInPatternLineRow(int row);
        
        /*
        * Checks to see if a row on the wall has a tile of a specific colour
        * @param colour The colour to be checked
        * @row The row on the wall.
        * @return True if the wall does contain a tile of the colour passed through.
        */
        bool doesWallRowContainColour(int colour, int row);

        /*
        * Returns the number of free spaces available on the floor line
        * @return the number of free spaces.
        */
        int numberOfFreeSpacesOnFloorLine();

        /*
        * Adds a tile to the floor line.
        * @param tile The tile to be added
        */
        bool addTileToFloorLine(Tile* tile);
        
        /*
        *  Checks to see if a tile on the Wall has any tiles directly to its north, south, east and west.
        * @param row The row on the wall 
        * @param col The column on the wall
        * @return bool True if the tile has no adjacent tiles.
        */
        bool allTilesAroundTileEmpty(int row, int col);

        std::string getASCIColourFromInt(int colour);
        

        //TO SAVE GAME STATE
        void saveWall(std::ofstream& printToFile);
        void savePatternLines(std::ofstream& printToFile);
        void saveFloorLine(std::ofstream& printToFile);

        //TO IMPLEMENT LOADING GAME
        void loadPatternLines(std::string* data);
        void loadWall(std::string* data);
        void loadFloorLine(std::string data);

        //Getters and Setters
        Tile** getPatternLines();
        Tile** getWall();
        Tile* getFloorLine();
        
        /*
        * Check to see if the wall has a row that is full. Used to end the match.
        * @return True if there is a row on the wall that is full.
        */
        bool checkIfWallRowIsFull();
        
        /*
        * Checks if the specified row on the patternline is full.
        * @param row The specified row
        * @return True if the pattern line row is full.
        */
        bool checkPatternLineFull(int row);



    
        
};

#endif //COSC_ASS_TWO_MOSAIC