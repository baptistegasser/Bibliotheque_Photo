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
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);

    this->isCleared = false;
    this->width_window = geometry().width();
    this->height_window = geometry().height();
    this->currentSearch.sortOrder = ImageSearch::Name;

    _album_combobox->addItems(DB::getAlbumDAO().getAlbums());
    this->currentSearch.album = _album_combobox->itemText(0);

    // Configure and connect the search bar and button
    QShortcut *shortcut = new QShortcut(QKeySequence(Qt::Key_Return), _search_comboBox);
    shortcut->setContext(Qt::ShortcutContext::WidgetShortcut);
    connect(shortcut, &QShortcut::activated, this, &MainWindow::setSearchKeyword);

    // Config filter and sort buttons
    FilterMenu *menu = new FilterMenu(&this->currentSearch);
    _filter_btn->setMenu(menu);
    connect(menu, &FilterMenu::filterUpdated, this, &MainWindow::updateImages);

    _search_comboBox->setCompleter(nullptr);
    constructSearchBar("");

    showImageList();
}

MainWindow::~MainWindow()
{
}

/**
 * Set the size of mainWindow
 * @brief MainWindow::setGeometrySize
 * @param width
 * @param height
 */
void MainWindow::setGeometrySize(int width, int height)
{
    setGeometry(0,0,width, height);
    width_window = width;
    height_window = height;
    updateImages();
}

void MainWindow::onClose() {
    DB::close();
}

/**
 * Construct the search bar for tag research
 * @brief MainWindow::constructSearchBar
 * @param s
 */
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
 * Update the image list in the mainWindow
 * @brief MainWindow::updateImages
 */
void MainWindow::updateImages()
{
    photoSelectionned = nullptr;
    QVBoxLayout *vBoxPage = new QVBoxLayout();

    QWidget *scrollContent = new QWidget();

    QSizePolicy test;
    test.setHorizontalPolicy(QSizePolicy::Expanding);
    test.setVerticalPolicy(QSizePolicy::Expanding);

    scrollContent->setSizePolicy(test);

    const QList<Image> images = DB::getImageDao().search(currentSearch);

    QHBoxLayout * photoGrid = new QHBoxLayout();

    int cpt = 0;

    for(const Image &img : images) {
        Image *image = new Image(img);
        PhotoCard *pC = new PhotoCard(scrollContent);
        pC->setImage(image);
        pC->setFixedSize((width_window-320)/2,268);

        connect(pC, SIGNAL(clicked(PhotoCard *)), this, SLOT(showModificationWindow(PhotoCard *)));
        connect(pC, SIGNAL(isSelectionned(PhotoCard *)), this, SLOT(showSelectionnedPhoto(PhotoCard *)));

        photoGrid->addWidget(pC);

        if (cpt%2 != 0) {
            vBoxPage->addLayout(photoGrid);
            photoGrid = new QHBoxLayout();
        }

        cpt += 1;
    }
    // Si il y a un nombre d'éléments impairs
    if (cpt%2 != 0)
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
        page_2->layout()->removeWidget(currentWin);
    }

    currentWin = new Modification_window(page_2, ph->getImage());
    page_2->layout()->addWidget(currentWin);

    connect(currentWin->getReturnButton(), SIGNAL(clicked()), this, SLOT(showImageList()));

    currentWin->getReturnButton();
    _my_stack->setCurrentIndex(1);
}

/**
 * Show the design of the selected photo
 * @brief MainWindow::showSelectionnedPhoto
 * @param ph
 */
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
    updateImages();
    _my_stack->setCurrentIndex(0);
}

/**
 * Set the search request
 * @brief MainWindow::setSearchKeyword
 */
void MainWindow::setSearchKeyword()
{
    qDebug() << __FUNCTION__;
    _search_comboBox->clearFocus();
    this->currentSearch.keyword = _search_comboBox->currentText();
    updateImages();
}

/**
 *
 * @brief MainWindow::addAlbum
 */
void MainWindow::addAlbum()
{
    bool ok;
    QString name = QInputDialog::getText(this, tr("Choisir le nom du nouvel album photo"), "", QLineEdit::Normal, "", &ok);
    if (ok && !name.isEmpty()) {
        currentSearch.album = name;
        updateImages();
    }
}


void MainWindow::setAlbum(int i)
{
    currentSearch.album = _album_combobox->itemText(i);
}

/**
 * Show the type of order
 * @brief MainWindow::sortItemChanged
 * @param index
 */
void MainWindow::sortItemChanged(int index)
{
    if (index == -1) {
        _sort_comboBox->setCurrentIndex(index);
        return;
    }

    switch (index) {
    case 0:
        this->currentSearch.sortOrder = currentSearch.Name;
        break;
    case 1:
        this->currentSearch.sortOrder = currentSearch.Date;
        break;
    case 2:
        this->currentSearch.sortOrder = currentSearch.Size;
        break;
    case 3:
        this->currentSearch.sortOrder = currentSearch.Rating;
        break;
    default:
        this->currentSearch.sortOrder = currentSearch.None;
        break;
    }

    updateImages();
}

/**
 * Show the direction of order
 * @brief MainWindow::sortOrderChanged
 */
void MainWindow::sortOrderChanged()
{
    this->currentSearch.sortDescendant = !currentSearch.sortDescendant;
    if (currentSearch.sortDescendant) {
        _sort_order_btn->setIcon(QIcon(":/icon/sort"));
    } else {
        _sort_order_btn->setIcon(QIcon(":/icon/sort_reverse"));
    }
    updateImages();
}
