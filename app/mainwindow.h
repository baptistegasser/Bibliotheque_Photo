#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "photocard.h"
#include "db/filter.h"

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
    void setSearchKeyword();

    void sortItemChanged(int index);
    void sortOrderChanged();

private:
    bool isCleared;
    int width_window;
    QString keyword;
    Filter currentFilter;
    int orderType;
    bool orderedSort;
    QGridLayout *gridLayoutPage;
    QGridLayout *gridLayoutPage2;
    QScrollArea *scrollAreaPage;
    QVBoxLayout * vBoxPage;
    QWidget * scrollContent;
};
#endif // MAINWINDOW_H
