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
    logindialog.cpp \
    settingsview.cpp \
    src/nightcharts.cpp

HEADERS  += mainwindow.h \
    indicatorsmodel.h \
    accessreader.h \
    settingsmodel.h \
    logindialog.h \
    settingsview.h \
    src/nightcharts.h

FORMS    += mainwindow.ui \
    logindialog.ui \
    settingsview.ui

RESOURCES += \
    ordersvi.qrc
