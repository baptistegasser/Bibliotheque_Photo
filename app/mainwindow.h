#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "photocard.h"
#include "db/imagesearch.h"
#include "modification_window.h"

#include <QMainWindow>
#include <QScrollArea>
#include "db/imagedao.h"

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected slots:
    void onClose();
    void constructSearchBar(QString s);
    void updateImages();
    void showModificationWindow(PhotoCard *ph);
    void showSelectionnedPhoto(PhotoCard *ph);
    void showImageList();
    void setSearchKeyword();

    void sortItemChanged(int index);
    void sortOrderChanged();

private:
    bool isCleared;
    int width_window;
    ImageSearch currentSearch;

    QScrollArea *scrollAreaPage;
    QVBoxLayout * vBoxPage;
    QWidget * scrollContent;
    QGridLayout *gridLayoutModification_Window;
    QStackedWidget *modification_Window_Widget;
    Modification_window *currentWin;
    PhotoCard *photoSelectionned = nullptr;
};
#endif // MAINWINDOW_H
