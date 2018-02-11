#include "category.h"

Category::Category()
{

}

QString& Category::id()
{
    return m_id;
}

void Category::setId(const QString &id)
{
    m_id = QString(id);
}

QString& Category::title()
{
    return m_title;
}

void Category::setTitle(const QString &title)
{
    m_title =QString(title);
}
