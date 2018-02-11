#ifndef IMAINWINDOWMODEL_HPP
#define IMAINWINDOWMODEL_HPP

#include <QObject>

class Item;

class IMainWindowModel : public QObject
{
public:
    virtual ~IMainWindowModel() {};
    virtual QList<Item*> getItems() = 0;

public slots:
    virtual void changeCategory(QString& itemId, QString& category) = 0;
    virtual void changeTitle(QString& itemId, QString& title) = 0;
    virtual void changeDescription(QString& itemId, QString& desc) = 0;
    virtual void changeImage(QString& itemId, QImage* image) = 0;
signals:
    virtual void signal_itemUpdated(Item* i) = 0;
};

Q_DECLARE_INTERFACE(IMainWindowModel, "de.storage")


#endif // IMAINWINDOWMODEL_HPP
