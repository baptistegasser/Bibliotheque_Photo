#include "mainwindow.h"
#include "photocard.h"

#include <QDebug>
#include <QScrollArea>
#include <QLabel>

#include "db/db.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);
    connect(this, &QWidget::destroyed, this, &MainWindow::onClose);
    connect(_search_comboBox, &QComboBox::currentTextChanged, this, &MainWindow::constructSearchBar);

    isCleared = false;

    Image *image = new Image(":/image/resources/example.jpg");
    photoCard *pC = new photoCard(this);
    pC->setImage(image);
    _my_stack->addWidget(pC);
    pC->show();
}

MainWindow::~MainWindow()
{
}

void MainWindow::onClose() {
    DB::close();
}

void MainWindow::constructSearchBar(QString s)
{
    if (!isCleared) {
        isCleared = true;
        _search_comboBox->clear();

        QList<Tag> all = DB::getTagDao().search(s);

        for (int i = 0; i< all.size(); i++) {
            _search_comboBox->addItem(all[i].value);
        }
         _search_comboBox->setCurrentText(s);
        isCleared = false;
    }
}
