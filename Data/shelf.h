#ifndef SHELF_H
#define SHELF_H

#include "room.h"

#include <QString>

class Shelf
{
public:
    Shelf();
    ~Shelf();

    Room* room();
    void setRoom(Room* room);

    QString& id();
    void setId(const QString &id);

    QString title() const;
    void setTitle(const QString &title);

private:
    Room* m_room;
    QString m_title;
    QString m_id;
};

#endif // SHELF_H
