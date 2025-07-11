# include <iostream>
# include "../headers/gamewindow.h"
# include "../headers/sampling.h"
# include <QApplication>
# include <QGridLayout>
# include <QPushButton>
# include <QLCDNumber>
# include <QSlider>
# include <QLabel>
# include <QFont>
# include <QCloseEvent>

QFont gamefont("Arial",20,QFont::Bold);

Nim_game gamewindow::game = {};
NimNN gamewindow::trained_NN = {};
int gamewindow::max_sticks = 0;
int gamewindow::n_cups = 0;
int gamewindow::n_played = 1;

GameWindow::GameWindow(QWidget *parent) : QMainWindow(parent) {

    this->setAttribute(::Qt::WA_DeleteOnClose);
    auto *centralWidget = new QWidget(this);
    auto *layout = new QGridLayout(centralWidget);

    sticks_number_LCD = new QLCDNumber(this);
    played_sticks_LCD = new QLCDNumber(this);
    start_button = new QPushButton(tr("Start"),this);
    play_button = new QPushButton(tr("Play"),this);
    game_state = new QLabel("",this);
    selected_sticks_slider = new QSlider(Qt::Horizontal);
    selected_sticks = new QLabel(tr("Sticks to remove"),this);

    sticks_number_LCD->setFixedSize(400,250);
    played_sticks_LCD->setFixedSize(100,100);
    selected_sticks_slider->setFixedWidth(200);
    selected_sticks_slider->setEnabled(false);

    game_state->setFont(gamefont);
    selected_sticks->setFont(gamefont);
    start_button->setFont(gamefont);
    play_button->setFont(gamefont);

    selected_sticks_slider->setMinimum(1);
    selected_sticks_slider->setTickInterval(1);
    selected_sticks_slider->setValue(gamewindow::n_played);
    selected_sticks_slider->setTickPosition(QSlider::TicksBothSides);

    layout->addWidget(sticks_number_LCD,0,0,1,2);
    layout->addWidget(start_button,2,0,1,2);
    layout->addWidget(play_button,3,0,1,2);
    layout->addWidget(game_state,1,0,1,2);
    layout->addWidget(played_sticks_LCD,4,0,1,1);
    layout->addWidget(selected_sticks_slider,4,1,1,1);
    layout->addWidget(selected_sticks,5,0,1,1);

    play_button->setEnabled(false);

    setCentralWidget(centralWidget);
    setWindowTitle(tr("Game"));

    connect(start_button,&QPushButton::clicked,this,&GameWindow::start_game);
    connect(play_button,&QPushButton::clicked,this,&GameWindow::play_turn);
    connect(selected_sticks_slider,&QSlider::valueChanged,this,&GameWindow::select_sticks_number);

};

void GameWindow::init_game() {
    trained_NN = new NimNN;
    trained_NN->init_from_save(nn_path);
    game = new Nim_game;
    game->init_game(0,trained_NN);
    gamewindow::n_cups = trained_NN->n_cups;
    gamewindow::max_sticks = trained_NN->max_sticks;
    game_state->setText(tr("NN is ready to play !"));
    selected_sticks_slider->setMaximum(gamewindow::max_sticks);
    show_sticks_left();
    played_sticks_LCD->display(gamewindow::n_played);
};

void GameWindow::select_sticks_number() {
    gamewindow::n_played = selected_sticks_slider->value();
    played_sticks_LCD->display(gamewindow::n_played);
};

void GameWindow::play_turn() {

    if ((game->state && game->check_play(gamewindow::n_played)) || !(game->state)) {
        game->play(gamewindow::n_played);
    }
    else {};

    // if (!game->mode && game->check_play(gamewindow::n_played)) {
    //     game->play(gamewindow::n_played);
    // }
    // else {};

    if (game->check_end()){

        play_button->setEnabled(false);
        selected_sticks_slider->setEnabled(false);
        if (game->state) {
            game_state->setText(tr("You lose !"));
        }
        else {
            game_state->setText(tr("You win !"));
        };
    }

    else {

        if (game->state) {
            selected_sticks_slider->setEnabled(true);
            play_button->setText(tr("Play"));
            game_state->setText(tr("Your move..."));
        }
        else {
            selected_sticks_slider->setEnabled(false);
            play_button->setText(tr("Make NN play"));
            game_state->setText(tr("NN's turn..."));
        };

    };

    show_sticks_left();
    played_sticks_LCD->display(gamewindow::n_played);

};

// void GameWindow::play_turn() {

//     if (game->state && !game->mode) {
//         game->play(gamewindow::n_played);
//         play_button->setEnabled(false);
//         show_sticks_left();
//         if (!game->check_end()) {
//             game_state->setText("NN is playing...");
//             game->play(1);
//             show_sticks_left();
//             if (!game->check_end()) {
//                 game_state->setText("Your move...");
//                 play_button->setEnabled(true);
//                 show_sticks_left();
//             }
//             else {
//                 game_state->setText("You lose !");
//                 play_button->setEnabled(false);
//             };
//         }
//         else {
//             game_state->setText("You win !");
//             play_button->setEnabled(false);
//         };
//         play_button->setEnabled(true);
//     }
//     else {};
// };

void GameWindow::start_game() {

    float starting_probas[2];
    int n_played_human=0;

    start_button->setText(tr("Reset"));
    connect(start_button,&QPushButton::clicked,this,&GameWindow::reset_game);

    *starting_probas = 0.5;
    *(starting_probas+1) = 0.5;
    game->state = random_number(2,starting_probas)-1;

    show_sticks_left();
    play_button->setEnabled(true);

    if (game->state) {
        selected_sticks_slider->setEnabled(true);
        play_button->setText(tr("Play"));
        game_state->setText(tr("Your move..."));
    }
    else {
        selected_sticks_slider->setEnabled(false);
        play_button->setText(tr("Make NN play"));
        game_state->setText(tr("NN's turn..."));
    };
};

void GameWindow::reset_game() {
    play_button->setEnabled(false);
    game->init_game(0,trained_NN);
    game_state->setText(tr("NN is ready to play !"));
    connect(start_button,&QPushButton::clicked,this,&GameWindow::start_game);
    start_button->setText(tr("Start"));
    show_sticks_left();
};

void GameWindow::show_sticks_left() {
    sticks_number_LCD->display(game->n_sticks);
};

void GameWindow::closeEvent(QCloseEvent * event) {
    emit close_game_window();
    QMainWindow::closeEvent(event);
};

void GameWindow::translateUi() {};
