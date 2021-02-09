#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "photocard.h"

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
    void constructImageList(Directory dir);
    void constructImageList(QList<Directory> dirs);
    void updateImages();
    void showModificationWindow(PhotoCard *ph);

private:
    bool isCleared;
    int width_window;
    QGridLayout *gridLayoutPage;
    QGridLayout *gridLayoutPage2;
    QScrollArea *scrollAreaPage;
    QVBoxLayout * vBoxPage;
    QWidget * scrollContent;
};
#endif // MAINWINDOW_H
