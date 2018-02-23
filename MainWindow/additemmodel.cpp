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

void AddItemModel::setItem(Item* i) {
    this->m_item = i;
    emit this->itemSet();
}

void saveItem() {

}

QList<Category*> AddItemModel::getAllCategories() {
    return m_db->getAllCategories();
}

QList<Shelf*> AddItemModel::getAllShelves() {
    return m_db->getAllShelves();
}

void AddItemModel::saveItem() {
    m_db->addOrUpdateEntryToItemTable(*this->m_item);
    emit itemUpdatedOrInserted(m_item->id());
}
