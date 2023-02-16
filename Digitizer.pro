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
SOURCES += src/main.cpp\
    src/grid.cpp \
    src/mainwindow.cpp \
    src/myscaler.cpp \
    src/mypolyline.cpp

HEADERS  += src/mainwindow.h \
    src/grid.h \
    src/myscaler.h \
    src/mypolyline.h

FORMS    += mainwindow.ui\

CONFIG += C++11

RESOURCES += \
    Buttons.qrc
