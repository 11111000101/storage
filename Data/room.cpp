#include "room.h"

Room::Room()
{

}

const QString& Room::title()
{
    return m_title;
}

void Room::setTitle(const QString &title)
{
    m_title = QString(title);
}

const QString& Room::id()
{
    return m_id;
}

void Room::setId(const QString &id)
{
    m_id = QString(id);
}
