#ifndef ROOM_H
#define ROOM_H

#include <QString>

class Room
{
public:
    Room();

    const QString& title();
    void setTitle(const QString &title);

    const QString& id();
    void setId(const QString &id);

private:
    QString m_title;
    QString m_id;
};

#endif // ROOM_H
