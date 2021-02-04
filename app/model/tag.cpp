#include "tag.h"

Tag Tag::INVALID ("INVALID", "INVALID");

Tag::Tag(QString value) :
    Tag(value, "#000000")
{}

Tag::Tag(QString value, QString color) :
    value(value),
    color(color)
{}

bool Tag::equal(const Tag& tag) const
{
    return value == tag.value && color == tag.color;
}

bool Tag::operator== (const Tag& tag) const
{
    return value == tag.value;
}

bool Tag::operator!= (const Tag& tag) const
{
    return !(*this == tag);
}

Tag::operator QString() const {
    QString s = QString("{ Value: %1, Color: %2 }").arg(value, color);
    return s;
}
