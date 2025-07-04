# include <iostream>
# include <random>
# include "../headers/sampling.h"

int random_number(int N_max,float * probas){

    float rand_value = (float)(rand()) / ((float)RAND_MAX);
    // std::cout << "Random value : " << rand_value << std::endl;

    int i = 1;
    float val = *probas;
    // std::cout << "Probas : " << *probas << "\t"<< *(probas+1) << "\t ..." << std::endl;
    while (val <= rand_value && i < N_max){
        val += *(probas+i);
        i += 1;
    };

    return i;

};