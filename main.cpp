#include "mainwindow.h"

#include "modification_window.h"
#include <iostream>

#include "db/dbmanager.h"

#include <QApplication>
#include <QDebug>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Feuille de style externe ajoutée à l'App
    QFile file(":/css/style.css");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    a.setStyleSheet(styleSheet);

    DBManager* manager;
    try {
        manager = new DBManager();
    }  catch (const DBManager::DBException &) {
        qCritical() << "Failed to init the database !" << manager->lastErrorMsg();
    }

    /*MainWindow w;
    w.show();*/

    Modification_window w;
    w.setImage(":/image/resources/star_fill.png");
    w.show();


    delete manager;
    return a.exec();
}
