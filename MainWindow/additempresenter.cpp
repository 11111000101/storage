#include "additempresenter.h"

#include <QDebug>
#include <QDate>

#include "Data/datamodel.h"
#include "additemview.h"

#include "Data/item.h"

#include "Data/shelf.h"

AddItemPresenter::AddItemPresenter(IItemView* addItemView, DataModel& dataModel)
    : m_dataModel(dataModel), m_addItemView(addItemView)
{
    this->setViewData();
    QObject::connect(&m_dataModel, SIGNAL(itemUpdatedOrInserted(QString)),
                     this, SIGNAL(itemUpdatedOrInserted(QString)));

    QObject::connect(m_addItemView, SIGNAL(roomSelectionChanged(QString)),
                     this, SLOT(onRoomSelectionChanged(QString)));

    QObject::connect(m_addItemView, SIGNAL(takePhoto()),
                     this, SIGNAL(takePhoto()));
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
    return this->m_addItemView->getWidget();
}

void AddItemPresenter::saveItem() {
//    QString id = m_addItemView->getID();
//    Category* c = m_addItemView->getCategory();
//    QString t = m_addItemView->getTitle();
//    QString d = m_addItemView->getDescription();
//    QDate e = m_addItemView->getExpirationDate();
//    QImage* i = m_addItemView->getImage();
//    Shelf* s = m_addItemView->getShelf();

//    m_dataModel.saveItem("", t, d, c, s, e, i);
}

void AddItemPresenter::showEditItem(QString itemId) {
    Item* i = m_dataModel.getItemById(itemId);
    this->m_addItemView->setCategories(m_dataModel.getAllCategories());
    this->m_addItemView->setRooms(m_dataModel.getAllRooms());
    this->m_addItemView->setShelves(m_dataModel.getAllShelves());
    if (i != nullptr) {
        this->m_addItemView->setCategory(i->category());
        this->m_addItemView->setDescription(i->description());
        this->m_addItemView->setExpirationDate(*i->getExpirationDate());
        this->m_addItemView->setPicture(i->picture());
        this->m_addItemView->setRoom(i->shelf()->room());
        this->m_addItemView->setShelf(i->shelf());
        this->m_addItemView->setTitle(i->name());
    } else {
        this->m_addItemView->setCategory(nullptr);
        this->m_addItemView->setDescription("");
        this->m_addItemView->setExpirationDate(QDate::currentDate());
        this->m_addItemView->setPicture(nullptr);
        this->m_addItemView->setRoom(nullptr);
        this->m_addItemView->setShelf(nullptr);
        this->m_addItemView->setTitle("");
    }
}

void AddItemPresenter::show() {
//    this->m_addItemView->reset();
//    this->setViewData();
    this->m_addItemView->show();
}

void AddItemPresenter::hide() {
    this->m_addItemView->hide();
}

void AddItemPresenter::onRoomSelectionChanged(QString roomId) {
    m_addItemView->setShelves(m_dataModel.getAllShelvesFromRoom(roomId));
}
