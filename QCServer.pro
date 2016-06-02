#-------------------------------------------------
#
# Project created by QtCreator 2016-05-30T22:15:48
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QCServer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mslotitem.cpp \
    serversetform.cpp

HEADERS  += mainwindow.h \
    mslotitem.h \
    serversetform.h

FORMS    += mainwindow.ui \
    serversetform.ui

RESOURCES += \
    Res.qrc
