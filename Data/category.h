#ifndef CATEGORY_H
#define CATEGORY_H

#include <QString>

class Category
{
public:
    Category();

    QString& id();
    void setId(const QString &id);

    QString& title();
    void setTitle(const QString &title);

private:
    QString m_id;
    QString m_title;
};

#endif // CATEGORY_H
