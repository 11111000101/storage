#ifndef MAINWINDOWVIEW_HPP
#define MAINWINDOWVIEW_HPP

#include <QMap>
#include <QString>

#include "imainwindowview.hpp"

namespace Ui {
class MainViewForm;
}

class QWidget;
class QLayout;
class QGroupBox;
class QPushButton;

class Item;

class MainWindowView : public IMainWindowView
{
    Q_OBJECT

public:
    explicit MainWindowView(QWidget *parent = 0);
    ~MainWindowView();

    QWidget* getWidget();

public slots:
    virtual void addCategory(QString& category);
    virtual void addOrUpdateItem(Item& item);

    virtual void removeCategory(QString& category);
    virtual void removeItemFromCategory(QString& category, QString& item);

    virtual int getNofItemsInCategory(QString& category);

    virtual void show();
    virtual void hide();

    virtual void onItemBtnClicked(bool);

    void test(QString);

signals:
    void itemSelected(QString);

private:
    QWidget* m_widget;
    Ui::MainViewForm* ui;
    QLayout* m_placeholderLayout;
    QMap<QString, QGroupBox*> m_groupBoxes;
    QMap<QPushButton*, QString> m_itemMap;

    QGroupBox* getCategoryGroup(const QString& category);
};

#endif // MAINWINDOWVIEW_HPP
