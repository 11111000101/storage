#include "additemview.h"
#include "ui_additemview.h"

#include <QDebug>

#include "Data/category.h"
#include "Data/room.h"
#include "Data/shelf.h"

AddItemView::AddItemView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddItemView)
{
    ui->setupUi(this);

    QObject::connect(ui->categoryComboBox, SIGNAL(activated(QString)),
                     this, SLOT(onCategorySelected(QString)));
    QObject::connect(ui->roomComboBox, SIGNAL(activated(int)),
                     this, SLOT(onRoomSelected(int)));
    QObject::connect(ui->storageComboBox, SIGNAL(activated(QString)),
                     this, SLOT(onStorageSelected(QString)));
}

void AddItemView::show() {
    QWidget::show();
}

void AddItemView::reset() {
    ui->categoryComboBox->clear();
    ui->customCategoryLineEdit->clear();
    ui->descriptionTextEdit->clear();
    ui->expirationDateEdit->clear();
    ui->storageComboBox->clear();
}

AddItemView::~AddItemView() {
    qDebug() << "~AddItemView";
    delete ui;
}

void AddItemView::setCategories(QList<Category*> categories) {
    this->ui->categoryComboBox->clear();
    foreach (Category* c, categories) {
        ui->categoryComboBox->addItem(c->title(), c->id());
    }
    while (!categories.isEmpty()) {
        delete categories.takeLast();
    }
    ui->categoryComboBox->addItem("Neuer Eintrag", "");
    setCustomCategoryVisible(ui->categoryComboBox->currentData().toString().isEmpty());
}

void AddItemView::setCustomCategoryVisible(bool visible) {
    this->ui->customCategoryLineEdit->setVisible(visible);
}

void AddItemView::setShelves(QList<Shelf*> shelves) {
    ui->storageComboBox->clear();
    foreach (Shelf* shelf, shelves) {
        ui->storageComboBox->addItem(shelf->title(), shelf->id());
    }
    while (!shelves.isEmpty()) {
        delete shelves.takeLast();
    }
    ui->storageComboBox->addItem("Neuer Eintrag", "");
    // if id is empty show line edit
    setStorageLineVisible(ui->storageComboBox->currentData().toString().isEmpty());
}

void AddItemView::setRooms(QList<Room*> rooms) {
    this->ui->roomComboBox->clear();
    foreach (Room* room, rooms) {
        ui->roomComboBox->addItem(room->title(), room->id());
    }
    while (!rooms.isEmpty()) {
        delete rooms.takeLast();
    }
    ui->roomComboBox->addItem("Neuer Eintrag", "");
    // if id is empty show line edit
    setRoomLineVisible(ui->roomComboBox->currentData().toString().isEmpty());
}

void AddItemView::setStorageLineVisible(bool visible) {
    this->ui->storageLineEdit->setVisible(visible);
}

void AddItemView::setRoomLineVisible(bool visible) {
    this->ui->roomLineEdit->setVisible(visible);
}


Category* AddItemView::getCategory() {
    Category* c = new Category();
    c->setId(ui->categoryComboBox->currentData().toString());
    if (c->id().isEmpty()) {
        c->setTitle(ui->customCategoryLineEdit->text());
    } else {
        c->setTitle(ui->categoryComboBox->currentText());
    }
    return c;
}

QString AddItemView::getExpirationDateString(){
    if (!ui->expirationDateEdit->date().isNull()) {
        return ui->expirationDateEdit->date().toString(Qt::ISODate);
    } else {
        return "";
    }
}

QDate AddItemView::getExpirationDate(){
    return ui->expirationDateEdit->date();
}

QString AddItemView::getTitle(){
    return ui->titleLineEdit->text();
}

QString AddItemView::getDescription() {
    return ui->descriptionTextEdit->toPlainText();
}

Room* AddItemView::getRoom(){
    Room* p = new Room;
    if (ui->roomComboBox->currentData().toString() == "") {
        p->setId("");
        p->setTitle(ui->roomLineEdit->text());
    } else {
        p->setId(ui->roomComboBox->currentData().toString());
        p->setTitle(ui->roomComboBox->currentText());
    }
    return p;
}

void AddItemView::onCategorySelected(QString category) {
    this->setCustomCategoryVisible(category == "Neuer Eintrag");
}

void AddItemView::onStorageSelected(QString storage) {
    this->setStorageLineVisible(storage == "Neuer Eintrag");
}

void AddItemView::onRoomSelected(int roomIndex) {
    this->setRoomLineVisible(ui->roomComboBox->itemText(roomIndex) == "Neuer Eintrag");
    qDebug() << "data: " << this->ui->roomComboBox->itemData(roomIndex).toString();
    qDebug() << "text: " << this->ui->roomComboBox->itemText(roomIndex);

    emit roomSelectionChanged(this->ui->roomComboBox->itemData(roomIndex).toString());
}

QImage* AddItemView::getImage(){
    return nullptr;
}

Shelf* AddItemView::getShelf() {
    Shelf* s = new Shelf();
    s->setRoom(this->getRoom());
    if (this->ui->storageComboBox->currentData().toString() == "") { // New entry
        s->setTitle(this->ui->storageLineEdit->text());
    } else {
        s->setTitle(this->ui->storageComboBox->currentText());
        s->setId(this->ui->storageComboBox->currentData().toString());
    }
    return s;
}

