#include "Player.h"

Player::Player(int playerId, std::string playerName){
    //TODO
    this->playerId = playerId;
    this->playerName = playerName;
    this->score = 0;
    mosaic = new Mosaic();
}

Player::~Player(){
    delete mosaic;
}

int Player::getPlayerId(){
    return playerId;
}    

int Player::getScore(){
    return score;
}

void Player::setScore(int playerScore){
    this->score = playerScore;
}

void Player::addScore(int row){
    
    if(this->getMosaic()->checkPatternLineFull(row)){
        int colour = this->getMosaic()->getPatternLines()[row][row].getColour();
        //column of tile to be added
        int col = (colour + row - 1)%5;
        
        //std::cout << this->getMosaic()->allTilesAroundTileEmpty(row, col) << std::endl;
        if(this->getMosaic()->allTilesAroundTileEmpty(row, col)){
            score++;
        }else{
            checkDirectionsAndAdd(row, col);
        }
    }

}

void Player::setHasFirstPlayerToken(bool hasToken) {
    this->hasFirstPlayerToken = hasToken;
}

bool Player::getHasFirstPlayerToken() {
    return this->hasFirstPlayerToken;
}

void Player::floorLineDeduct(){
    int arr[7] = {-1, -1, -2, -2, -2, -3, -3};
    for(int i = 0; i < FLOORLINESIZE; ++i){
        if(this->getMosaic()->getFloorLine()[i].getColour() != E){
            if(score + arr[i] >= 0){
                score = score + arr[i];
            }else{
                score = 0;
            }
            
        }
    }
}

std::string Player::getName(){
    return playerName;
}

Mosaic* Player::getMosaic(){
    //TODO
    return (*this).mosaic;
}

void Player::checkDirectionsAndAdd(int row, int col){
    bool checkedHorizontal = true;
    score++;

    //check for any adjacent tiles right
    int rightcheckCol = col;
    bool endOfRight = false;
    while(rightcheckCol < WALLSIZE-1){
        if(this->getMosaic()->getWall()[row][rightcheckCol+1].getColour() != E && endOfRight == false){
            score++; 
            rightcheckCol++;
            checkedHorizontal = true;
        }else{
            endOfRight = true;
            rightcheckCol++;
        }
    }
   
    //check for any adjacent tiles left
    int leftcheckCol = col;
    bool endOfLeft = false;
    while(leftcheckCol > 0){
        //std::cout << playerName << ":" << " " << row << " " << leftcheckCol << std::endl;
        if(this->getMosaic()->getWall()[row][leftcheckCol-1].getColour() != E && endOfLeft == false){
            score ++; 
            leftcheckCol--;
            checkedHorizontal = true;
        }else{
            endOfLeft = true;
            leftcheckCol--;
        }
    }

    /*if there are both tiles in the column and the row, we need to increment
    *the score again since scoring counts the new tile again per horizontal/vertical check
    */
    if(checkedHorizontal == true){
        score++;
    }

    // //check for any adjacent tiles upwards
    int upcheckRow = row;
    bool endOfUp = false;
    while(upcheckRow > 0){
        if(this->getMosaic()->getWall()[upcheckRow -1][col].getColour() != E && endOfUp == false){
            score++;
            upcheckRow--;
        }else{
            endOfUp = true;
            upcheckRow--;
        }
    }
    
    //check for any adjacent  tiles downwards
    int downcheckRow = row;
    bool endOfDown = false;
    while(downcheckRow < WALLSIZE-1){
        if(this->getMosaic()->getWall()[downcheckRow + 1][col].getColour() != E && endOfDown == false){
            score++;
            downcheckRow++;
        }else{
            endOfDown = true;
            downcheckRow++;
        }
        
    }
        
}
