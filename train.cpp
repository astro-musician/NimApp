# include <iostream>
# include "headers/nn.h"
# include "headers/game.h"
# include "headers/train.h"

// namespace train{
//     int n_games;
//     NimNN NN;
//     NimNN * pNN;
//     bool winning_state;
// };

int train::n_games = 0;
NimNN train::NN = {};
NimNN * train::pNN = {};
bool train::winning_state = 0;

void train_NN(int n, int p, int k){

    train::NN.n_cups = n;
    train::NN.max_sticks = p;
    train::n_games = k;

    train::NN.init_from_scratch();
    train::pNN = &train::NN; 
    Nim_game game;

    for (int i=0;i<k;i++){

        game.init_game(1,train::pNN);
        train::winning_state = game.run();

        if (train::winning_state){
            for (int j=0;j<game.nn_number_of_plays;j++){
                train::NN.win_cup(*(game.nn_cups+j),*(game.nn_plays+j));
            };
        }

        else {
            for (int j=0;j<game.nn_number_of_plays;j++){
                train::NN.lose_cup(*(game.nn_cups+j),*(game.nn_plays+j));
            };
        };

    };

    train::NN.save();
    train::NN.show();

};