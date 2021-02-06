#include "mainwindow.h"
#include "photocard.h"

#include <QDebug>
#include <QScrollArea>

#include "db/db.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);
    connect(this, &QWidget::destroyed, this, &MainWindow::onClose);
    connect(_search_Text, &QLineEdit::textChanged, this, &MainWindow::showSearchMenu);

    photoCard *pC = new photoCard(this);
    _my_stack->addWidget(pC);
    pC->show();

    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

MainWindow::~MainWindow()
{
}

void MainWindow::onClose() {
    DB::close();
}

void MainWindow::showSearchMenu(QString s)
{
    //Qlist Test
    QList<Tag> listTag;
    listTag.append(Tag("Pain"));
    listTag.append(Tag("Patate"));
    listTag.append(Tag("Patate douce"));
    listTag.append(Tag("Radis"));

    QGridLayout * mobile = new QGridLayout();
    QWidget * dummy = new QWidget();
    dummy->setStyleSheet("background-color: white;border:1px solid rgb(186,186,186); border-radius: 3px; ");

    for (int i = 0; i< listTag.size(); i++) {
        QPushButton * button = new QPushButton(dummy);
        button->setText(listTag[i].value);
        button->setCheckable(true);
        button->setChecked(true);
        button->setStyleSheet("QPushButton {Text-align:left; padding: 3px; border: none} QPushButton:hover { background-color: rgb(186,186,186);border-style: inset;}");
        mobile->addWidget(button);
    }

    dummy->setLayout(mobile);

    scrollArea->setWidget(dummy);


    qDebug() << s;
}
