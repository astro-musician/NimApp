# ifndef NN_H
# define NN_H

# include <iostream>

// Neural Network

class NimNN {

    public:
        static int n_cups;
        static int max_sticks;
        static float chips[100];
        static float probas[100];
        static void init_from_save(std::string);
        static void init_from_scratch();
        static void win_cup(int,int);
        static void lose_cup(int,int);
        static void init_cup(int);
        static float compute_n_chips(int);
        static void compute_probas();
        static void show();
        static int play(int);
        static void save();

};

# endif