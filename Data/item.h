#ifndef ITEM_H
#define ITEM_H

#include <QString>


class Category;
class Shelf;
class QDate;
class QPixmap;

class Item
{
public:
    Item(const QString& id, const QString& name, const QString& description,
         Category* category, QPixmap* picture = 0);
    ~Item();
    const QString name();
    void setName(const QString &name);

    const QString description();
    void setDescription(const QString &description);

    Category* category();
    void setCategory(Category* category);

    QPixmap *picture();
    void setPicture(QPixmap *picture);

    const QString& id();
    void setId(const QString &id);

    Shelf* shelf();
    void setShelf(Shelf* shelf);

    QString getExpirationDateString();
    const QDate* getExpirationDate();

    void setExpirationDate(const QString expirationDate);
    void setExpirationDate(const QDate& expirationDate);

private:
    QString m_id;
    QString m_name;
    QString m_description;
    Category* m_category;
    Shelf* m_shelf;
    QPixmap* m_picture;
    QDate* m_expirationDate = nullptr;
};

#endif // ITEM_H
