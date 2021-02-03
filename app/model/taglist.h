#ifndef TAGLIST_H
#define TAGLIST_H

#include "tag.h"

#include <QSet>
#include <iterator>

class TagList
{
private:
    QList<Tag> m_data;
    QSet<Tag> m_added;
    QSet<Tag> m_removed;

public:
    TagList();

    int size();
    void add(Tag tag);
    void remove(Tag tag);
    bool contains(Tag tag);

    QSet<Tag> getAdded();   // Get the tags that where added to this list since last clear
    QSet<Tag> getRemoved(); // Get the tags that where added from the list since last clear
    void commit();          // Commit the add/remove operations

    // Methods to iterate other the list
    inline Tag operator[](int i) const { return m_data[i]; }
    typedef QList<Tag>::iterator iterator;
    typedef QList<Tag>::const_iterator const_iterator;
    inline const_iterator begin() const noexcept { return m_data.begin(); }
    inline const_iterator cbegin() const noexcept { return m_data.cbegin(); }
    inline const_iterator end() const noexcept { return m_data.end(); }
    inline const_iterator cend() const noexcept { return m_data.cend(); }
};

#endif // TAGLIST_H
