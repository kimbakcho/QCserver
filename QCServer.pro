#-------------------------------------------------
#
# Project created by QtCreator 2016-05-30T22:15:48
#
#-------------------------------------------------

QT       += core gui network ftp

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QCServer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mslotitem.cpp

HEADERS  += mainwindow.h \
    mslotitem.h

FORMS    += mainwindow.ui

RESOURCES += \
    Res.qrc
