# include <iostream>
# include "headers/nn.h"
# include "headers/game.h"
# include "headers/train.h"

using namespace std;

int main(int argc, char *argv[]){

    // Training

    std::srand(std::time(0));
    train_NN(stoi(*(argv+1)),stoi(*(argv+2)),stoi(*(argv+3)));

    // Playing

    NimNN trained_NN;
    trained_NN.init_from_save("nn_saves/nn.txt");
    Nim_game game_against_NN;
    game_against_NN.init_game(0,&trained_NN);
    bool result = game_against_NN.run();

    if (result){
        std::cout << "You win !" << std::endl;
    }
    else {
        std::cout << "You lose !" << std::endl;
    };

    return 0;
};