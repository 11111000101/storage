#include "additemmodel.h"

#include "Data/dbmanager.h"
#include "Data/item.h"

#include <QDate>
#include <QDebug>

AddItemModel::AddItemModel(DBManager *dbManager)
    :m_db(dbManager)
{

}

AddItemModel::~AddItemModel(){
    qDebug() << "~AddItemModel";
}

QList<Category*> AddItemModel::getAllCategories() {
    return m_db->getAllCategories();
}

QList<Shelf*> AddItemModel::getAllShelves() {
    return m_db->getAllShelves();
}

void AddItemModel::saveItem(const QString& id, QString& name, QString& description,
                            Category* category, Shelf* shelf, QDate& expirationDate, QImage* picture) {
    Item i(id, name, description, category, picture);
    i.setShelf(shelf);
    i.setExpirationDate(expirationDate);
    m_db->addOrUpdateEntryToItemTable(i);
    emit itemUpdatedOrInserted(i.id());
}
