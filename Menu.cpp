#include "Menu.h"

Menu::Menu(){
    this->game = new Game();
}
Menu::~Menu(){
    delete game;
}
void Menu::run(unsigned int seed){
    std::cout<<"Welcome to Azul!"<< "\n" <<"-----------------------------------"<<std::endl;
    
    std::string input;
    std::string firstInput, secondInput;
    do{
        printMenu();
        std::cout << "> ";
        if(std::cin.good()) {
            std::cin>>input;

            if(input == "1"){
                std::cout<<std::endl;
                std::cout<<"Starting a New Game"<< "\n" <<std::endl<<std::endl;
                startGame(seed);
            }else if(input == "2"){
                std::cout << "Enter the filename to load a game" << std::endl;
                std::cout << "> ";
                std::cin >> firstInput;
                if(game != nullptr){
                    delete game;
                    this->game = new Game();
                }
                loadGame(firstInput);
            }else if(input == "3"){
                printCredits();
            }
        }
        //clear input stream before asking for input again.
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::cin.clear();
    }while(input != "4");
    
    
}

void Menu::startGame(unsigned int seed) {
    int numPlayers;
    int numFactories;

    //game->setQuit(false);

    if(this->game == nullptr) {
        this->game = new Game();
    } else {
        delete this->game;
        this->game = new Game();
    }

    std::cout << "Enter the number of players (2, 3 or 4 players): " << std::endl;
    std::cin >> numPlayers;

    //Check user input is correct
    if(std::cin.fail()) {
        std::cout << "Incorrect input entered. Please try again." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        startGame(seed);
    } else if (numPlayers < 2 || numPlayers > 4) {
        std::cout << numPlayers << " players is an invalid number of Players." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        startGame(seed);
    }

    std::cout << "Enter the number of factories you wish to use (5 or 6):" << std::endl;
    std::cin >> numFactories;

    //check user input is correct
    if(std::cin.fail()) {
        std::cout << "Incorrect input entered. Please try again." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        startGame(seed);
    } else if (numFactories < 5 || numFactories > 6) {
        std::cout << numFactories << " is an invalid number of factories." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        startGame(seed);
    }

    game->startGame(seed, numPlayers, numFactories);
}

void Menu::loadGame(std::string filename){
    game->loadGameFile(filename);
}

void Menu::printMenu(){
    std::cout<<std::endl;

    std::cout<<"Menu"<<"\n"<<"----"<<std::endl;
    std::cout<<"1. New Game" <<std::endl;
    std::cout<<"2. Load Game" <<std::endl;
    std::cout<<"3. Credits (Show student information)" <<std::endl;
    std::cout<<"4. Quit" <<std::endl;
}

void Menu::printCredits(){
    std::cout<<"-----------------------------------"<<std::endl;
    std::cout<<"Name: Marco Nadalin"<<std::endl;
    std::cout<<"Student ID: s3782230"<<std::endl;
    std::cout<<"Email: s3782230@student.rmit.edu.au"<<std::endl;
    std::cout<<std::endl;

    std::cout<<"Name: Raymond Caucci"<<std::endl;
    std::cout<<"Student ID: s3779722"<<std::endl;
    std::cout<<"Email: s3779722@student.rmit.edu.au"<<std::endl;
    std::cout<<std::endl;

    std::cout<<"Name: Anthony Ojaimi"<<std::endl;
    std::cout<<"Student ID: s3782507"<<std::endl;
    std::cout<<"Email: s3782507@student.rmit.edu.au"<<std::endl;
    std::cout<<"-----------------------------------"<<std::endl;

}