#-------------------------------------------------
#
# Project created by QtCreator 2018-01-17T11:02:11
#
#-------------------------------------------------

CONFIG += c++11


QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Storage
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    Data/dbmanager.cpp \
    Data/item.cpp \
    Data/shelf.cpp \
    application.cpp \
    MainWindow/imainwindowpresenter.cpp \
    MainWindow/mainwindowmodel.cpp \
    MainWindow/mainwindowpresenter.cpp \
    MainWindow/mainwindowview.cpp \
    Data/category.cpp \
    MainWindow/mainviewform.cpp \
    MainWindow/additemview.cpp \
    MainWindow/additemmodel.cpp \
    MainWindow/additempresenter.cpp \
    Data/datamodel.cpp \
    Data/room.cpp

HEADERS += \
    Data/dbmanager.h \
    Data/item.h \
    Data/shelf.h \
    Data/category.h \
    application.h \
    MainWindow/imainwindowview.hpp \
    MainWindow/imainwindowmodel.hpp \
    MainWindow/imainwindowpresenter.hpp \
    MainWindow/mainwindowview.hpp \
    MainWindow/mainwindowmodel.hpp \
    MainWindow/mainwindowpresenter.hpp \
    MainWindow/mainviewform.h \
    MainWindow/additemview.h \
    MainWindow/additemmodel.h \
    MainWindow/additempresenter.h \
    Data/datamodel.h \
    Data/room.h

FORMS += \
        MainWindow/mainwindow.ui \
    MainWindow/mainviewform.ui \
    MainWindow/additemview.ui

DISTFILES += \
    Valgrind.supp
