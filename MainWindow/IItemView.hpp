#ifndef IITEMVIEW_HPP
#define IITEMVIEW_HPP

#include <QObject>
#include <QList>

class QString;
class QPixmap;
class QDate;
class QWidget;

class Category;
class Shelf;
class Room;


class IItemView : public QObject
{
    Q_OBJECT
public:
    IItemView(){}

    virtual void setTitle(const QString &title) = 0;
    virtual const QString& getTitle() = 0;

    virtual void setDescription(const QString &description) = 0;
    virtual const QString& getDescription() = 0;

    virtual void setCategory(Category* category) = 0;
    virtual Category* getCategory() = 0;

    virtual const QPixmap* getPicture() = 0;
    virtual void setPicture(QPixmap *picture) = 0;

    virtual Shelf* getShelf() = 0;
    virtual void setShelf(Shelf* shelf) = 0;

    virtual Room* getRoom() = 0;
    virtual void setRoom(Room* room) = 0;

    virtual void setExpirationDate(const QDate& expirationDate) = 0;
    virtual const QDate& getExpirationDate() = 0;

    virtual void setCategories(QList<Category*> categories) = 0;
    virtual void setShelves(QList<Shelf*> shelves) = 0;
    virtual void setRooms(QList<Room*> rooms) = 0;

    virtual QWidget* getWidget() = 0;

public slots:
    virtual void hide() = 0;
    virtual void show() = 0;
signals:
    void roomSelectionChanged(QString id);
    void takePhoto();
};

#endif // IITEMVIEW_HPP
