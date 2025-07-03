# ifndef TRAIN_H
# define TRAIN_H

# include <iostream>
# include "nn.h"

namespace train{
    extern int n_games;
    extern NimNN NN;
    extern NimNN * pNN;
    extern bool winning_state;
};

void train_NN(int, int, int);

# endif

// void train_NN(int n, int p, int k){

//     train::NN.n_cups = n;
//     train::NN.max_sticks = p;
//     train::n_games = k;

//     train::NN.init_from_scratch();
//     train::pNN = &train::NN; 
//     Nim_game game;

//     for (int i=0;i<k;i++){

//         game.init_game(1,train::pNN);
//         train::winning_state = game.run();

//         if (train::winning_state){
//             for (int j=0;j<game.nn_number_of_plays;j++){
//                 train::NN.win_cup(*(game.nn_cups+j),*(game.nn_plays+j));
//             };
//         }

//         else {
//             for (int j=0;j<game.nn_number_of_plays;j++){
//                 train::NN.lose_cup(*(game.nn_cups+j),*(game.nn_plays+j));
//             };
//         };

//     };

//     train::NN.save();
//     train::NN.show();

// };