#ifndef TAG_H
#define TAG_H

#include "QString"

class Tag
{
public:
    Tag() = default;

    int ID;
    QString value;
    QString color;

    bool operator== (const Tag& tag) const { return this->value == tag.value; }
};

#endif // TAG_H
