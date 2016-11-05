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
    preview.cpp \
    export.cpp \
    addframecommand.cpp \
    removeframecommand.cpp \
    duplicateframecommand.cpp \
    drawcommand.cpp \
    saveonclose.cpp \
    newproject.cpp \
    moveframecommand.cpp

HEADERS  += mainwindow.h \
    model.h \
    startup.h \
    preview.h \
    export.h \
    addframecommand.h \
    removeframecommand.h \
    duplicateframecommand.h \
    drawcommand.h \
    saveonclose.h \
    newproject.h \
    moveframecommand.h

FORMS    += mainwindow.ui \
    startup.ui \
    preview.ui \
    export.ui \
    newproject.ui \
    saveonclose.ui

RESOURCES += \
    icons/icons.qrc \
    qdarkstyle/style.qrc

DISTFILES +=
