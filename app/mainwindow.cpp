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

    _dir_tree->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    _dir_tree->displayDirs(DB::getDirectoryDao().getAll());
    connect(_add_dir, &QPushButton::clicked, this, &MainWindow::chooseFolder);
    //connect(_del_dir, &QPushButton::clicked, this, &MainWindow::removeFolder);



    gridLayoutPage = new QGridLayout();
    scrollAreaPage = new QScrollArea();
    vBoxPage = new QVBoxLayout();
    scrollContent = new QWidget(scrollAreaPage);

    page->setLayout(gridLayoutPage);

    gridLayoutPage->addWidget(scrollAreaPage);

    scrollContent->setLayout(vBoxPage);

    scrollAreaPage->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);


    constructImageList(DB::getDirectoryDao().getAll());
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

void MainWindow::chooseFolder()
{
    QString title = "Ouvrir un dossier d'images";
    QString baseDir = "/home";
    QFileDialog::Options options = QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks;

    QString dir = QFileDialog::getExistingDirectory(this, title, baseDir, options);
    addFolder(dir);
}

void MainWindow::addFolder(const QString path)
{
    Directory dir(path, Directory::INCLUDE);
    DB::getDirectoryDao().save(dir);

    ImageFinder(path).index();

    _dir_tree->displayDir(dir);

    constructImageList(dir);
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
        Image *image = new Image(img.path);
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
    vBoxPage->addLayout(photoGrid);
}

void MainWindow::constructImageList(QList<Directory> dirs)
{
    for (const Directory &dir : dirs) {
        constructImageList(dir);
    }
}


























