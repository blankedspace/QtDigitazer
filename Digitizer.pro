#-------------------------------------------------
#
# Project created by QtCreator 2022-10-07T15:13:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Digitizer
TEMPLATE = app

INCLUDEPATH += $$PWD/src
INCLUDEPATH += $$PWD/src/DrawableItems
SOURCES += src/main.cpp\
    src/DrawableItems/dgzgrid.cpp \
    src/datamanager.cpp \
    src/dgzpolyline.cpp \
    src/dgzscaler.cpp \
    src/drawablewindow.cpp \
    src/startwindow.cpp

HEADERS  += \
    src/DrawableItems/dgzgrid.h \
    src/datamanager.h \
    src/dgzpolyline.h \
    src/dgzscaler.h \
    src/drawablewindow.h \
    src/startwindow.h \

FORMS    += mainwindow.ui\

CONFIG += C++11

RESOURCES += \
    Buttons.qrc
