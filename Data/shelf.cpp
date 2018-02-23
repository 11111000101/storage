#include "shelf.h"

Shelf::Shelf()
{

}

Shelf::~Shelf() {
    delete m_room;
}

Room* Shelf::room()
{
    return m_room;
}

void Shelf::setRoom(Room *place)
{
    m_room = place;
}

QString &Shelf::id()
{
    return m_id;
}

void Shelf::setId(const QString &id)
{
    m_id = QString(id);
}

QString Shelf::title() const
{
    return m_title;
}

void Shelf::setTitle(const QString &title)
{
    m_title = title;
}
