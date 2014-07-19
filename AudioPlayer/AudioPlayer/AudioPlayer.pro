#-------------------------------------------------
#
# Project created by QtCreator 2014-07-12T13:32:21
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia
QT       += quickwidgets
QT += multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AudioPlayer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

RESOURCES += \
    appicons.qrc

OTHER_FILES += \
    rotationsquare.qml

win32: LIBS += -L$$PWD/../../../../../fmod/api/lib/ -lfmodex_vc

INCLUDEPATH += $$PWD/../../../../../fmod/api/inc
DEPENDPATH += $$PWD/../../../../../fmod/api/inc
