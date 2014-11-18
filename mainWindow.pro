#-------------------------------------------------
#
# Project created by QtCreator 2014-07-05T18:46:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mainWindow
TEMPLATE = app

CONFIG +=c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    picgen.cpp \
    rangen.cpp \
    aes_ctr.cpp \
    recdia.cpp

HEADERS  += mainwindow.h \
    picgen.h \
    rangen.h \
    aes_ctr.h \
    recdia.h

FORMS    +=

LIBS += -lcryptopp
