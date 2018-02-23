#include "additemview.h"
#include "ui_additemview.h"

#include <QDebug>

#include "Data/category.h"
#include "Data/room.h"
#include "Data/shelf.h"

AddItemView::AddItemView(QWidget *parent) :
    ui(new Ui::AddItemView),
    m_widget(new QWidget(parent))
{
    ui->setupUi(m_widget);

    QObject::connect(ui->categoryComboBox, SIGNAL(currentIndexChanged(QString)),
                     this, SLOT(onCategorySelected(QString)));
    QObject::connect(ui->roomComboBox, SIGNAL(currentIndexChanged(int)),
                     this, SLOT(onRoomSelected(int)));
    QObject::connect(ui->storageComboBox, SIGNAL(currentIndexChanged(QString)),
                     this, SLOT(onStorageSelected(QString)));
    QObject::connect(ui->imagePlaceholderLbl, SIGNAL(clicked()),
                     this, SIGNAL(takePhoto()));
}

AddItemView::~AddItemView() {
    qDebug() << "~AddItemView";
    delete ui;
    delete m_widget;
}

/** ----------------------------------------------------------------------- **/

void AddItemView::setTitle(const QString &title) {
    this->ui->titleLineEdit->setText(title);
}

const QString& AddItemView::getTitle(){
    return ui->titleLineEdit->text();
}

void AddItemView::setDescription(const QString &description){
    this->ui->descriptionTextEdit->document()->setPlainText(description);
}

const QString& AddItemView::getDescription() {
    return ui->descriptionTextEdit->toPlainText();
}

void AddItemView::setCategory(Category* category){
    if (category != nullptr) {
        this->ui->categoryComboBox->setCurrentIndex(ui->categoryComboBox->findData(category->id()));
    } else {
        this->ui->categoryComboBox->setCurrentIndex(ui->categoryComboBox->findData(""));
    }
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

const QPixmap* AddItemView::getPicture() {
    return ui->imagePlaceholderLbl->pixmap();
}
void AddItemView::setPicture(QPixmap* picture) {
    if (picture != nullptr) {
        this->ui->imagePlaceholderLbl->setPixmap(*picture);
    } else {
        QPixmap p;
        this->ui->imagePlaceholderLbl->setPixmap(p);
    }
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
void AddItemView::setShelf(Shelf *shelf) {
    if (shelf != nullptr) {
        this->ui->storageComboBox->setCurrentIndex(this->ui->storageComboBox->findData(shelf->id()));
    } else {
        this->ui->storageComboBox->setCurrentIndex(this->ui->storageComboBox->findData(""));
    }
    this->ui->storageComboBox->update();
}

void AddItemView::setRoom(Room* room) {
    if (room == nullptr) {
        ui->roomComboBox->setCurrentIndex(ui->roomComboBox->findData(""));
    } else {
        ui->roomComboBox->setCurrentIndex(ui->roomComboBox->findData(room->id()));
    }
//    ui->roomComboBox->update();
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

void AddItemView::setExpirationDate(const QDate& expirationDate) {
    ui->expirationDateEdit->setDate(expirationDate);
}
const QDate& AddItemView::getExpirationDate(){
    return ui->expirationDateEdit->date();
}


/** ----------------------------------------------------------------------- **/

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

/** --------------------------- SLOTS ------------------------------------- **/

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

/** ----------------------------------------------------------------------- **/

void AddItemView::hide() {
    m_widget->hide();
}

void AddItemView::show() {
    m_widget->show();
}

void AddItemView::reset() {
    ui->categoryComboBox->clear();
    ui->customCategoryLineEdit->clear();
    ui->descriptionTextEdit->clear();
    ui->expirationDateEdit->clear();
    ui->storageComboBox->clear();
}

QWidget* AddItemView::getWidget() {
    return m_widget;
}

/** -------------------------------- private ------------------------------ **/

void AddItemView::setCustomCategoryVisible(bool visible) {
    this->ui->customCategoryLineEdit->setVisible(visible);
}

void AddItemView::setStorageLineVisible(bool visible) {
    this->ui->storageLineEdit->setVisible(visible);
}

void AddItemView::setRoomLineVisible(bool visible) {
    this->ui->roomLineEdit->setVisible(visible);
}
