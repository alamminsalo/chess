#-------------------------------------------------
#
# Project created by QtCreator 2014-11-20T23:09:06
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CHESS-APP
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gameview.cpp \
    ../../logic/src/board.cpp \
    ../../logic/src/piece.cpp

HEADERS  += mainwindow.h \
    gameview.h \
    ../../logic/src/board.h \
    ../../logic/src/piece.h

FORMS    += mainwindow.ui
