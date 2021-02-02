#ifndef TAG_H
#define TAG_H

#include <QDebug>
#include <QString>

class Tag
{
public:
    Tag() = default;
    Tag(QString value): Tag(value, "#000000") {};
    Tag(QString value, QString color): value(value), color(color) {};

    QString value;
    QString color;

    bool operator== (const Tag& tag) const { return value == tag.value && color == tag.color; }
    bool operator!= (const Tag& tag) const { return !(*this == tag); }

    operator QString() const {
        QString s = QString("{ Value: %1, Color: %2 }").arg(value, color);
        return s;
    }
};

#endif // TAG_H
