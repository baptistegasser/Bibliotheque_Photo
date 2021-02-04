#include "qinputcustom.h"
#include "QFormLayout"
#include "QLabel"
#include "QDialogButtonBox"
#include "iostream"


QInputCustom::QInputCustom(QWidget * parent, int numInput, QList<QString> texts) : QDialog(parent)
{
    QFormLayout *main = new QFormLayout(this);
    for (int i = 0;i< numInput ;i++)
    {

        QLabel *label = new QLabel(QString(texts[i]),this);
        QLineEdit *line = new QLineEdit(this);
        main->addRow(label,line);
        fields.append(line);
    }

    QDialogButtonBox buttonBox (QDialogButtonBox::Ok|QDialogButtonBox::Cancel,Qt::Horizontal,this);
    main->addWidget(&buttonBox);
    bool conn = connect(&buttonBox, &QDialogButtonBox::accepted,this, &QInputCustom::accept);
    Q_ASSERT(conn);
    conn = connect(&buttonBox, &QDialogButtonBox::rejected,this, &QInputCustom::reject);
    Q_ASSERT(conn);
    this->exec();

}

QStringList QInputCustom::getStrings()
{

        QStringList list;
        for(QLineEdit *qle:this->fields)
        {
            list.append(qle->text());
        }
        return list;
}

