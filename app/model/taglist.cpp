#include "taglist.h"

TagList::TagList()
{
}

int TagList::size()
{
    return m_data.size();
}

void TagList::add(Tag tag)
{
    if (contains(tag)) {
        return;
    }

    m_data.append(tag);
    m_added.insert(tag);
    m_removed.remove(tag);
}

void TagList::remove(Tag tag)
{
    // If the tag was added since last clear, remove it
    // from the added list but don't mark as deleted
    if (m_added.contains(tag)) {
        m_added.remove(tag);
    } else {
        m_removed.insert(tag);
    }
    m_data.removeAll(tag);
}

bool TagList::contains(Tag tag)
{
    return m_data.contains(tag);
}

QSet<Tag> TagList::getAdded()
{
    return m_added;
}

QSet<Tag> TagList::getRemoved()
{
    return m_removed;
}

void TagList::commit()
{
    m_added.clear();
    m_removed.clear();
}
