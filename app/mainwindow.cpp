#include "mainwindow.h"
#include "photocard.h"

#include "db/db.h"
#include "imagefinder.h"

#include <QDebug>
#include <QFileDialog>
#include <QScrollArea>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);
    connect(this, &QWidget::destroyed, this, &MainWindow::onClose);
    connect(_search_Text, &QLineEdit::textChanged, this, &MainWindow::showSearchMenu);

    Image *image = new Image(":/image/resources/example.jpg");
    photoCard *pC = new photoCard(this);
    pC->setImage(image);
    _my_stack->addWidget(pC);
    pC->show();

    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

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
