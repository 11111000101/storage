#ifndef ADDITEMVIEW_H
#define ADDITEMVIEW_H

#include <QWidget>
#include <QList>
#include <QDate>

#include "Data/category.h"
#include "Data/room.h"

class QImage;

class Shelf;
class Room;

namespace Ui {
class AddItemView;
}

class AddItemView : public QWidget
{
    Q_OBJECT

public:
    explicit AddItemView(QWidget *parent = 0);
    ~AddItemView();

    void setCategories(QList<Category*> categories);
    void setShelves(QList<Shelf*> shelves);
    void setRooms(QList<Room*> rooms);

    Category* getCategory();
    QString getExpirationDateString();
    QDate getExpirationDate();
    QString getTitle();
    QString getDescription();
    Room* getRoom();
    QImage* getImage();
    Shelf* getShelf();

    void show();
    void reset();

signals:
    void roomSelectionChanged(QString);

private slots:
    void onCategorySelected(QString category);
    void onStorageSelected(QString storage);
    void onRoomSelected(int roomIndex);

private:
    Ui::AddItemView *ui;
    void setCustomCategoryVisible(bool visible = true);
    void setStorageLineVisible(bool visible = true);
    void setRoomLineVisible(bool visible = true);
};

#endif // ADDITEMVIEW_H
