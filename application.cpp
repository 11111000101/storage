#include "application.h"

#include "ui_mainwindow.h"

#include "MainWindow/imainwindowview.hpp"
#include "MainWindow/imainwindowmodel.hpp"
#include "MainWindow/imainwindowpresenter.hpp"

#include "MainWindow/mainwindowview.hpp"
#include "MainWindow/mainwindowmodel.hpp"
#include "MainWindow/mainwindowpresenter.hpp"

#include "MainWindow/additemview.h"
#include "MainWindow/additemmodel.h"
#include "MainWindow/additempresenter.h"

#include "Data/dbmanager.h"
#include "MainWindow/CameraView.hpp"

#include <QVBoxLayout>
#include <QGroupBox>
#include <QSpacerItem>
#include <QDebug>

Application::Application(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), m_dataModel(new DBManager(QString("./db.sqlite")))
{
    ui->setupUi(this);

    setNewLayout();

    m_presenter = new MainWindowPresenter(new MainWindowView(), m_dataModel);
    m_cameraView = new CameraView();

    QLayoutItem* spacer = ui->placeholder->layout()->takeAt(ui->placeholder->layout()->count()-1);
    ui->placeholder->layout()->addWidget(m_presenter->getWidget());
    ui->placeholder->layout()->addItem(spacer);
    m_presenter->setUp();

    AddItemView* addItemView = new AddItemView();
    m_addItemPresenter = new AddItemPresenter(addItemView, m_dataModel);

    // return to default view
    QObject::connect(ui->mainBtn, SIGNAL(clicked(bool)),
                     this, SLOT(onMainBtnClicked()));

    // show addItemView
    QObject::connect(ui->pushButton, SIGNAL(clicked(bool)),
                     this, SLOT(onPushButtonClicked()));

    QObject::connect(m_addItemPresenter, SIGNAL(takePhoto()),
                     this, SLOT(showTakePhoto()));
//    QObject::connect(this->m_addItemPresenter, SIGNAL(itemUpdatedOrInserted(QString)),
//                     this->m_presenter, SLOT(onUpdatedItem(QString)));
}

Application::~Application() {
    delete this->m_presenter;
    delete this->ui;
    delete this->m_addItemPresenter;
}

void Application::onPushButtonClicked() {
    switch (this->state) {
    case CurrentState::StateMain:
        m_presenter->hide();
        showAddItemView();
        this->setPushButtonLabel("Save");
        this->state = CurrentState::StateAddItemView;
        break;
    case CurrentState::StateAddItemView:
        m_addItemPresenter->saveItem();
        ui->placeholder->layout()->removeWidget(m_addItemPresenter->getWidget());
        m_addItemPresenter->hide();
        showMainView();
        this->setPushButtonLabel("Add");
        this->state = CurrentState::StateMain;
    default:
        break;
    }
}

void Application::onMainBtnClicked() {
    switch (this->state) {
    case CurrentState::StateMain:
        break;
    case CurrentState::StateAddItemView:
        this->setPushButtonLabel("Add");
        ui->placeholder->layout()->removeWidget(m_addItemPresenter->getWidget());
        m_addItemPresenter->hide();
        this->showMainView();
        this->state = CurrentState::StateMain;
        break;
    default:
        break;
    }
}

void Application::showTakePhoto() {
    qDebug() << "showTakePhoto";
    this->state = CurrentState::StateTakePhoto;
    ui->placeholder->layout()->removeWidget(m_addItemPresenter->getWidget());
    m_addItemPresenter->hide();
    ui->placeholder->layout()->addWidget(m_cameraView);
}

void Application::showAddItemView() {
    QLayoutItem* spacer = ui->placeholder->layout()->takeAt(ui->placeholder->layout()->count()-1);
    ui->placeholder->layout()->addWidget(m_addItemPresenter->getWidget());
    ui->placeholder->layout()->addItem(spacer);
    m_addItemPresenter->showEditItem("");
    m_addItemPresenter->show();
}

void Application::showMainView() {
    QLayoutItem* spacer = ui->placeholder->layout()->takeAt(ui->placeholder->layout()->count()-1);
    ui->placeholder->layout()->addWidget(m_presenter->getWidget());
    ui->placeholder->layout()->addItem(spacer);
    m_presenter->show();
}

void Application::setPushButtonLabel(const QString& label) {
    ui->pushButton->setText(label);
}

void Application::setNewLayout() {
    ui->placeholder->setLayout(new QVBoxLayout());
    QSpacerItem* spacer = new QSpacerItem(1,1, QSizePolicy::Fixed, QSizePolicy::Expanding);
    ui->placeholder->layout()->addItem(spacer);
}


