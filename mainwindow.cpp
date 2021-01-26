#include "mainwindow.h"
#include "photocard.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);
    photoCard* photoCard = new class::photoCard();
    photoCard->show();
    //connect(_btn_one, &QPushButton::clicked, this, &MainWindow::test_change);
}

MainWindow::~MainWindow()
{
}

void MainWindow::test_change() {
    _my_stack->setCurrentIndex(1);
    _my_stack->removeWidget(_my_stack->currentWidget());
}
