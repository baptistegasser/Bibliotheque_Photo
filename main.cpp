#include "mainwindow.h"

#include "db/dbmanager.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DBManager* manager;
    try {
        manager = new DBManager();
    }  catch (const DBManager::DBException &) {
        qCritical() << "Failed to init the database !" << manager->lastErrorMsg();
    }

    MainWindow w;
    w.show();

    delete manager;
    return a.exec();
}
