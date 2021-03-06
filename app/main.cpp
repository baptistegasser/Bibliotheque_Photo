#include "mainwindow.h"

#include "photocard.h"
#include "modification_window.h"
#include <iostream>

#include "dirindexer.h"

#include "db/db.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>

#include "QFileDialog"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    try {
        DB::init();
    } catch (DB::DBException &e) {
        qCritical() << "Failed to init DB manager, aborting !\n" << e.what();
        exit(EXIT_FAILURE);
    }

    // Feuille de style externe ajoutée à l'App
    QFile file(":/css/style.css");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    a.setStyleSheet(styleSheet);

    // Logo
    a.setWindowIcon(QIcon(":/icon/logo"));

    MainWindow w;
    w.setGeometrySize(a.desktop()->width(), a.desktop()->height());
    w.showMaximized();

    /*Modification_window win(nullptr,&DB::getImageDao().getAll().at(0));*/

    /*photoCard pC;
    pC.show();*/

    return a.exec();
}
