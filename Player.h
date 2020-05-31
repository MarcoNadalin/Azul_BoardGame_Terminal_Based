#ifndef COSC_ASS_TWO_PLAYER
#define COSC_ASS_TWO_PLAYER
#include <string>
#include "Mosaic.h"

class Player{

    public:
        /*
        * The player constructor
        * @param playerId The id for the player
        * @param std::string playerName The name of the player.
        */
        Player(int playerId, std::string playerName);
        ~Player();

        int getPlayerId();    
        
        int getScore();
        void addScore(int row);
        void setScore(int playerScore);
        void floorLineDeduct();

        void setHasFirstPlayerToken(bool hasToken);
        bool getHasFirstPlayerToken();
        void checkDirectionsAndAdd(int row, int col);

        bool isAI();
        void setAI(bool ai);
        std::string getName();
        Mosaic* getMosaic();
        
    private:
        int playerId;
        int score;
        std::string playerName;
        Mosaic* mosaic;
        bool hasFirstPlayerToken = false;
        bool AI = false;
        
};

#endif