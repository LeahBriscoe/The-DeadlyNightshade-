#-------------------------------------------------
#
# Project created by QtCreator 2015-05-23T23:46:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TheDeadlyNightshade
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    myplant.cpp \
    enemy.cpp \
    terpene.cpp \
    gameboard.cpp \
    insect.cpp \
    virus.cpp \
    instructions.cpp \
    lcdnumber.cpp

HEADERS  += mainwindow.h \
    myplant.h \
    terpene.h \
    enemy.h \
    gameboard.h \
    insect.h \
    virus.h \
    instructions.h \
    lcdnumber.h \
    documentation.h

FORMS    += mainwindow.ui \
    instructions.ui
QMAKE_CXXFLAGS += -std=c++11

CONFIG += c++11

RESOURCES += \
    images.qrc

DISTFILES +=
