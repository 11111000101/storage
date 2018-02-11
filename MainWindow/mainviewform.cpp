#include "mainviewform.h"
#include "ui_mainviewform.h"

#include <QDebug>

MainViewForm::MainViewForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainViewForm)
{
    ui->setupUi(this);
}

MainViewForm::~MainViewForm()
{
    qDebug() << "~MainViewForm";
    delete ui;
}
