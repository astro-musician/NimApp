# include <iostream>
# include "headers/nn.h"
# include "headers/sampling.h"
# include "headers/utils.h"
# include "headers/game.h"

// GAME CLASS

float trainer::probas[100] = {};
int trainer::n_played = 0;
int nn::n_played = 0;
int human::n_played = 0;


int Nim_game::player1 = 0;
int Nim_game::player2 = 0;
bool Nim_game::state = 0; // 1 : player 1 , 0 : player 2
int Nim_game::n_sticks = 0;
int Nim_game::max_sticks = 0;
float Nim_game::fmax_sticks = 0;
bool Nim_game::mode = 0; // 0 : training, 1 : versus
NimNN Nim_game::NN = {};
int Nim_game::nn_plays[50] = {};
int Nim_game::nn_cups[50] = {};
int Nim_game::nn_number_of_plays = 0;

void Nim_game::init_game(bool m, NimNN * pNN = 0){

    mode = m;
    nn_number_of_plays = 0;
        if (mode){
            NN = *pNN;
            // NN.show();
            n_sticks = NN.n_cups;
            max_sticks = NN.max_sticks;
            fmax_sticks = NN.max_sticks;
            player1 = 1; // NN
            player2 = 2; // trainer
            // std::cout << "Training mode" << std::endl;
        }

        else {
            NN.init_from_save(nn_path);
            NN.show();
            n_sticks = NN.n_cups;
            max_sticks = NN.max_sticks;
            fmax_sticks = NN.max_sticks;
            player1 = 0; // human
            player2 = 1; // NN (trained)
            std::cout << "Versus mode" << std::endl;
        };

};

bool Nim_game::check_play(int n){

    bool check;
    if (n>=1 && n<=max_sticks && n<=n_sticks){
        check = 1;
    }

    else {
        check = 0;
    };

    return check;
};

void Nim_game::remove_sticks(int n){

    if (check_play(n)){
        n_sticks -= n;
    };
};

bool Nim_game::check_end(){

    bool check;

    if (n_sticks==0){
        check = 1;
    }
    else {
        check = 0;
    };

    return check;
};

void Nim_game::human_play(int n){

    if (check_play(n)){
        remove_sticks(n);
    }
    else {};

};

void Nim_game::nn_play(){
    
    nn::n_played = NN.play(n_sticks);
    
    while (!check_play(nn::n_played)){
        nn::n_played = NN.play(n_sticks);
    };

    // std::cout << "NN played " << nn::n_played << " at cup " << n_sticks << std::endl;

    *(nn_cups+nn_number_of_plays) = n_sticks-1;
    *(nn_plays+nn_number_of_plays) = nn::n_played-1;
    nn_number_of_plays += 1;

    remove_sticks(nn::n_played);

};

void Nim_game::trainer_play(float success_prob = 0.9){

    if (n_sticks%(max_sticks+1)==0){
        for (int i=0;i<max_sticks;i++){
            *(trainer::probas+i) = 1/fmax_sticks;
        };
    }

    else {
        for (int i=0;i<max_sticks;i++){
            *(trainer::probas+i) = (1.0-success_prob)/(fmax_sticks-1.0);
        };
        *(trainer::probas+n_sticks%(max_sticks+1)-1) = success_prob;
    };

    trainer::n_played = random_number(max_sticks,trainer::probas);

    while (!check_play(trainer::n_played)){
        trainer::n_played = random_number(max_sticks,trainer::probas);
    };

    remove_sticks(trainer::n_played);

};

void Nim_game::play(int n_played_human=1){

    // std::cout << "Remaining sticks : " << n_sticks << std::endl;

    if (state){

        if (!mode){
            std::cout << "Human" << std::endl;
        };

        if (player1==0){
            human_play(n_played_human);
        }
        else if (player1==1){
            nn_play();
        }
        else if (player1==2){
            trainer_play();
        };
    }

    else {

        if (!mode){
            std::cout << "NN" << std::endl;
        };

        if (player2==0){
            human_play(n_played_human);
        }
        else if (player2==1){
            nn_play();
        }
        else if (player2==2){
            trainer_play();
        };
    };

    state = !state;

};

bool Nim_game::run(){

    float starting_probas[2];
    int n_played_human=0;

    *starting_probas = 0.5;
    *(starting_probas+1) = 0.5;
    state = random_number(2,starting_probas)-1;

    while (!check_end()){

        // Cas particulier : intervention d'un joueur humain
        if (state && !mode){
            std::cout << "Remaining sticks : " << n_sticks << std::endl;
            std::cin >> n_played_human;
            while (!check_play(n_played_human)){
                std::cout << "Not possible to play " << n_played_human << std::endl;
                std::cin >> n_played_human;
            };
            play(n_played_human);
        } 
        // Autres cas (NN ou trainer)
        else {
            play();
        };
    };

    // Sur interface graphique, remplacer la boucle while par l'exécution de son contenu
    // avec un bouton PLAY. Il faut aussi que le NN joue à la suite du joueur, et instantanément
    // s'il commmence la partie :

    // Sélecteur de nombre n_played_human
    // check_play() conditionne l'utilisation du bouton Play (le griser si possible)
    // Le bouton Play exécute : "play(n_played_human); play();" pour faire jouer tour à tour l'humain et le NN.

    return !state;

};