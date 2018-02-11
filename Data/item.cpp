#include "item.h"

#include "category.h"
#include "shelf.h"

#include <QDate>

Item::Item(const QString &id, const QString& name, const QString& description, Category* category, QImage* picture)
    :m_id(id), m_name(name), m_description(description), m_category(category), m_picture(picture)
{
}

Item::~Item(){
    delete m_category;
    delete m_shelf;
    delete m_expirationDate;
    delete m_picture;
}

const QString Item::name()
{
    return m_name;
}

void Item::setName(const QString &name)
{
    m_name = QString(name);
}

const QString Item::description()
{
    return m_description;
}

void Item::setDescription(const QString &description)
{
    m_description = QString(description);
}

Category& Item::category()
{
    return *m_category;
}

void Item::setCategory(Category* category)
{
    m_category = category;
}

QImage* Item::picture()
{
    return m_picture;
}

void Item::setPicture(QImage *picture)
{
    m_picture = picture;
}

const QString& Item::id()
{
    return m_id;
}

void Item::setId(const QString &id)
{
    m_id = QString(id);
}

Shelf& Item::shelf()
{
    return *m_shelf;
}

void Item::setShelf(Shelf* shelf)
{
    m_shelf = shelf;
}


QString Item::getExpirationDateString() {
    if (m_expirationDate != nullptr) {
        m_expirationDate->toString(Qt::ISODate);
    }
    return "";
}

const QDate* Item::getExpirationDate() {
    return m_expirationDate;
}

void Item::setExpirationDate(const QString expirationDate) {
    QDate t = QDate::fromString(expirationDate, Qt::ISODate);
    this->setExpirationDate(t);
}

void Item::setExpirationDate(const QDate& expirationDate) {
    if (expirationDate.isNull() || !expirationDate.isValid()) {
        this->m_expirationDate = new QDate();
    } else {
        this->m_expirationDate = new QDate(expirationDate.year(),
                                           expirationDate.month(),
                                           expirationDate.day());
    }
}
