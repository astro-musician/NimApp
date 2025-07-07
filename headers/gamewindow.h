# pragma once
# include <QMainWindow>
# include "../headers/game.h"
# include "../headers/nn.h"
# include "../headers/utils.h"

# ifndef GAMEWINDOW_H
# define GAMEWINDOW_H

namespace gamewindow {
    extern Nim_game game;
    extern NimNN trained_NN;
    extern int n_cups;
    extern int max_sticks;
    extern int n_played;
};

class QPushButton;
class QLCDNumber;
class QLabel;
class QSlider;
class NimNN;
class Nim_game;

class GameWindow : public QMainWindow {
    Q_OBJECT

    public:
        GameWindow(QWidget *parent = nullptr);

    private: 
        QPushButton *play_button;
        QPushButton *start_button;
        QLCDNumber *sticks_number_LCD;
        QLCDNumber *played_sticks_LCD;
        QLabel *game_state;
        QLabel *selected_sticks;
        QSlider *selected_sticks_slider;
        NimNN *trained_NN;
        Nim_game *game;

    public slots:
        void init_game();
        void select_sticks_number();
        void play_turn();
        void start_game();
        void reset_game();
        void show_sticks_left();
        void translateUi();

    signals:
        void close_game_window();
    
    public:
        void closeEvent(QCloseEvent *event) override;

};

# endif