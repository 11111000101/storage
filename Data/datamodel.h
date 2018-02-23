#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QObject>
#include <QString>

class DBManager;
class Category;
class Shelf;
class Room;
class Room;
class Item;

class DataModel : public QObject
{
    Q_OBJECT
public:
    DataModel(DBManager* db);
    ~DataModel();

    virtual QList<Item*> getItems();
    virtual Item* getItemById(const QString& id);

public slots:
    virtual void changeCategory(const QString& itemId, const QString& categoryId);
    virtual void changeTitle(const QString& itemId, const QString& title);
    virtual void changeDescription(const QString& itemId, const QString& desc);
    virtual void changeImage(const QString& itemId, QPixmap* image);


    QList<Category*> getAllCategories();
    QList<Shelf*> getAllShelves();
    QList<Shelf*> getAllShelvesFromRoom(const QString& roomId);
    QList<Room*> getAllRooms();


    void saveItem(const QString& id, const QString& name, const QString& description,
                  Category* category, Shelf* shelf, const QDate& expirationDate,
                  QPixmap* picture = nullptr);

signals:
    void itemUpdatedOrInserted(const QString& id);

private:
    DBManager* m_dbManager;
};

#endif // DATAMODEL_H
