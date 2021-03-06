#ifndef TAG_H
#define TAG_H

#include <QDebug>
#include <QString>

class Tag
{
public:
    static Tag INVALID;

    QString value;
    QString color;

    Tag() = default;
    Tag(QString value);
    Tag(QString value, QString color);

    bool equal(const Tag& tag) const;
    bool operator== (const Tag& tag) const;
    bool operator!= (const Tag& tag) const;
    operator QString() const;
    static QString listToQString(const QList<Tag> list);
};

#endif // TAG_H
