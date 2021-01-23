#include "tag.h"

Tag::Tag(const Tag& tag): Tag(tag.ID, tag.value, tag.color)
{
}

Tag::Tag(int ID, QString value): Tag(ID, value, "#000000")
{
}

Tag::Tag(int ID, QString value, QString color): ID(ID), value(value), color(color)
{
}


void Tag::operator= (const Tag& tag)
{
    this->value = tag.value;
    this->color = tag.color;
}

bool Tag::operator== (const Tag& tag) const
{
    return this->value == tag.value;
}
