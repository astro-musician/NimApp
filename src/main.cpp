# include <iostream>
# include <QApplication>
# include <QTranslator>
# include <QDir>
# include <QString>
# include <QDebug>
# include <QCoreApplication>
# include "../headers/trainwindow.h"

int main(int argc, char *argv[]) {

    std::srand(std::time(0));
    QApplication app(argc,argv);
    QTranslator translator;

    // Traductions sous Windows

    QString qmPath = QCoreApplication::applicationDirPath()+"/translations";
    qDebug() << "Chemin utilisé : " << qmPath;

    bool translator_loaded = translator.load(qmPath+"/fr.qm");
    qDebug() << "Chargement de traduction FR:" << translator_loaded;

    if (translator_loaded) {
        app.installTranslator(&translator);
    }
    else {

        // Traductions sous MacOS

        qmPath = QCoreApplication::applicationDirPath()+"/../Resources/translations";
        translator_loaded = translator.load(qmPath+"/fr.qm");

        if (translator_loaded) {
            app.installTranslator(&translator);
        }
        else {};

    };

    TrainWindow window;
    window.resize(600,500);
    window.show();
    return app.exec();
}