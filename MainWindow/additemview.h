#ifndef ADDITEMVIEW_H
#define ADDITEMVIEW_H

#include <QWidget>
#include "MainWindow/IItemView.hpp"

#include <QList>

#include "Data/category.h"
#include "Data/room.h"

class QPicture;
class QDate;

class Shelf;
class Room;
class Item;

namespace Ui {
class AddItemView;
}

class AddItemView : public IItemView
{
    Q_OBJECT

public:
    explicit AddItemView(QWidget *parent = 0);
    ~AddItemView();

/** ----------------------------------------------------------------------- **/

    virtual void setTitle(const QString &title);
    virtual const QString& getTitle();

    virtual void setDescription(const QString &description);
    virtual const QString& getDescription();

    virtual void setCategory(Category* category);
    virtual Category* getCategory();

    virtual const QPixmap* getPicture();
    virtual void setPicture(QPixmap* picture);

    virtual Shelf* getShelf();
    virtual void setShelf(Shelf* shelf);

    virtual void setRoom(Room* room);
    virtual Room* getRoom();

    virtual void setExpirationDate(const QDate& expirationDate);
    virtual const QDate& getExpirationDate();

/** ----------------------------------------------------------------------- **/

    virtual void setCategories(QList<Category*> categories);
    virtual void setShelves(QList<Shelf*> shelves);
    virtual void setRooms(QList<Room*> rooms);

/** ----------------------------------------------------------------------- **/

    virtual void hide();
    virtual void show();
    virtual void reset();

    virtual QWidget* getWidget();

signals:
    void roomSelectionChanged(QString id);

private slots:
    void onCategorySelected(QString category);
    void onStorageSelected(QString storage);
    void onRoomSelected(int roomIndex);

private:
    Ui::AddItemView *ui;
    QWidget* m_widget;
    void setCustomCategoryVisible(bool visible = true);
    void setStorageLineVisible(bool visible = true);
    void setRoomLineVisible(bool visible = true);
};

#endif // ADDITEMVIEW_H
