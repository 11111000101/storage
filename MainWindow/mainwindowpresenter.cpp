#include "mainwindowpresenter.hpp"

#include <QDebug>

#include "mainwindowview.hpp"
#include "Data/datamodel.h"

#include "Data/item.h"

MainWindowPresenter::MainWindowPresenter(IMainWindowView* view, DataModel& model)
    :IMainWindowPresenter(view, model)
{
}

void MainWindowPresenter::show() {
    this->m_view->show();
}

void MainWindowPresenter::hide() {
    this->m_view->hide();
}

QWidget* MainWindowPresenter::getWidget() {
    return m_view->getWidget();
}

void MainWindowPresenter::setUp() {
    QObject::connect(&m_model, SIGNAL(itemUpdatedOrInserted(QString)),
                     this, SLOT(onUpdatedItem(QString)));

    QList<Item*> items = m_model.getItems();
    while(!items.isEmpty()) {
        Item* t = items.takeFirst();
        m_view->addOrUpdateItem(*t);
        delete t;
    }
}

void MainWindowPresenter::onUpdatedItem(QString id) {
    qDebug() << "onUpdatedItem " << id;
    Item* i = m_model.getItemById(id);
    m_view->addOrUpdateItem(*i);
    delete i;
}

MainWindowPresenter::~MainWindowPresenter() {
    qDebug() << "~MainWindowPresenter";
    delete m_view;
    m_view = nullptr;
}
