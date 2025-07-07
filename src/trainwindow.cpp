# include <iostream>
# include "../headers/trainwindow.h"
# include "../headers/gamewindow.h"
# include <QApplication>
# include <QGridLayout>
# include <QPushButton>
# include <QSlider>
# include <QLCDNumber>
# include <QLabel>
# include <QString>
# include <QFont>
# include <QApplication>

QFont labelfont("Arial",20,QFont::Bold);

TrainWindow::TrainWindow(QWidget *parent) : QMainWindow(parent) {
    
    auto *centralWidget = new QWidget(this);
    auto *layout = new QGridLayout(centralWidget);

    total_sticks_number = 8;
    max_sticks_number = 2;
    trains_number = 10;

    total_sticks_slider = new QSlider(this);
    lcd_total_sticks = new QLCDNumber(this);
    total_sticks_label = new QLabel(tr("Total number of sticks"),this);
    max_sticks_slider = new QSlider(this);
    lcd_max_sticks = new QLCDNumber(this);
    max_sticks_label = new QLabel(tr("Maximum number of sticks"),this);
    trains_slider = new QSlider(this);
    lcd_trains = new QLCDNumber(this);
    trains_label = new QLabel(tr("Trains"),this);
    train_button = new QPushButton(tr("Train"),this);
    game_button = new QPushButton(tr("Play against NN"),this);

    total_sticks_label->setFont(labelfont);
    max_sticks_label->setFont(labelfont);
    trains_label->setFont(labelfont);

    total_sticks_slider->setTickInterval(1);
    max_sticks_slider->setTickInterval(1);
    trains_slider->setTickInterval(1);

    total_sticks_slider->setMinimum(8);
    total_sticks_slider->setMaximum(25);
    max_sticks_slider->setMinimum(2);
    max_sticks_slider->setMaximum(4);
    trains_slider->setMinimum(1);
    trains_slider->setMaximum(100);

    max_sticks_slider->setTickPosition(QSlider::TicksBothSides);

    total_sticks_slider->setValue(total_sticks_number);
    max_sticks_slider->setValue(max_sticks_number);
    trains_slider->setValue(trains_number);

    lcd_total_sticks->display(total_sticks_number);
    lcd_max_sticks->display(max_sticks_number);
    lcd_trains->display(trains_number);

    train_button->setFont(labelfont);
    game_button->setFont(labelfont);
    game_button->setEnabled(false);

    setCentralWidget(centralWidget);

    layout->addWidget(total_sticks_slider,0,0);
    layout->addWidget(lcd_total_sticks,0,1);
    layout->addWidget(total_sticks_label,0,2);
    layout->addWidget(max_sticks_slider,1,0);
    layout->addWidget(lcd_max_sticks,1,1);
    layout->addWidget(max_sticks_label,1,2);
    layout->addWidget(trains_slider,2,0);
    layout->addWidget(lcd_trains,2,1);
    layout->addWidget(trains_label,2,2);
    layout->addWidget(train_button,3,0,1,3);
    layout->addWidget(game_button,4,0,1,3);

    connect(total_sticks_slider,&QSlider::valueChanged,this,&TrainWindow::select_total_sticks_number);
    connect(max_sticks_slider,&QSlider::valueChanged,this,&TrainWindow::select_max_sticks_number);
    connect(trains_slider,&QSlider::valueChanged,this,&TrainWindow::select_trains_number);
    connect(train_button,&QPushButton::clicked,this,&TrainWindow::train);
    connect(game_button,&QPushButton::clicked,this,&TrainWindow::start_game);

};

void TrainWindow::select_total_sticks_number() {
    total_sticks_number = total_sticks_slider->value();
    lcd_total_sticks->display(total_sticks_number);
};

void TrainWindow::select_max_sticks_number() {
    max_sticks_number = max_sticks_slider->value();
    lcd_max_sticks->display(max_sticks_number);
};

void TrainWindow::select_trains_number() {
    trains_number = trains_slider->value();
    lcd_trains->display(trains_number);
};

void TrainWindow::train() {
    train_NN(total_sticks_number,max_sticks_number,trains_number);
    game_button->setEnabled(true);
};

void TrainWindow::start_game() {
    train_button->setEnabled(false);
    game_button->setEnabled(false);
    auto gamewindow = new GameWindow();
    gamewindow->init_game();
    gamewindow->resize(500,500);
    gamewindow->show();
    connect(gamewindow,&GameWindow::close_game_window,this,&TrainWindow::enable_buttons);
};

void TrainWindow::enable_buttons() {
    train_button->setEnabled(true);
    game_button->setEnabled(true);
};