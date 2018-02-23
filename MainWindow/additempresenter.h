#ifndef ADDITEMPRESENTER_H
#define ADDITEMPRESENTER_H

#include <QObject>

class AddItemModel;
class QWidget;
class DataModel;

class IItemView;

class AddItemPresenter : public QObject
{
    Q_OBJECT
public:
    AddItemPresenter(IItemView* addItemView, DataModel& addItemModel);
    ~AddItemPresenter();

    void show();
    void hide();
    QWidget* getWidget();
    void saveItem();

signals:
    void itemUpdatedOrInserted(const QString& id);
    void takePhoto();

public slots:
    void showEditItem(QString itemId);

private slots:
    void onRoomSelectionChanged(QString roomId);

private:
    DataModel& m_dataModel;
    IItemView* m_addItemView;

    void setViewData();
};

#endif // ADDITEMPRESENTER_H
