#-------------------------------------------------
#
# Project created by QtCreator 2011-08-10T22:53:47
#
#-------------------------------------------------

QT       += core gui sql

TARGET = ordersvi
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    accessreader.cpp \
    logindialog.cpp

HEADERS  += mainwindow.h \
    indicatorsmodel.h \
    accessreader.h \
    settingsmodel.h \
    logindialog.h

FORMS    += mainwindow.ui \
    logindialog.ui

RESOURCES += \
    ordersvi.qrc
