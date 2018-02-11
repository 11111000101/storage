#include "mainwindowview.hpp"
//#include "ui_mainwindow.h"
#include "ui_mainviewform.h"

#include "Data/dbmanager.h"
#include "Data/item.h"
#include "Data/category.h"

#include <QVBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QDebug>

MainWindowView::MainWindowView(QWidget *parent) :
    m_widget(new QWidget(parent)),
    ui(new Ui::MainViewForm)
{
    ui->setupUi(m_widget);
    m_placeholderLayout = new QGridLayout();
    ui->placeholder->setLayout(m_placeholderLayout);
}

QWidget* MainWindowView::getWidget() {
    return m_widget;
}

void MainWindowView::addOrUpdateItem(Item& item) {
    if (m_itemMap.values().contains(item.id())) { // update
        QPushButton* btn = m_itemMap.key(item.id());

    } else { // new Item
        QGroupBox* groupBox = getCategoryGroup(item.category().title());
        QPushButton* itemBtn = new QPushButton(item.name());

        QGridLayout* layout = ((QGridLayout*)groupBox->layout());
        layout->addWidget(itemBtn, layout->rowCount(), 1, 3, 1, Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
    }
}

QGroupBox* MainWindowView::getCategoryGroup(const QString& category) {
    if (m_groupBoxes.contains(category)) {
        return m_groupBoxes.find(category).value();
    } else {
        QGroupBox* groupBox = new QGroupBox();
        groupBox->setTitle(category);
        groupBox->setLayout(new QGridLayout());
        m_groupBoxes.insert(category, groupBox);
        QGridLayout* l = ((QGridLayout*)m_placeholderLayout);
        l->addWidget(groupBox, l->rowCount(), 1, 1, 1);
        return groupBox;
    }
}

void MainWindowView::addCategory(QString& category) {

}

//void MainWindowView::addItemToCategory(QString& category, QString& item) {

//}

void MainWindowView::removeCategory(QString& category) {

}

void MainWindowView::removeItemFromCategory(QString& category, QString& item) {

}

int MainWindowView::getNofItemsInCategory(QString& category) {

}

void MainWindowView::show() {
    ui->placeholder->show();
//    foreach(QGroupBox* child, this->ui->gridLayout->findChildren<QGroupBox*>("", Qt::FindChildrenRecursively)) {
//        child->show();
//    }
}

void MainWindowView::hide() {
    ui->placeholder->hide();
//    foreach(QGroupBox* child, this->ui->placeholder->findChildren<QGroupBox*>()) {
//        child->hide();
//        qDebug() << "hiding group box";
//    }
//    ui->placeholder->
}

MainWindowView::~MainWindowView() {
    qDebug() << "~MainWindowView";
    delete ui;
}
