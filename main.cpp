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

    DBManager* manager;
    try {
        manager = new DBManager();
    }  catch (const DBManager::DBException &) {
        qCritical() << "Failed to init the database !" << manager->lastErrorMsg();
    }

    /*MainWindow w;
    w.show();*/

    Modification_window w;
    QImage img;
    if(img.load(":/image/resources/star_fill.png"))
    {
        w.setImage(img);
    }
    else
    {
         cout << "ca marche pas" << endl;
    }
    w.show();


    delete manager;
    return a.exec();
}
