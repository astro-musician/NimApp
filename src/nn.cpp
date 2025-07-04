# include <iostream>
# include <fstream>
# include <string>
# include "../headers/sampling.h"
# include "../headers/utils.h"
# include "../headers/nn.h"
# include <QStandardPaths>
# include <QDir>

// Neural Network

int NimNN::max_sticks = 0;
int NimNN::n_cups = 0;
float NimNN::chips[100] = {};
float NimNN::probas[100] = {};

void NimNN::init_from_scratch(){
        
    for (int i=0;i<n_cups;i++){
        init_cup(i);
    };

    compute_probas();
};

void NimNN::init_from_save(std::string filename){

    std::ifstream file;
    std::string line;
    int line_number = 0;

    file.open(filename);

    while (getline(file,line,'\n')){
        if (line_number==0){
            NimNN::n_cups = stoi(line);
        }
        else if (line_number==1){
            NimNN::max_sticks = stoi(line);
        }
        else {
            *(NimNN::chips+line_number-2) = stoi(line);
        };
        line_number += 1;
    };

    file.close();
    compute_probas();

};

void NimNN::init_cup(int i){
    for (int j=0;j<NimNN::max_sticks;j++){
        *(chips+i*NimNN::max_sticks+j) = 2;
    };
};

void NimNN::win_cup(int i, int j){
    *(NimNN::chips+i*NimNN::max_sticks+j) = *(NimNN::chips+i*NimNN::max_sticks+j) + 1;
    compute_probas();
};

void NimNN::lose_cup(int i, int j){
    *(NimNN::chips+i*NimNN::max_sticks+j) = *(NimNN::chips+i*NimNN::max_sticks+j) - 1;
    
    float n_chips = compute_n_chips(i);
    if (n_chips <= 0){
        init_cup(i);
        // std::cout << "No chips remaining in cup " << i << std::endl;
    };
    compute_probas();
};

float NimNN::compute_n_chips(int i){
    float n_chips = 0;
    
    for (int j=0;j<NimNN::max_sticks;j++){
        n_chips = n_chips + *(NimNN::chips+i*NimNN::max_sticks+j);
    };

    return n_chips;
};

void NimNN::compute_probas(){
    for (int i=0;i<NimNN::n_cups;i++){
        float n_chips = compute_n_chips(i);

        for (int j=0;j<NimNN::max_sticks;j++){
            *(NimNN::probas+i*NimNN::max_sticks+j) = *(NimNN::chips+i*NimNN::max_sticks+j)/n_chips;
        };

    };
};

void NimNN::show(){
    for (int i=0;i<NimNN::n_cups;i++){
        std::cout << "Cup " << i+1 << "\t";
        for (int j=0;j<NimNN::max_sticks;j++){
            std::cout << *(NimNN::chips+i*NimNN::max_sticks+j) << "\t";
        };
        std::cout << "\n";
    };
    std::cout << "\n";
};

int NimNN::play(int i){
    int number;
    if (i>= max_sticks) {
        number = random_number(NimNN::max_sticks,NimNN::probas+(i-1)*NimNN::max_sticks);
    }
    else {
        number = random_number(i,NimNN::probas+(i-1)*NimNN::max_sticks);
    };
    return number;
};

void NimNN::save(){

    // First line : n_cups
    // Second line : max_sticks
    // Following : flattened chips/probas array

    QString nn_filename = nn_path_qs;
    QFile nn_file(nn_filename);

    if (nn_file.open(QIODevice::WriteOnly)) {
        QTextStream out(&nn_file);
        out << NimNN::n_cups << Qt::endl;
        out << NimNN::max_sticks << Qt::endl;

        for (int i=0;i<NimNN::n_cups;i++){
            for (int j=0;j<NimNN::max_sticks;j++){
                out << *(NimNN::chips+i*NimNN::max_sticks+j) << Qt::endl;
            };
        };

        nn_file.close();
    };

    // std::string filename = "nn_saves/nn.txt";
    // std::ofstream file;
    // file.open(filename);
    
    // file << n_cups << "\n";
    // file << max_sticks << "\n";

    // for (int i=0;i<n_cups;i++){
    //     for (int j=0;j<max_sticks;j++){
    //         file << *(chips+i*max_sticks+j) << "\n";
    //     };
    // };

    // file.close();

};