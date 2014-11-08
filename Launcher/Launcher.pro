#-------------------------------------------------
#
# Project created by QtCreator 2014-10-31T19:09:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Launcher
TEMPLATE = app


SOURCES += main.cpp\
        edmmainwindow.cpp

HEADERS  += edmmainwindow.h

FORMS    += edmmainwindow.ui
QT += sql

SUBDIRS += \
    ../DbRegisterTool/DbRegisterTool.pro