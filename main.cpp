# include <iostream>
# include <QApplication>
# include "gui/trainwindow.h"

int main(int argc, char *argv[]) {
    std::srand(std::time(0));
    QApplication app(argc,argv);
    TrainWindow window;
    window.resize(500,500);
    window.show();
    return app.exec();
}