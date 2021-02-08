#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

#include <QMainWindow>
#include <QScrollArea>

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected slots:
    void onClose();
    void constructSearchBar(QString s);
    void chooseFolder();
    void addFolder(const QString path);
    void constructImageList(Directory dir);
    void constructImageList(QList<Directory> dirs);

private:
    bool isCleared;
    QGridLayout *gridLayoutPage;
    QScrollArea *scrollAreaPage;
    QVBoxLayout * vBoxPage;
    QWidget * scrollContent;
};
#endif // MAINWINDOW_H
