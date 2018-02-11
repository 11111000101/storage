#ifndef ITEM_H
#define ITEM_H

#include <QString>
#include <QImage>


class Category;
class Shelf;
class QDate;

class Item
{
public:
    Item(const QString& id, const QString& name, const QString& description,
         Category* category, QImage* picture = 0);
    ~Item();
    const QString name();
    void setName(const QString &name);

    const QString description();
    void setDescription(const QString &description);

    Category& category();
    void setCategory(Category* category);

    QImage *picture();
    void setPicture(QImage *picture);

    const QString& id();
    void setId(const QString &id);

    Shelf& shelf();
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
    QImage* m_picture;
    QDate* m_expirationDate = nullptr;
};

#endif // ITEM_H
