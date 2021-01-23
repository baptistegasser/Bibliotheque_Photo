#ifndef TAG_H
#define TAG_H

#include "QString"

class Tag
{
public:
    const int ID;
    QString value;
    QString color;

    Tag(const Tag& tag);
    Tag(int ID, QString value);
    Tag(int ID, QString value, QString color);

    void operator= (const Tag& tag);
    bool operator== (const Tag& tag) const;
};

#endif // TAG_H
