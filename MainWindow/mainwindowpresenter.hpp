#ifndef MAINWINDOWPRESENTER_HPP
#define MAINWINDOWPRESENTER_HPP

#include "imainwindowpresenter.hpp"

#include <QObject>

class DataModel;
class IMainWindowView;
class Item;

class MainWindowPresenter : public QObject, public IMainWindowPresenter
{
    Q_OBJECT
public:
    explicit MainWindowPresenter(IMainWindowView* view, DataModel& model);
    virtual void setUp();
    virtual void show();
    virtual void hide();
    virtual QWidget* getWidget();
    virtual ~MainWindowPresenter();

public slots:
    void onUpdatedItem(QString id);
};

#endif // MAINWINDOWPRESENTER_HPP
