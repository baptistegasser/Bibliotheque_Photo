#include "mainwindow.h"

#include "db/dbmanager.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    DBManager* manager;
    try {
        manager = new DBManager();
    }  catch (const DBManager::DBException &) {
        qCritical() << "Failed to init the database !" << manager->lastErrorMsg();
    }

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
