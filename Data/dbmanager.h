#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QList>

class QImage;
class Item;
class Category;
class Shelf;
class Room;

class DBManager
{
public:
    DBManager(const QString& path);
    ~DBManager();
    QList<Item*> getAll();
    Item* getItemById(const QString& id);
    QList<Category*> getAllCategories();
    QList<Shelf*> getAllShelves();
    QList<Shelf*> getAllShelvesFromRoom(const QString& roomId);
    QList<Room*> getAllRooms();
    void updateCategory(const QString &itemId, const QString &category);
    void updateTitle(const QString &itemId, const QString &title);
    void updateDescription(const QString &itemId, const QString &desc);
    void updateImage(const QString &itemId, QImage* image);

    bool addOrUpdateEntryToRoomTable(Room& room);
    bool addOrUpdateEntryToShelfTable(Shelf& shelf);
    bool addOrUpdateEntryToCategoryTable(Category& category);
    bool addOrUpdateEntryToItemTable(Item& item);

private:
    QSqlDatabase m_db;

    bool createCategoryTable();
    bool createItemTable();
    bool createShelfTable();
    bool createRoomTable();


    bool hasRoomEntry(const QString &entryId);
    bool hasShelfEntry(QString& shelfId);
    bool hasCategoryEntry(QString& categoryId);
    bool hasItemEntry(const QString &itemId);
    bool hasValueInTable(const QString &valueId, const QString &table);

    QString getLastId(const QString &table);
};


#endif // DBMANAGER_H
