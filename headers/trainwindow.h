# pragma once
# include <QMainWindow>
# include "../headers/train.h"
# include "../headers/nn.h"

# ifndef TRAINWINDOW_H
# define TRAINWINDOW_H

class QPushButton;
class QLCDNumber;
class QLabel;
class QSlider;
class QLCDNumber;
class QString;
class GameWindow;

class TrainWindow : public QMainWindow {
    Q_OBJECT

    public:
        TrainWindow(QWidget *parent = nullptr);
        int trains_number;
        int total_sticks_number;
        int max_sticks_number;

    private: 
        QPushButton *train_button;
        QPushButton *game_button;
        QSlider *total_sticks_slider;
        QSlider *trains_slider;
        QSlider *max_sticks_slider;
        QLCDNumber *lcd_total_sticks;
        QLCDNumber *lcd_max_sticks;
        QLCDNumber *lcd_trains;
        QLabel *total_sticks_label;
        QLabel *max_sticks_label;
        QLabel *trains_label;
        QString *total_sticks_string;

    private slots:
        void select_total_sticks_number();
        void select_max_sticks_number();
        void select_trains_number();
        void train();
        void start_game();

    public slots:
        void enable_buttons();
        void translateUi();

};

# endif