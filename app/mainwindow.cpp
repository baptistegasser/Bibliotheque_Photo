#include "mainwindow.h"
#include "photocard.h"

#include <QDebug>

#include "db/db.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);
    connect(this, &QWidget::destroyed, this, &MainWindow::onClose);

    photoCard *pC = new photoCard(this);
    _my_stack->addWidget(pC);
    pC->show();

    qDebug() << groupBox_2->contentsRect();
    _search_Text->setGeometry(1000,10,101,31);
}

MainWindow::~MainWindow()
{
}

void MainWindow::onClose() {
    DB::close();
}
