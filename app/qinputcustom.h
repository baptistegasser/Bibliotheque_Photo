#ifndef QINPUTCUSTOM_H
#define QINPUTCUSTOM_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QLineEdit>
#include "QFormLayout"

class QInputCustom : public QDialog
{
    bool done;
    QFormLayout *main;
public:
    QInputCustom(QWidget *parent = nullptr, int num = 1, QList<QString> texts = {},QList<QString> preTexts = {});
    QStringList getStrings();
    void accept();
    void reject();
    bool isDone();
    void addWidget(QWidget * w);
    virtual int exec();

private:
    QList<QLineEdit*> fields;

};

#endif // QINPUTCUSTOM_H
