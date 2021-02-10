#include "mainwindow.h"
#include "photocard.h"
#include "modification_window.h"
#include "filtermenu.h"
#include "db/db.h"

#include <QDebug>
#include <QFileDialog>
#include <QScrollArea>
#include <QShortcut>
#include <QLabel>
#include <QMenu>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);

    // Configure and connect the search bar and button
    keyword = QString::Null();
    currentFilter = Filter::Empty();
    QShortcut *shortcut = new QShortcut(QKeySequence(Qt::Key_Return), _search_comboBox);
    shortcut->setContext(Qt::ShortcutContext::WidgetShortcut);
    connect(shortcut, &QShortcut::activated, this, &MainWindow::setSearchKeyword);
    connect(_search_btn, &QAbstractButton::clicked, this, &MainWindow::setSearchKeyword);
    connect(_search_comboBox, &QComboBox::currentTextChanged, this, &MainWindow::constructSearchBar);

    // Config filter and sort buttons
    FilterMenu *menu = new FilterMenu(&this->currentFilter);
    _filter_btn->setMenu(menu);
    connect(menu, &FilterMenu::filterUpdated, this, &MainWindow::updateImages);

    orderType = 0;
    orderedSort = true;

    // Handle windows closing
    connect(this, &QWidget::destroyed, this, &MainWindow::onClose);

    isCleared = false;

    width_window = width();

    gridLayoutPage = new QGridLayout();
    scrollAreaPage = new QScrollArea();
    scrollAreaPage->setStyleSheet("background: transparent;");

    page->setLayout(gridLayoutPage);


    gridLayoutPage->addWidget(scrollAreaPage);

    scrollAreaPage->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollAreaPage->setStyleSheet("background-color : white;");

    connect(_dir_manager, &DirectoryManager::directoryAdded, this, &MainWindow::updateImages);
    connect(_dir_manager, &DirectoryManager::directoryRemoved, this, &MainWindow::updateImages);
    updateImages();

    gridLayoutPage2 = new QGridLayout();
    page_2->setLayout(gridLayoutPage2);
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
        PhotoCard *pC = new PhotoCard(scrollContent);
        pC->setImage(image);
        pC->setFixedSize(width_window-540/2,268);

        connect(pC, SIGNAL(clicked(PhotoCard *)), this, SLOT(showModificationWindow(PhotoCard *)));

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

    QSizePolicy test;
    test.setHorizontalPolicy(QSizePolicy::Expanding);
    test.setVerticalPolicy(QSizePolicy::Expanding);

    scrollContent->setSizePolicy(test);

    for (const Directory &dir : dirs) {
        constructImageList(dir);
    }

    scrollContent->setLayout(vBoxPage);
    scrollAreaPage->setWidget(scrollContent);
}

void MainWindow::updateImages()
{
    vBoxPage = new QVBoxLayout();

    scrollContent = new QWidget();

    QSizePolicy test;
    test.setHorizontalPolicy(QSizePolicy::Expanding);
    test.setVerticalPolicy(QSizePolicy::Expanding);

    scrollContent->setSizePolicy(test);

    const QList<Image> images = DB::getImageDao().search(keyword, currentFilter);

    QHBoxLayout * photoGrid = new QHBoxLayout();

    int cpt = 0;

    for(const Image &img : images) {
        Image *image = new Image(img);
        PhotoCard *pC = new PhotoCard(scrollContent);
        pC->setImage(image);
        pC->setFixedSize(width_window-540/2,268);

        connect(pC, SIGNAL(clicked(PhotoCard *)), this, SLOT(showModificationWindow(PhotoCard *)));

        photoGrid->addWidget(pC);

        if (cpt%2 != 0) {
            vBoxPage->addLayout(photoGrid);
            photoGrid = new QHBoxLayout();
        }

        cpt += 1;
    }
    if (cpt%2 == 0)
        vBoxPage->addLayout(photoGrid);

    scrollContent->setLayout(vBoxPage);
    scrollAreaPage->setWidget(scrollContent);
}

void MainWindow::showModificationWindow(PhotoCard *ph)
{
    qDebug() << "Click" << this;

    Modification_window *win =  new Modification_window(nullptr,ph->getImage());
    gridLayout_2->addWidget(win);

    _my_stack->setCurrentIndex(1);
}

void MainWindow::setSearchKeyword()
{
    _search_comboBox->clearFocus();
    keyword = _search_comboBox->currentText();
    updateImages();
}

void MainWindow::sortItemChanged(int index)
{
    if (index == -1) {
        _sort_comboBox->setCurrentIndex(index);
        return;
    }

    this->orderType = index;
    updateImages();
}

void MainWindow::sortOrderChanged()
{
    this->orderedSort = !orderedSort;
    if (orderedSort) {
        _sort_order_btn->setIcon(QIcon(":/icon/sort"));
    } else {
        _sort_order_btn->setIcon(QIcon(":/icon/sort_reverse"));
    }
    updateImages();
}
