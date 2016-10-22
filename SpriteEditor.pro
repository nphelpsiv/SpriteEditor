#-------------------------------------------------
#
# Project created by QtCreator 2016-10-21T12:13:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SpriteEditor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    model.cpp \
    startup.cpp \
    preview.cpp

HEADERS  += mainwindow.h \
    model.h \
    startup.h \
    preview.h

FORMS    += mainwindow.ui \
    startup.ui \
    preview.ui
