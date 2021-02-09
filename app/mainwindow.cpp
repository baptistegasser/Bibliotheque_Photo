#include "mainwindow.h"
#include "photocard.h"

#include "db/db.h"

#include <QDebug>
#include <QFileDialog>
#include <QScrollArea>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);
    connect(this, &QWidget::destroyed, this, &MainWindow::onClose);
    connect(_search_comboBox, &QComboBox::currentTextChanged, this, &MainWindow::constructSearchBar);

    isCleared = false;

    //Image *image = new Image(":/image/resources/example.jpg");
    //photoCard *pC = new photoCard(_my_stack);
    //pC->setImage(image);
    //_my_stack->addWidget(pC);
    //pC->show();

    gridLayoutPage = new QGridLayout();
    scrollAreaPage = new QScrollArea();
    scrollAreaPage->setStyleSheet("background: transparent;");

    page->setLayout(gridLayoutPage);

    gridLayoutPage->addWidget(scrollAreaPage);

    scrollAreaPage->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    connect(_dir_manager, &DirectoryManager::directoryAdded, this, &MainWindow::updateImages);
    connect(_dir_manager, &DirectoryManager::directoryRemoved, this, &MainWindow::updateImages);
    updateImages();
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

void MainWindow::constructImageList(Directory dir)
{
    QLabel * label = new QLabel(scrollContent);
    label->setText("<strong>"+dir.dirName()+"</strong>");
    label->setMaximumSize(9999999, 30);
    label->setStyleSheet("padding: 5px; border: 1px solid rgb(231,231,231); border-radius: 7px; background-color: rgb(231,231,231); ");

    vBoxPage->addWidget(label);

    const QList<Image> images = DB::getImageDao().getInDir(dir);

    QHBoxLayout * photoGrid = new QHBoxLayout();

    int cpt = 0;

    for(const Image &img : images) {
        Image *image = new Image(img);
        qDebug() << img.path;
        photoCard *pC = new photoCard(scrollContent);
        pC->setImage(image);
        pC->setFixedSize(511,268);

        photoGrid->addWidget(pC);

        if (cpt%2 != 0) {
            vBoxPage->addLayout(photoGrid);
            photoGrid = new QHBoxLayout();
        }

        cpt += 1;
    }
    if (cpt%2 == 0)
        vBoxPage->addLayout(photoGrid);
}

void MainWindow::constructImageList(QList<Directory> dirs)
{
    vBoxPage = new QVBoxLayout();

     scrollContent = new QWidget();

    for (const Directory &dir : dirs) {
        constructImageList(dir);
    }

    scrollContent->setLayout(vBoxPage);
    scrollAreaPage->setWidget(scrollContent);
}

void MainWindow::updateImages()
{
    constructImageList(DB::getDirectoryDao().getAll());
}
