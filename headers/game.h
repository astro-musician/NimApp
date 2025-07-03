# ifndef GAME_H
# define GAME_H

# include <iostream>
# include "nn.h"

// GAME CLASS

namespace trainer {
    extern float probas[100];
    extern int n_played;
};

namespace nn {
    extern int n_played;
};

namespace human {
    extern int n_played;
};

class Nim_game {

    public:
        static void init_game(bool,NimNN*);
        static int player1;
        static int player2;
        static bool state; // 1 : player 1 , 0 : player 2
        static int n_sticks;
        static int max_sticks;
        static float fmax_sticks;
        static bool mode; // 0 : training, 1 : versus
        static NimNN NN;
        static int nn_plays[50];
        static int nn_cups[50];
        static int nn_number_of_plays;
        static bool check_play(int);
        static void remove_sticks(int);
        static bool check_end();
        static void play(int);
        static void human_play(int);
        static void nn_play();
        static void trainer_play(float);
        static bool run();

};

#endif