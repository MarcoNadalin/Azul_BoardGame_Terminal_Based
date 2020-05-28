#include <iostream>
#include <fstream>
#include <limits>
#include "Game.h"

Game::Game(){
    bag = new TileBag();
    boxLid = new BoxLid();
}

Game::~Game(){
    delete bag;
    delete boxLid;
}

void Game::startGame(unsigned int seed, int numPlayers) {

    this->numPlayers = numPlayers;

    bag->setSeed(seed);
    bag->initialiseTileBag();
    bag->randomise();
    initFactories();
    //print instructions
    std::cout << "------------------------INPUT INSTRUCTIONS------------------------------------" << std::endl;
    std::cout << "For each turn, the expected input is: turn [number1] [character] [number2] " << std::endl;
    std::cout << "Where... " << std::endl;
    std::cout << "[number1] corresponds to: factory" << std::endl;
    std::cout << "[character] corresponds to: colour of tiles within previously selected factory" << std::endl;
    std::cout << "[number2] corresponds to: row on your pattern lines or the floor line" << std::endl << std::endl;
    std::cout << "------------------------HELP------------------------------------" << std::endl;
    std::cout << "If you need help, type 'help' as a command" << std::endl;

    //INITIALISE THE PLAYERS
    for(int i = 0; i < numPlayers; i++) {
        int x = i;
        std::string name;
        std::cout << "Enter a name for player "<< x + 1 << std::endl;
        std::cout << "> ";
        std::cin >> name;

        players.insert(players.begin(), new Player(i, name));
    }

    //Start the match
    match();    
    //end match
}

void Game::match() {
    while(!gameEnd()){
        //std::cout << "Game End: " << gameEnd() << std::endl;
        std::cout << BOLDRED << "=== " << "Start Round" << " ==="<< RESET <<std::endl;

        //check if player has 1st turn token
        int playerToGoFirst = 0;
        for(int j = 0; j < NUMPLAYERS; j++) {
            if(players.at(j)->getHasFirstPlayerToken()) {
                playerToGoFirst = j;
                players.at(j)->setHasFirstPlayerToken(false);
            }
        }

        while(!checkIfAllFactoriesEmpty() && quit == false){            
            for(int i = playerToGoFirst; i< NUMPLAYERS; ++i){
                if(!checkIfAllFactoriesEmpty() && quit == false){
                    std::string pname = players.at(i)->getName();std::cout<<std::endl;

                    std::cout<< "TURN FOR PLAYER: " << pname <<std::endl;
                    std::cout<< "Factories: "<<std::endl;
                    
                    printFactories(); std::cout<<std::endl;
                    
                    printBoardsForAllPlayers();
                    playerTurn(players.at(i));
                } 
                if(playerToGoFirst != 0) {
                    playerToGoFirst = 0;
                }                
            }
            
        }            

        if(quit == false) {
            printBoardsForAllPlayers();
            for(int i = 0; i<NUMPLAYERS; ++i){
                moveAllPatternLinesPerPlayer(players.at(i));
            }
            printBoardsForAllPlayers();

            //Move tiles from floor line (except F tile) to box lid.
            moveTilesFromFloorLineToBoxLid(players.at(0));
            moveTilesFromFloorLineToBoxLid(players.at(1));

            std::cout << BOLDRED << "=== " << "END OF ROUND" << " ==="<< RESET << std::endl;   

            //repopulate the factories after the round
            repopulateFactoriesAfterRound();
        }
        
    }
    std::cout << BOLDRED << "=== " << "END OF MATCH" << " ==="<< RESET << std::endl;
    std::cout << "Final Scores: " <<std::endl;
    for(int i = 0; i < NUMPLAYERS; ++i) {
        std::cout << players.at(i)->getName() << ": " << players.at(i)->getScore() <<std::endl;
    }
    std::cout << "Press ENTER to return to main menu" << std::endl;
}

void Game::playerTurn(Player* player) {
    int factoryId;
    int colourInt;
    int row;

    //User input
    userInputForPlayerTurn(player, &factoryId, &colourInt, &row);

    if(quit == false){
        //Checking if selected values is valid / allowed.
        int freeSpacesOnPatternLinesRow = 0;
        int numTilesOfColourInFactory = factories.at(factoryId)->getNumberTilesOfColour(colourInt);
        int colourOfTilesInRow = 0;  
        int numFreeSpacesOnFloorLine = player->getMosaic()->numberOfFreeSpacesOnFloorLine();
        bool doesSelectedRowOnWallContainColour = false;

        //If the player hasnt selected the floorLine as their 'row'
        if(row != WALLSIZE) {
            doesSelectedRowOnWallContainColour = player->getMosaic()->doesWallRowContainColour(colourInt, row);
            freeSpacesOnPatternLinesRow = player->getMosaic()->numberOfFreeSpacesOnPatternLineRow(row);
            colourOfTilesInRow = player->getMosaic()->getColourOfTilesInPatternLineRow(row);
        }  
        //If the row they selected is empty
        if(colourOfTilesInRow == 0) {
            colourOfTilesInRow = colourInt;
        }

        if((row != WALLSIZE) && freeSpacesOnPatternLinesRow > 0 
            && numTilesOfColourInFactory > 0 && colourInt == colourOfTilesInRow && doesSelectedRowOnWallContainColour == false) {
            //move selected tiles from factory to correct patternLine
            moveTilesFromFactoryToPlayerPatternLine(player, colourInt, factoryId, row);
            //if the user hasnt chosent the centre factory,
            //move left overs (if any) in factory to the centre factory
            moveTilesFromFactoryToCentre(factoryId, colourInt);
        } else if(row == WALLSIZE && numTilesOfColourInFactory > 0) {
            //Move tiles from factory to floor line if there is enough space.
            if(numFreeSpacesOnFloorLine >= numTilesOfColourInFactory) {
            moveTilesFromFactoryToFloorLine(player, colourInt, factoryId);
            moveTilesFromFactoryToCentre(factoryId, colourInt);
            } else {
               std::cout << "You are trying to add too many tiles to the floor line" << std::endl;
               playerTurn(player);
            }
        } 
        else if (freeSpacesOnPatternLinesRow == 0) {
            std::cout << "There is no space left on the pattern line row you selected." << std::endl;
            playerTurn(player);
        } else if (numTilesOfColourInFactory == 0) {
            std::cout << "You either chose a non existent factory, or the factory does not contain any of the colours you selected." << std::endl;
            playerTurn(player);
        } else if (colourInt != colourOfTilesInRow) {
            std::cout << "Each row can only contain one colour." << std::endl;
            playerTurn(player);
        } else if(doesSelectedRowOnWallContainColour == true) {
            std::cout << "The colour of tile you tried to put into row " << row << " already exists on the wall in row" << row << std::endl;
            playerTurn(player);
        }
    
    }
}

void Game::moveAllPatternLinesPerPlayer(Player* player){
    for(int row = 0; row < WALLSIZE; ++row){
            player->addScore(row);
            moveTileFromPatternLineToWall(row, player);
    }
    player->floorLineDeduct();
}

void Game::moveTileFromPatternLineToWall(int row, Player* player){
    if(player->getMosaic()->checkPatternLineFull(row)){
        int colour = player->getMosaic()->getPatternLines()[row][row].getColour();
        //FINDS THE CORRECT PLACE TO PUT THE COLOUR ON THE WALL
        int col = (colour + row - 1)%5;
        //SETS THE RESPECTIVE COLOURED TILE AS THE RIGHTMOST TILE IN THE PATTERNLINES
            
            //This was originally done by creating a new tile. This has been changed to just changing the colour of the tile
            //on the wall.
            //player->getMosaic()->getWall()[row][col] = *new Tile(player->getMosaic()->getPatternLines()[row][row].getColour());
        player->getMosaic()->getWall()[row][col].setColour(player->getMosaic()->getPatternLines()[row][row].getColour());
        //SETS THE COLOUR OF THE RIGHTMOST TILE TO EMPTY
        player->getMosaic()->getPatternLines()[row][row].setColour(E);
        //MOVES OTHER TILES TO THE BOXLID
        (*boxLid).addTiles(player->getMosaic()->getPatternLines()[row], row+1);
    }
}

void Game::moveTilesFromFactoryToPlayerPatternLine(Player* player, int colour, int factoryId, int row) {
    int freeSpacesOnPatternLinesRow = player->getMosaic()->numberOfFreeSpacesOnPatternLineRow(row);
    int numTilesOfColourInFactory = factories.at(factoryId)->getNumberTilesOfColour(colour); 
    int freeSpacesOnFloorLine = player->getMosaic()->numberOfFreeSpacesOnFloorLine();  

    int numOfTilesToBeAddedToFloorLine = numTilesOfColourInFactory - freeSpacesOnPatternLinesRow; 

    /*
    * If the factory chosen isnt the centre
    * Check if there are actually tiles within the selected factory
    * Check if there is actually free space on the patternlines row 
    * Check if there will be enough room on the floor line
    */
    if(factoryId > 0) {
        if(numTilesOfColourInFactory > 0 && freeSpacesOnPatternLinesRow > 0 && numOfTilesToBeAddedToFloorLine <= freeSpacesOnFloorLine) {
            Tile* tilesToAdd = factories.at(factoryId)->getTilesOfColour(colour);
            int tilesToAddLength = numTilesOfColourInFactory;

            for(int i = 0; i < tilesToAddLength; i++) {
                if(freeSpacesOnPatternLinesRow > 0) {
                    player->getMosaic()->addTileToPatternLines(&tilesToAdd[i], row);
                    freeSpacesOnPatternLinesRow--;
                } else {
                    //Check if there is enough space before adding it to floor line
                    player->getMosaic()->addTileToFloorLine(&tilesToAdd[i]);
                }                
            }
        }
    }

    /*
    * If the factory chosen was the centre
    */
    else if (factoryId == 0) { 
        /*
        * If centre factory is chosen,
        * check if it has first player token. If so, add it to the players floor line
        */
        addFirstPlayerTokenToFloorLine(player, factoryId);
        
        //move the tiles form the centre factory to the selected row
        for(unsigned int i = 0; i < factories.at(factoryId)->getTiles()->size(); i++) {
            int freeSpaces = player->getMosaic()->numberOfFreeSpacesOnPatternLineRow(row);
            int numOfTilesOfcolour = factories.at(0)->getNumberTilesOfColour(colour);
            
            //If there is an available free space in the patternline to put the tile, put it in the pattern line
            //else, put it on the floor line. 
            if(factories.at(factoryId)->getTiles()->get(i)->getColour() == colour) {
                if(freeSpaces > 0) {
                    player->getMosaic()->addTileToPatternLines(factories.at(factoryId)->getTiles()->get(i), row);
                    numOfTilesOfcolour--;
                } else if(player->getMosaic()->numberOfFreeSpacesOnFloorLine() > numOfTilesOfcolour) {
                    player->getMosaic()->addTileToFloorLine(factories.at(factoryId)->getTiles()->get(i));
                } else {
                    std::cout << "invalid turn. floor line does not have enough room" << std::endl;
                    playerTurn(player);
                }                
            }            
        }        
        //Remove all the tiles of colour that were taken from the centre factory
        factories.at(factoryId)->removeTilesOfColour(colour);  
    } 
    else {
        std::cout << "ERROR. Try again." << std::endl;
        playerTurn(player);
    }
}

/*
* This method assumes that there is enough space on the floor line 
* and therefore, there is no need to check for it.
*/
void Game::moveTilesFromFactoryToFloorLine(Player* player, int colour, int factoryId) {
    int numberOfTilesSelected = factories.at(factoryId)->getNumberTilesOfColour(colour);
    Tile* tilesToAdd = factories.at(factoryId)->getTilesOfColour(colour);
    for(int i = 0; i < numberOfTilesSelected; ++i) {
        player->getMosaic()->addTileToFloorLine(&tilesToAdd[i]);
    }

    /*
    * If the centre factory was chosen, remove the tiles from the centre factory.
    */
    if(factoryId == 0) {
        //Move first player token to floor line
        addFirstPlayerTokenToFloorLine(player, factoryId);
        //Remove all the tiles of colour that were taken from the centre factory
        factories.at(factoryId)->removeTilesOfColour(colour);
    }
}

void Game::moveTilesFromFactoryToCentre(int factoryId, int colour) {
    if(factoryId != 0) {
        LinkedList* leftOverTiles = factories.at(factoryId)->getTiles();
        for(unsigned int i = 0; i < factories.at(factoryId)->getTiles()->size(); ++i) {
            if(leftOverTiles->get(i) != nullptr && leftOverTiles->get(i)->getColour() != colour) {
                factories.at(0)->getTiles()->addFront(leftOverTiles->get(i)); 
            }               
        }
        leftOverTiles->clear();
    }
}

void Game::moveTilesFromFloorLineToBoxLid(Player* player) {
    Tile* floor = player->getMosaic()->getFloorLine();
    for(int i = 0; i < FLOORLINESIZE; ++i) {
        if(floor[i].getColour() != E) {
            if(floor[i].getColour() == F) {
                floor[i].setColour(E);
            } else {
                boxLid->addTiles(&floor[i], 1);
            }
        } 
    }
}

void Game::printBoard(Player* player) {
    std::cout << player->getName() << "'s BOARD: " << std::endl;
    std::cout << "------------------------------" << std::endl;
    std::cout << "Score: "<< player->getScore()<<std::endl;

    for(int i = 0; i < WALLSIZE; ++i) {
        player->getMosaic()->printPatternLineRow(i);
        std::cout << " || ";
        player->getMosaic()->printWallRow(i);
    }
    std::cout << "5: Floor Line: ";
    player->getMosaic()->printFloorLine();

    std::cout << std::endl;
}

void Game::printBoardsForAllPlayers() {
    for(int i = 0; i < NUMPLAYERS; i++) {
        printBoard(players.at(i));
    }
}

void Game::initFactories(){
    for(int i = 0; i<NUMFACTORIES; ++i){
        
        if(i == 0) {
            factories.insert(factories.end(), new Factory(i));
            factories.at(i)->populateCentreFactory(); 
        }
        else {
            factories.insert(factories.end(), new Factory(i));
            factories.at(i)->populateFactory(bag);
        }
    }
}

void Game::repopulateFactoriesAfterRound(){
    //Check if there are enough tiles in the tile bag before refilling
    if(bag->getSize() >= 25){
        for(int i = 0; i<NUMFACTORIES; ++i){
            if(i == 0){
                factories.at(i)->populateCentreFactory();
            }else{
                factories.at(i)->populateFactory(bag);
            }
        }
    // if there arent enough tiles, move tiles from boxlid back to tile bag and shuffle.
    }
    else {
        bag->refilTileBag(boxLid);
        repopulateFactoriesAfterRound();
    }    
}

bool Game::gameEnd() {
    bool endGame = false;

    for(int i = 0; i < NUMPLAYERS; ++i) {
       if(players.at(i)->getMosaic()->checkIfWallRowIsFull()) {
           endGame = true;
       }
    }  

    if(quit == true) {
        endGame = true;
    }  
    
    return endGame;
}

void Game::printFactories(){
    for(int i = 0; i<NUMFACTORIES; ++i){
        factories.at(i)->printFactory();
    }
}


void Game::userInputForPlayerTurn(Player* player, int* factoryId, int* colourInt, int* row) {
    bool invalidInput = true;   
    char colour;
    //ask for input
    while(invalidInput){
        std::cout << player->getName() << " > ";
        if(std::cin.good()) {
            std::string argument;
            std::cin >> argument;
            if(argument == "turn"){
                std::cin >> *factoryId;
                std::cin >> colour;
                *colourInt = convertCharToColourInt(colour);

                std::cin >> *row;

                /*
                * row is less than wallsize + 1 because if the player inputs a row of 7, this indicates that the tiles 
                * will go to the floor line 
                */
                if((*factoryId < NUMFACTORIES && *factoryId >= 0) && (*row <= (WALLSIZE) && *row >= 0) && *colourInt > 0 && *colourInt  < 6){
                    invalidInput = false;
                }else{
                    std::cout << "factoryID must be 0-5, row must be 0-5, colour must be 1-5" << std::endl;
                    std::cin.clear();
                }
            }
            else if (argument == "save"){
                std::string name;
                std::cin >> name;
                saveGameFile(name);
            }
            else if(argument == "quit") {
                this->quit = true;
                invalidInput = false;
                //std::cout << "Game will end in 2 turns." << std::endl;
            } if(argument == "help") {
                printHelp();
            }
            else {
                std::cout << "Invalid Input" << std::endl;
            }
        } else {
            std::cout << "The input format is [int which corresponds to desired factory] [char which corresponds to colour of tiles in factory] [int which corresponds to desired row]" << std::endl;
            std::cin.clear();
            invalidInput = false;
            userInputForPlayerTurn(player, factoryId, colourInt, row);
        }
        //clear input stream before asking for input again.
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');        
    }
}

void Game::printHelp() {
    std::cout << RED << "------------------------INPUT INSTRUCTIONS------------------------------------" << RESET << std::endl;
    std::cout << "For each turn, the expected input is: turn [number1] [character] [number2] " << std::endl;
    std::cout << "Where... " << std::endl;
    std::cout << "[number1] corresponds to: factory" << std::endl;
    std::cout << "[character] corresponds to: colour of tiles within previously selected factory" << std::endl;
    std::cout << "[number2] corresponds to: row on your pattern lines or the floor line" << std::endl << std::endl;

    std::cout << RED << "------------------------COMMANDS------------------------------------" << RESET << std::endl;
    std::cout << "1. quit" << std::endl;
    std::cout << "   Ends the current match " << std::endl << std::endl;

    std::cout << "2. turn [number1] [character] [number2]" << std::endl;
    std::cout << "   player turn to move tile(s) from factory to pattern lines. " << std::endl << std::endl;

    std::cout << "3. save [filename]" << std::endl;
    std::cout << "   save the current game to the GameFiles directory with the filename [filename]. " << std::endl << std::endl;

    std::cout << "4. help" << std::endl;
    std::cout << "   Prints the help page. " << std::endl << std::endl;

}

void Game::addFirstPlayerTokenToFloorLine(Player* player, int factoryId) {
    if(factories.at(factoryId)->getNumberTilesOfColour(F) == 1) {
        for(unsigned int i = 0; i < factories.at(factoryId)->getTiles()->size(); i++) {
            if(factories.at(factoryId)->getTiles()->get(i)->getColour() == F) {
                player->getMosaic()->addTileToFloorLine(factories.at(factoryId)->getTiles()->get(i));
                factories.at(factoryId)->getTiles()->remove(i);
            }
        }
        player->setHasFirstPlayerToken(true);
    }
}

void Game::scorePlayers(){
    for(int i = 0; i<NUMPLAYERS; ++i){
        for(int row = 0; row < WALLSIZE; ++row){
                    players.at(i)->addScore(row);
        }
    }
}

//to implement load for tiles
void Game::loadGameFile(std::string filename){
    //default file path
    std::string txtFile = "GameFiles/" + filename + ".txt";
    std::fstream readFile;

    unsigned int lineNumber = 0;
    unsigned int* lineNumberPtr = &lineNumber;

    readFile.open(txtFile);
    if(readFile.is_open()){

        //load tile bag
        std::string readTileBag = getNextLine(readFile, lineNumberPtr);
        bag->loadTileBag(readTileBag);
        

        //loads boxlid
        std::string readBoxLid = getNextLine(readFile, lineNumberPtr);
        boxLid->loadBoxLid(readBoxLid);

        //loads factories
        loadFactory(readFile, lineNumberPtr);

        //loads seed
        unsigned int seed = std::stoi(getNextLine(readFile, lineNumberPtr));
        bag->setSeed(seed);
        bag->randomise();

        //if both tilebag and box lid is empty, create 100 tiles and randomize
        if(readBoxLid == "_" && readTileBag == "_"){
            bag->initialiseTileBag();
            bag->randomise();
        }

        //load players
        loadPlayer(readFile, lineNumberPtr);

        //loads PlayerToken
        int readPlayerToken = std::stoi(getNextLine(readFile, lineNumberPtr));
        players.at(readPlayerToken)->setHasFirstPlayerToken(true);

        readFile.close();
        std::cout << "Successfully loaded the game" << std::endl;
        match();
    } else {
        std::cout << "File does not exist" << std::endl;
    }
}

void Game::saveGameFile(std::string filename){
    std::ofstream writeFile;
    std::string comment;

    //file path
    std::string txtFile = "GameFiles/" + filename + ".txt";


    //If filname is from input
    if(filename.find(".out") != std::string::npos)
        txtFile = "GameFiles/" + filename;

    //if file could not be opened, create a new file
    if (writeFile.fail()) {
    writeFile.open(txtFile, std::fstream::out);
    writeFile.close();
    }

    //opens the file and overwrites the content
    writeFile.open(txtFile);
    if (writeFile.is_open()){

        //save TileBag
        comment = "#TileBag";
        writeFile << comment << std::endl;
        if(bag->getAllTiles().empty())
            writeFile << '_' << std::endl;
        else
            bag->saveTileBag(writeFile);
        //save Box lid
        comment = "#BoxLid";
        writeFile << comment << std::endl;

        //checks if boxlid is empty
        if(boxLid->getTileVector().empty())
            writeFile << '_' << std::endl;
        else
            boxLid->saveBoxLid(writeFile);
        //saves factory
        comment = "#Factories";
        writeFile << comment << std::endl;
        for(int i = 0; i<NUMFACTORIES; ++i){
            factories.at(i)->saveFactory(writeFile);
        }

        //save seed
        comment = "#Seed";
        writeFile << comment << std::endl;        
        writeFile << bag->getSeed() << std::endl;

        //save the players and mosaic board
        int playerTokenId = 0;
        for(int i = 0; i < numPlayers; i++) {
            savePlayer(writeFile, players[i]);
            if(players.at(i)->getHasFirstPlayerToken())
                playerTokenId = i;
        }
        comment = "#Player Token";
        writeFile << comment << std::endl;        
        writeFile << playerTokenId << std::endl;

        writeFile.close();
        std::cout << "Game saved successfully" << std::endl;
    }
    else 
        std::cout << "Unable to save file" << std::endl;
}


//returns a line of the file
//need to improve on the code, since everytime the method is called, it searches through the entire file 
//Complexity: Linear
std::string Game::getNextLine(std::fstream& file, unsigned int* num){
    (*num)++;
    std::string fileLine;
    file.seekg(std::ios::beg);
    for(unsigned int i=0; i < *num - 1; ++i){
        file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
    file >> fileLine;
    if(fileLine[0] == '#' || fileLine == ""){
        fileLine = getNextLine(file, num);
    }
    return fileLine;
}


//saves player and mosaic
void Game::savePlayer(std::ofstream& outStream, Player* player){
    std::string comment;
    comment = "#Player";
    outStream << comment << std::endl;
    outStream << player->getName() <<  std::endl;
    outStream << player->getPlayerId() <<  std::endl;

    comment = "#Pattern Line";
    outStream << comment << std::endl;
    player->getMosaic()->savePatternLines(outStream);

    comment = "#Wall";
    outStream << comment << std::endl;
    player->getMosaic()->saveWall(outStream);

    comment = "#Current Score";
    outStream << comment <<  std::endl;
    outStream << player->getScore() <<  std::endl;

    comment = "#FloorLine";
    outStream << comment << std::endl;
    player->getMosaic()->saveFloorLine(outStream);
    outStream <<  std::endl;
}

//loads player and mosaic
void Game::loadPlayer(std::fstream& readFile, unsigned int* lineNumberPtr){
    for(int i = 0; i < NUMPLAYERS; i++) {
        std::string playerName = getNextLine(readFile, lineNumberPtr);
        int playerId = std::stoi(getNextLine(readFile, lineNumberPtr));
        players.insert(players.begin(), new Player(playerId, playerName));

        //loads pattern lines
        std::string patternLines[5] = {getNextLine(readFile, lineNumberPtr), getNextLine(readFile, lineNumberPtr), 
                                    getNextLine(readFile, lineNumberPtr), getNextLine(readFile, lineNumberPtr), 
                                    getNextLine(readFile, lineNumberPtr)};
        players.at(i)->getMosaic()->loadPatternLines(patternLines);

        //loads wall
        std::string wall[5] = {getNextLine(readFile, lineNumberPtr), getNextLine(readFile, lineNumberPtr), 
                            getNextLine(readFile, lineNumberPtr), getNextLine(readFile, lineNumberPtr), 
                            getNextLine(readFile, lineNumberPtr)};
        players.at(i)->getMosaic()->loadWall(wall);

        //loads player score
        int playerScore = std::stoi(getNextLine(readFile,lineNumberPtr));
        players.at(i)->setScore(playerScore);


        //loads floorline
        std::string floorLine = getNextLine(readFile, lineNumberPtr);
        players.at(i)->getMosaic()->loadFloorLine(floorLine);
    }
}

void Game::loadFactory(std::fstream& readFile, unsigned int* lineNumberPtr){
    int count = 0;
    for(int i = 0; i < NUMFACTORIES; i++) {
        std::string factoryString = getNextLine(readFile, lineNumberPtr);
        if(factoryString[2] != '_'){
            factories.insert(factories.end(), new Factory(i));
            factories.at(i)->loadFactory(factoryString);
        } else {
            ++count;
        }
    }
    if(count == 6) {
        initFactories();
        
    }
}

bool Game::checkIfAllFactoriesEmpty(){
    bool isEmpty = true;

    for(int i = 0; i < NUMFACTORIES; i++) {
        if(factories.at(i)->getTiles()->getHead() != nullptr) {
            if(factories.at(i)->getTiles()->getHead()->getValue()->getColour() == E) {
                factories.at(i)->getTiles()->clear();
            }
        }
    }

    for(int i = 0; i< NUMFACTORIES; i++){
        if(factories.at(i)->getTiles()->getHead() != nullptr){
            isEmpty = false;
        }
    }
    return isEmpty;
}

int Game::convertCharToColourInt(char c) {
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