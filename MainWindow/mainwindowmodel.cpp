#include "mainwindowmodel.hpp"

#include <QDebug>

#include "Data/dbmanager.h"
#include "Data/category.h"
#include "Data/shelf.h"
#include "Data/item.h"

MainWindowModel::MainWindowModel(DBManager *dbManager)
    : m_db(dbManager)
{
//    QString catId("");
//    QString catTitle("Category 1");
//    Category* c = new Category();
//    c->setId(catId);
//    c->setTitle(catTitle);

//    QString t("1");
//    Place* p = new Place();
//    p->setId(t);
//    p->setTitle((t="Keller"));

//    Shelf* s = new Shelf();
//    s->setTitle("Shelf 1");
//    s->setPlace(p);

//    QString itemId("");
//    QString itemName("Item 1");
//    QString itemDesc("item description");

//    Item i(itemId, itemName, itemDesc, c);
//    i.setId((t=""));
//    i.setShelf(s);
//    this->m_db->addOrUpdateEntryToItemTable(i);
}

MainWindowModel::~MainWindowModel()
{
    qDebug() << "~MainWindowModel";
}


QList<Item*> MainWindowModel::getItems() {
    return m_db->getAll();
}

/** -------------------------------------------------- **/

void MainWindowModel::changeCategory(QString& itemId, QString& category) {
    m_db->updateCategory(itemId, category);
}

void MainWindowModel::changeTitle(QString& itemId, QString& title) {
    m_db->updateTitle(itemId, title);
}

void MainWindowModel::changeDescription(QString& itemId, QString& desc) {
    m_db->updateDescription(itemId, desc);
}

void MainWindowModel::changeImage(QString& itemId, QImage* image) {
    m_db->updateImage(itemId, image);
}
