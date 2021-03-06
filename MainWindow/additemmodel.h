#ifndef ADDITEMMODEL_H
#define ADDITEMMODEL_H

#include <QObject>

#include <QList>

class DBManager;
class Category;
class Shelf;

class QString;
class QImage;
class QDate;
class Item;

class AddItemModel : public QObject
{
    Q_OBJECT
public:
    AddItemModel(DBManager* dbManager);
    ~AddItemModel();

    void setItem(Item* i);
    void saveItem();




    QList<Category*> getAllCategories();
    QList<Shelf*> getAllShelves();
//    void saveItem(const QString& id, QString& name, QString& description,
//                  Category* category, Shelf* shelf, QDate& expirationDate, QImage* picture = nullptr);

signals:
    void itemSet();
    void itemUpdatedOrInserted(const QString& id);

private:
    DBManager* m_db;
    Item* m_item;

};

#endif // ADDITEMMODEL_H
