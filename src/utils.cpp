# include <iostream>
# include <string>
# include <QString>
# include <QStandardPaths>
# include <QDir>
# include "../headers/utils.h"

QString getAppDataPath() {
        QString appDataDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)+"/NimNN";

        QDir dir(appDataDir);
        if (!dir.exists()) {
            dir.mkpath(".");
        };

        return appDataDir;
    };

QString nn_path_qs = getAppDataPath()+"/nn.txt";
std::string nn_path = nn_path_qs.toStdString();