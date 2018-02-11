#include "additempresenter.h"

#include <QDebug>

#include "Data/datamodel.h"
#include "additemview.h"

#include "Data/item.h"

#include "Data/shelf.h"

AddItemPresenter::AddItemPresenter(AddItemView* addItemView, DataModel& dataModel)
    : m_dataModel(dataModel), m_addItemView(addItemView)
{
    this->setViewData();
    QObject::connect(&m_dataModel, SIGNAL(itemUpdatedOrInserted(QString)),
                     this, SIGNAL(itemUpdatedOrInserted(QString)));

    QObject::connect(m_addItemView, SIGNAL(roomSelectionChanged(QString)),
                     this, SLOT(onRoomSelectionChanged(QString)));
}

AddItemPresenter::~AddItemPresenter() {
    qDebug() << "~AddItemPresenter";
    delete m_addItemView;
    m_addItemView = nullptr;
}

void AddItemPresenter::setViewData() {
    m_addItemView->setCategories(m_dataModel.getAllCategories());
    m_addItemView->setRooms(m_dataModel.getAllRooms());
    m_addItemView->setShelves(m_dataModel.getAllShelvesFromRoom(m_addItemView->getRoom()->id()));
}

QWidget* AddItemPresenter::getWidget() {
    return this->m_addItemView;
}

void AddItemPresenter::saveItem() {

    Category* c = m_addItemView->getCategory();
    QString t = m_addItemView->getTitle();
    QString d = m_addItemView->getDescription();
    QDate e = m_addItemView->getExpirationDate();
    QImage* i = m_addItemView->getImage();
    Shelf* s = m_addItemView->getShelf();

    m_dataModel.saveItem("", t, d, c, s, e, i);
}

void AddItemPresenter::show() {
    this->m_addItemView->reset();
    this->setViewData();
    this->m_addItemView->show();
}

void AddItemPresenter::onRoomSelectionChanged(QString roomId) {
    m_addItemView->setShelves(m_dataModel.getAllShelvesFromRoom(roomId));
}
