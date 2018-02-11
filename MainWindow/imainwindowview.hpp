#ifndef IMAINWINDOWVIEW_HPP
#define IMAINWINDOWVIEW_HPP

#include <QObject>

class QString;
class QWidget;
class Item;

class IMainWindowView : public QObject
{
public:
    virtual ~IMainWindowView() {}
    virtual void addCategory(QString& category) = 0;
    virtual void addOrUpdateItem(Item& item) = 0;

    virtual void removeCategory(QString& category) = 0;
    virtual void removeItemFromCategory(QString& category, QString& item) = 0;

    virtual int getNofItemsInCategory(QString& category) = 0;

    virtual void show() = 0;
    virtual void hide() = 0;

    virtual QWidget* getWidget() = 0;

signals:
    void itemChanged();
};

#endif // IMAINWINDOWVIEW_HPP
