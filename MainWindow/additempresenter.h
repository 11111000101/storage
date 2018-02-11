#ifndef ADDITEMPRESENTER_H
#define ADDITEMPRESENTER_H

#include <QObject>

class AddItemView;
class AddItemModel;
class QWidget;
class DataModel;



class AddItemPresenter : public QObject
{
    Q_OBJECT
public:
    AddItemPresenter(AddItemView* addItemView, DataModel& addItemModel);
    ~AddItemPresenter();

    void show();
    QWidget* getWidget();
    void saveItem();

signals:
    void itemUpdatedOrInserted(const QString& id);

private slots:
    void onRoomSelectionChanged(QString roomId);

private:
    DataModel& m_dataModel;
    AddItemView* m_addItemView;

    void setViewData();
};

#endif // ADDITEMPRESENTER_H
