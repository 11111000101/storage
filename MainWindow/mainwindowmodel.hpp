#ifndef MAINWINDOWMODEL_HPP
#define MAINWINDOWMODEL_HPP

#include "imainwindowmodel.hpp"

class DBManager;

class MainWindowModel : public IMainWindowModel
{
    Q_OBJECT
    Q_INTERFACES(IMainWindowModel)
public:
    explicit MainWindowModel(DBManager* dbManager);
    virtual ~MainWindowModel();

    virtual QList<Item*> getItems();
public slots:
    virtual void changeCategory(QString& itemId, QString& category);
    virtual void changeTitle(QString& itemId, QString& title);
    virtual void changeDescription(QString& itemId, QString& desc);
    virtual void changeImage(QString& itemId, QImage* image);

signals:
    void signal_itemUpdated(Item* i);

private:
    DBManager* m_db;
};

#endif // MAINWINDOWMODEL_HPP
