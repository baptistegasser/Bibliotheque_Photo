#include "mainwindow.h"

#include "photocard.h"
#include "modification_window.h"
#include <iostream>

#include "db/dbmanager.h"

#include <QApplication>
#include <QDebug>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    try {
        DBManager::init();
    } catch (DBManager::DBException &e) {
        qCritical() << "Failed to init DB manager, aborting !\n" << e.what();
        exit(EXIT_FAILURE);
    }

    // Feuille de style externe ajoutée à l'App
    QFile file(":/css/style.css");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    a.setStyleSheet(styleSheet);

    MainWindow w;
    w.show();

    /*Modification_window w;
    w.setImage(":/image/resources/star_fill.png");
    w.show();

    photoCard pC;
    pC.show();*/

    return a.exec();
}
