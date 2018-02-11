#include "datamodel.h"

#include "Data/dbmanager.h"
#include "Data/item.h"
#include "Data/room.h"
#include "Data/category.h"
#include "Data/shelf.h"

#include <QList>

DataModel::DataModel(DBManager* dbManager)
    :m_dbManager(dbManager)
{

}

DataModel::~DataModel() {
    delete m_dbManager;
}

Item* DataModel::getItemById(const QString& id) {
    return m_dbManager->getItemById(id);
}

QList<Item*> DataModel::getItems() {
    return m_dbManager->getAll();
}

void DataModel::changeCategory(const QString& itemId, const QString& categoryId) {
    m_dbManager->updateCategory(itemId, categoryId);
}

void DataModel::changeTitle(const QString& itemId, const QString& title) {
    m_dbManager->updateTitle(itemId, title);
}

void DataModel::changeDescription(const QString& itemId, const QString& desc) {
    m_dbManager->updateDescription(itemId, desc);
}

void DataModel::changeImage(const QString& itemId, QImage* image) {
    m_dbManager->updateImage(itemId, image);
}


QList<Category*> DataModel::getAllCategories() {
    return m_dbManager->getAllCategories();
}

QList<Shelf*> DataModel::getAllShelves() {
    return m_dbManager->getAllShelves();
}

QList<Shelf*> DataModel::getAllShelvesFromRoom(const QString& roomId) {
    return m_dbManager->getAllShelvesFromRoom(roomId) ;
}


QList<Room*> DataModel::getAllRooms() {
    return m_dbManager->getAllRooms();
}

void DataModel::saveItem(const QString& id, const QString& name, const QString& description,
                Category* category, Shelf* shelf, const QDate& expirationDate,
                QImage* picture) {
    Item i(id, name, description, category, picture);
    i.setExpirationDate(expirationDate);
    i.setShelf(shelf);
    m_dbManager->addOrUpdateEntryToItemTable(i);
    emit itemUpdatedOrInserted(i.id());
}
