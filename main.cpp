#include "MainWindow/mainwindowview.hpp"
#include <QApplication>

#include "application.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Application app;
    app.show();
    return a.exec();
}
