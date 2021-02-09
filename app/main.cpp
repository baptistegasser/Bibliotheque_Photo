#include "mainwindow.h"

#include "photocard.h"
#include "modification_window.h"
#include <iostream>

#include "dirindexer.h"

#include "db/db.h"

#include <QApplication>
#include <QDebug>

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
    w.showMaximized();

    /*QDir dir = QFileDialog::getExistingDirectory();
    cout << dir.path().toStdString() << endl;
    ImageFinder imgFinder (dir);
    imgFinder.index();*/



    /*Modification_window win(nullptr,&DB::getImageDao().getAll().at(0));
    win.show();*/

    /*photoCard pC;
    pC.show();*/



    return a.exec();
}
