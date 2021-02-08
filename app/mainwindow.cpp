#include "mainwindow.h"
#include "photocard.h"

#include "db/db.h"
#include "imagefinder.h"

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

    Image *image = new Image(":/image/resources/example.jpg");
    photoCard *pC = new photoCard(_my_stack);
    pC->setImage(image);
    //_my_stack->addWidget(pC);
    //pC->show();

    _dir_tree->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    _dir_tree->displayDirs(DB::getDirectoryDao().getAll());
    connect(_add_dir, &QPushButton::clicked, this, &MainWindow::chooseFolder);
    //connect(_del_dir, &QPushButton::clicked, this, &MainWindow::removeFolder);
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
}
