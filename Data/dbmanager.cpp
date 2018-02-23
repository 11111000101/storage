#include "dbmanager.h"

#include <QDebug>
#include <QDir>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QPixmap>
#include <QBuffer>

#include "Data/item.h"
#include "Data/category.h"
#include "Data/room.h"
#include "Data/shelf.h"


#define DB_CATEGORY QString("category")
#define DB_ITEM QString("item")
#define DB_SHELF QString("shelf")
#define DB_ROOM QString("room")


DBManager::DBManager(const QString& path) {
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if (!m_db.open())
    {
        qDebug() << "Error: connection with database fail";
    }
    else
    {
        bool error = !this->createCategoryTable();
        error |= !this->createRoomTable();
        error |= !this->createShelfTable();
        error |= !this->createItemTable();
        qDebug() << "Database: connection ok ";
        if (error) {
            qDebug() << "error creating tables!";
        }
    }
}

DBManager::~DBManager() {
    m_db.close();
}

/**
 * @brief DBManager::getAll
 * @return List of Item* which have to be deleted.
 */
QList<Item*> DBManager::getAll() {
    QList<Item*> list;
    QSqlQuery query(m_db);
    query.prepare(QString("select i.id as itemId, i.title as itemTitle, i.description as itemDescription, i.image as itemImage,"
                          " c.id as categoryId, c.title as categoryTitle,"
                          " s.id as ShelfID,"
                          " s.title as sTitle,"
                          " p.id as roomId, p.title as roomTitle"
                          " from item i"
                          " inner join category c on i.category = c.id"
                          " inner join shelf s on i.shelf = s.id"
                          " inner join room p on s.room = p.id;"));
    if (query.exec()) {
        while (query.next()) {
            Category* c = new Category();
            QString cId(query.value(query.record().indexOf("categoryId")).toString());
            QString cTitle(query.value(query.record().indexOf("categoryTitle")).toString());
            c->setId(cId);
            c->setTitle(cTitle);

            Room* p = new Room();
            QString pId(query.value(query.record().indexOf("roomId")).toString());
            QString pTitle(query.value(query.record().indexOf("roomTitle")).toString());
            p->setId(pId);
            p->setTitle(pTitle);

            Shelf* s = new Shelf();
            QString sId(query.value(query.record().indexOf("shelfId")).toString());
            QString sTitle(query.value(query.record().indexOf("sTitle")).toString());
            s->setId(sId);
            s->setTitle(sTitle);
            s->setRoom(p);

            QString iId(query.value(query.record().indexOf("itemId")).toString());
            QString iTitle(query.value(query.record().indexOf("itemTitle")).toString());
            QString iDescription(query.value(query.record().indexOf("itemDescription")).toString());
            Item* i = new Item(iId, iTitle, iDescription, c);
            i->setShelf(s);

            list.append(i);
        }
    } else {
        qDebug() << "Error fetching items!";
    }
    return list;
}

Item* DBManager::getItemById(const QString& id) {
    QSqlQuery query(m_db);
    query.prepare(QString("select i.id as itemId, i.title as itemTitle, i.description as itemDescription, i.image as itemImage,"
                          " c.id as categoryId, c.title as categoryTitle,"
                          " s.id as ShelfID,"
                          " p.id as roomId, p.title as roomTitle"
                          " from item i"
                          " inner join category c on i.category = c.id"
                          " inner join shelf s on i.shelf = s.id"
                          " inner join room p on s.room = p.id"
                          " where i.id = :id;"));
    query.bindValue(":id", id);
    if (query.exec()) {
        if (query.next()) {
            Category* c = new Category();
            QString cId(query.value(query.record().indexOf("categoryId")).toString());
            QString cTitle(query.value(query.record().indexOf("categoryTitle")).toString());
            c->setId(cId);
            c->setTitle(cTitle);

            Room* p = new Room();
            QString pId(query.value(query.record().indexOf("roomId")).toString());
            QString pTitle(query.value(query.record().indexOf("roomTitle")).toString());
            p->setId(pId);
            p->setTitle(pTitle);

            Shelf* s = new Shelf();
            QString sId(query.value(query.record().indexOf("shelfId")).toString());
            s->setId(sId);
            s->setRoom(p);

            QString iId(query.value(query.record().indexOf("itemId")).toString());
            QString iTitle(query.value(query.record().indexOf("itemTitle")).toString());
            QString iDescription(query.value(query.record().indexOf("itemDescription")).toString());
            Item* i = new Item(iId, iTitle, iDescription, c);
            i->setShelf(s);

            return i;
        }
        else {
            return nullptr;
        }
    } else {
        qDebug() << "Error fetching item with id " << id;
        return nullptr;
    }
}

QList<Category*> DBManager::getAllCategories(){
    QList<Category*> list;
    QSqlQuery query(m_db);
    query.prepare(QString("select c.id as categoryId, c.title as categoryTitle"
                          " from category c"));
    if (query.exec()) {
        while (query.next()) {
            Category* c = new Category();
            QString cId(query.value(query.record().indexOf("categoryId")).toString());
            QString cTitle(query.value(query.record().indexOf("categoryTitle")).toString());
            c->setId(cId);
            c->setTitle(cTitle);
            list.append(c);
        }
    } else {
        qDebug() << "Error fetching items!";
    }
    return list;
}

QList<Shelf*> DBManager::getAllShelves() {
    QList<Shelf*> list;
    QSqlQuery query(m_db);
    query.prepare(QString("select s.id as shelfId, s.title as shelfTitle, s.room as shelfRoomId, p.title as roomTitle"
                          " from shelf s"
                          " inner join room p on p.id = s.room;"));
    if (query.exec()) {
        while (query.next()) {
            Shelf* s = new Shelf();
            QString sId(query.value(query.record().indexOf("shelfId")).toString());
            QString sRoomId(query.value(query.record().indexOf("shelfRoomId")).toString());
            QString sTitle(query.value(query.record().indexOf("shelfTitle")).toString());
            QString pTitle(query.value(query.record().indexOf("roomTitle")).toString());
            s->setId(sId);
            s->setTitle(sTitle);

            Room* p = new Room();
            p->setId(sRoomId);
            p->setTitle(pTitle);

            s->setRoom(p);
            list.append(s);
        }
    } else {
        qDebug() << "Error fetching items!";
    }
    return list;
}

QList<Shelf*> DBManager::getAllShelvesFromRoom(const QString& roomId) {
    QList<Shelf*> list;
    QSqlQuery query(m_db);
    query.prepare(QString("select s.id as shelfId, s.title as shelfTitle, s.room as shelfRoomId, p.title as roomTitle"
                          " from shelf s"
                          " inner join room p on p.id = s.room"
                          " where p.id = :roomId;"));
    query.bindValue(":roomId", roomId);
    if (query.exec()) {
        while (query.next()) {
            Shelf* s = new Shelf();
            QString sId(query.value(query.record().indexOf("shelfId")).toString());
            QString sRoomId(query.value(query.record().indexOf("shelfRoomId")).toString());
            QString sTitle(query.value(query.record().indexOf("shelfTitle")).toString());
            QString pTitle(query.value(query.record().indexOf("roomTitle")).toString());
            s->setId(sId);
            s->setTitle(sTitle);

            Room* p = new Room();
            p->setId(sRoomId);
            p->setTitle(pTitle);

            s->setRoom(p);
            list.append(s);
        }
    } else {
        qDebug() << "Error fetching items!";
    }
    return list;
}

QList<Room*> DBManager::getAllRooms() {
    QList<Room*> list;
    QSqlQuery query(m_db);
    query.prepare(QString("select p.id as roomId, p.title as roomTitle"
                          " from room p;"));
    if (query.exec()) {
        while (query.next()) {
            QString roomId(query.value(query.record().indexOf("roomId")).toString());
            QString roomTitle(query.value(query.record().indexOf("roomTitle")).toString());

            Room* p = new Room();
            p->setId(roomId);
            p->setTitle(roomTitle);
            list.append(p);
        }
    } else {
        qDebug() << "Error fetching items!";
    }
    return list;
}

void DBManager::updateCategory(const QString& itemId, const QString& category) {
    QSqlQuery q(m_db);
    q.prepare("update " + DB_ITEM + " set category = :category where id = :itemID;");
    q.bindValue(":category", category);
    q.bindValue(":itemID", itemId);
    q.exec();
}

void DBManager::updateTitle(const QString& itemId, const QString& title) {
    QSqlQuery q(m_db);
    q.prepare("update " + DB_ITEM + " set title = :title where id = :itemID;");
    q.bindValue(":title", title);
    q.bindValue(":itemID", itemId);
    q.exec();
}

void DBManager::updateDescription(const QString& itemId, const QString& desc) {
    QSqlQuery q(m_db);
    q.prepare("update " + DB_ITEM + " set description = :description where id = :itemID;");
    q.bindValue(":description", desc);
    q.bindValue(":itemID", itemId);
    q.exec();
}

void DBManager::updateImage(const QString& itemId, QPixmap* image) {
    QSqlQuery q(m_db);
    q.prepare("update " + DB_ITEM + " set image = :image where id = :itemID;");
    if (image == NULL) {
        q.bindValue(":image", "");
    } else {
        QByteArray bArray;
        QBuffer buffer(&bArray);
        buffer.open(QIODevice::WriteOnly);
        image->save(&buffer, "PNG");
        q.bindValue(":image", bArray);
    }
    q.bindValue(":itemID", itemId);
    q.exec();
}

bool DBManager::addOrUpdateEntryToRoomTable(Room& room) {
    QSqlQuery q(m_db);
    if (hasRoomEntry(room.id())) {
        q.prepare("update " + DB_ROOM + " set title = :title"
                                        " where id = :id;");
        q.bindValue(":title", room.title());
        q.bindValue(":id", room.id());
        q.exec();
    } else {
        q.prepare("insert into " + DB_ROOM + " (title) values (:title)");
        q.bindValue(":title", room.title());

        if (q.exec()) {
            room.setId((getLastId(DB_ROOM)));
            return true;
        }
    }

    return false;
}

bool DBManager::addOrUpdateEntryToShelfTable(Shelf& shelf) {
    QSqlQuery q(m_db);
    if (hasShelfEntry(shelf.id())) {
        q.prepare("update " + DB_SHELF + " set room = :roomID, title = :shelfTitle"
                                         " where id = :id;");
        q.bindValue(":roomID", shelf.room()->id());
        q.bindValue(":shelfTitle", shelf.title());
        q.bindValue(":id", shelf.id());
        return q.exec();
    } else {
        q.prepare("insert into " + DB_SHELF + " (room, title) values (:roomID, :shelfTitle)");
        q.bindValue(":roomID", shelf.room()->id());
        q.bindValue(":shelfTitle", shelf.title());
        if (q.exec()) {
            shelf.setId(getLastId(DB_SHELF));
            return true;
        }
    }
    return false;
}

bool DBManager::addOrUpdateEntryToCategoryTable(Category& category) {
    QSqlQuery q(m_db);
    if (hasCategoryEntry(category.id())) {
        q.prepare("update " + DB_CATEGORY + " set title = :title where id = :id;");
        q.bindValue(":title", category.title());
        q.bindValue(":id", category.id());
        q.exec();
        return true;
    } else {
        q.prepare("insert into " + DB_CATEGORY + " (title) values (:title)");
        q.bindValue(":title", category.title());
        if (q.exec()) {
            category.setId(getLastId(DB_CATEGORY));
            return true;
        }
    }
    return false;
}

bool DBManager::addOrUpdateEntryToItemTable(Item& item) {
    this->addOrUpdateEntryToCategoryTable(*item.category());
    this->addOrUpdateEntryToRoomTable(*item.shelf()->room());
    this->addOrUpdateEntryToShelfTable(*item.shelf());
    if (!hasItemEntry(item.id())) {
        QSqlQuery query(m_db);
        query.prepare(QString("insert into ").append(DB_ITEM)
                      .append(" (title, description, image, category, shelf)")
                      .append(" values (:title, :description, :image, :category, :shelf)"));
        query.bindValue(":title", item.name());
        query.bindValue(":description", item.description());
        if (item.picture() != 0) {
            QByteArray bArray;
            QBuffer buffer(&bArray);
            buffer.open(QIODevice::WriteOnly);
            item.picture()->save(&buffer, "PNG");

//            QByteArray arr((char*)->bits(), item.picture()->byteCount());
            query.bindValue(":image", bArray);
        } else {
            query.bindValue(":image", QVariant::ByteArray);
        }
        query.bindValue(":category", item.category()->id());
        query.bindValue(":shelf", item.shelf()->id());
        if (!query.exec()) {
            qDebug() << "Error occured inserting item: " << query.lastError();
            qDebug() << query.lastQuery();
        } else {
            item.setId(this->getLastId(DB_ITEM));
        }
    } else {
        this->updateImage(item.id(), item.picture());
        this->updateDescription(item.id(), item.description());
//        this->updateCategory(item.id(), item.category().id());
        this->updateTitle(item.id(), item.name());
    }
}

bool DBManager::hasRoomEntry(const QString& entryId){
    QString table = DB_ROOM;
    return this->hasValueInTable(entryId, table);
}

bool DBManager::hasShelfEntry(QString& shelfId) {
    QString table = DB_SHELF;
    return this->hasValueInTable(shelfId, table);
}

bool DBManager::hasCategoryEntry(QString& categoryId) {
    QString table = DB_CATEGORY;
    return this->hasValueInTable(categoryId, table);
}

bool DBManager::hasItemEntry(const QString& itemId) {
    QString table = DB_ITEM;
    return this->hasValueInTable(itemId, table);
}

bool DBManager::hasValueInTable(const QString& valueId, const QString& table) {
    if (valueId.isEmpty()) {
        return false;
    }
    QSqlQuery query(m_db);
    query.prepare(QString("select * from "+table+
                          " where id = :id"));
    query.bindValue(":id", valueId);
    if (query.exec()) {
        qDebug() << "hasValueInTable +";
    } else {
        qDebug() << "hasValueInTable -";
    }
    return query.next();
}

QString DBManager::getLastId(const QString &table) {
    QSqlQuery query(m_db);
    query.prepare("select max(id) as id from " + table + ";");
//    query.bindValue(":tableName", table);
    query.exec();
    if (query.next()) {
        return query.value(query.record().indexOf("id")).toString();
    } else {
        return "";
    }
}

/** ---------------------------- create table --------------------------- **/

bool DBManager::createCategoryTable() {
    QSqlQuery q(m_db);
    QString query = QString("CREATE TABLE IF NOT EXISTS ").append(DB_CATEGORY).
            append(" (id integer PRIMARY KEY AUTOINCREMENT, title varchar(255));");
    return q.exec(query);
}

bool DBManager::createItemTable() {
    QSqlQuery q(m_db);
    QString query = QString("CREATE TABLE IF NOT EXISTS ").append(DB_ITEM)
            .append(" (id integer PRIMARY KEY AUTOINCREMENT, title varchar(255)"
                    ", description varchar(255), image blob, category integer, shelf integer"
                    ", FOREIGN KEY (category) REFERENCES ")
            .append(DB_CATEGORY).append("(id)")
            .append(", FOREIGN KEY (shelf) REFERENCES ")
            .append(DB_SHELF).append("(id));");
    return q.exec(query);
}

bool DBManager::createShelfTable() {
    QSqlQuery q(m_db);
    QString query = QString("CREATE TABLE IF NOT EXISTS ").append(DB_SHELF).
            append(" (id integer PRIMARY KEY AUTOINCREMENT, title varchar(255),"
                   " room integer, FOREIGN KEY (room) REFERENCES ").
            append(DB_ROOM).append("(id));");
    return q.exec(query);
}

bool DBManager::createRoomTable() {
    QSqlQuery q(m_db);
    QString query = QString("CREATE TABLE IF NOT EXISTS ").append(DB_ROOM).
            append(" (id integer PRIMARY KEY, title varchar(255));");
    return q.exec(query);
}


