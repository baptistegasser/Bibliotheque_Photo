#include "mainwindow.h"
#include "photocard.h"
#include "filtermenu.h"
#include "db/db.h"
#include "ui_photocard.h"

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
    currentFilter = Filter();
    QShortcut *shortcut = new QShortcut(QKeySequence(Qt::Key_Return), _search_comboBox);
    shortcut->setContext(Qt::ShortcutContext::WidgetShortcut);
    connect(shortcut, &QShortcut::activated, this, &MainWindow::setSearchKeyword);
    connect(_search_btn, &QAbstractButton::clicked, this, &MainWindow::setSearchKeyword);
    connect(_search_comboBox, &QComboBox::currentTextChanged, this, &MainWindow::constructSearchBar);

    // Config filter and sort buttons
    FilterMenu *menu = new FilterMenu(&this->currentFilter);
    _filter_btn->setMenu(menu);
    connect(menu, &FilterMenu::filterUpdated, this, &MainWindow::updateImages);

    orderType = ImageDAO::SortBy::None;
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

    gridLayoutModification_Window = new QGridLayout();
    modification_Window_Widget = new QStackedWidget();

    modification_Window_Widget->setLayout(gridLayoutModification_Window);

    _my_stack->setCurrentIndex(0);
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

/**
 * Construct list of image of one Directory
 * @brief MainWindow::constructImageList
 * @param dir
 */
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

/**
 * Construct a list of image with a list of Directory
 * @brief MainWindow::constructImageList
 * @param dirs
 */
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

    const QList<Image> images = DB::getImageDao().search(keyword, currentFilter, orderType, orderedSort);

    QHBoxLayout * photoGrid = new QHBoxLayout();

    int cpt = 0;

    for(const Image &img : images) {
        Image *image = new Image(img);
        PhotoCard *pC = new PhotoCard(scrollContent);
        pC->setImage(image);
        pC->setFixedSize(width_window-540/2,268);

        connect(pC, SIGNAL(clicked(PhotoCard *)), this, SLOT(showModificationWindow(PhotoCard *)));
        connect(pC, SIGNAL(isSelectionned(PhotoCard *)), this, SLOT(showSelectionnedPhoto(PhotoCard *)));

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

/**
 * Show a modification window of the photocard
 * @brief MainWindow::showModificationWindow
 * @param ph
 */
void MainWindow::showModificationWindow(PhotoCard *ph)
{
    if (currentWin != nullptr) {
        gridLayoutModification_Window->removeWidget(currentWin);
    }

    currentWin =  new Modification_window(modification_Window_Widget,ph->getImage());

    gridLayoutModification_Window->addWidget(currentWin);

    gridLayoutPage2->addWidget(modification_Window_Widget);

    connect(currentWin->getReturnButton(), SIGNAL(clicked()), this, SLOT(showImageList()));

    currentWin->getReturnButton();
    _my_stack->setCurrentIndex(1);
}

void MainWindow::showSelectionnedPhoto(PhotoCard *ph)
{
    if (photoSelectionned != nullptr) {
        photoSelectionned->getUi()->main_widget->setStyleSheet("QWidget#main_widget {border: none}");

        photoSelectionned->setIsClicked(false);
    }

    photoSelectionned = ph;

    photoSelectionned->getUi()->main_widget->setStyleSheet("QWidget#main_widget {border:2px solid rgb(25,25,25)}");

    photoSelectionned->setIsClicked(true);
}

/**
 * Slot for return to the image list
 * @brief MainWindow::showModificationWindow
 * @param ph
 */
void MainWindow::showImageList()
{
    _my_stack->setCurrentIndex(0);
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

    switch (index) {
    case 0:
        this->orderType = ImageDAO::SortBy::Name;
        break;
    case 1:
        this->orderType = ImageDAO::SortBy::Date;
        break;
    case 2:
        this->orderType = ImageDAO::SortBy::Size;
        break;
    case 3:
        this->orderType = ImageDAO::SortBy::Rating;
        break;
    default:
        this->orderType = ImageDAO::SortBy::None;
        break;
    }

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
