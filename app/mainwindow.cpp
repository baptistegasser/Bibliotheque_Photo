#include "mainwindow.h"
#include "photocard.h"

#include "db/db.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);
    connect(this, &QWidget::destroyed, this, &MainWindow::onClose);

    photoCard *pC = new photoCard(this);
    _my_stack->addWidget(pC);
    pC->show();
}

MainWindow::~MainWindow()
{
}

void MainWindow::onClose() {
    DB::close();
}
