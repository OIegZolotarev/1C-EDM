#-------------------------------------------------
#
# Project created by QtCreator 2014-10-31T21:04:56
#
#-------------------------------------------------

QT       += core gui
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DbRegisterTool
TEMPLATE = app


SOURCES += main.cpp\
        dbregtoolwindow.cpp \
    ../Common/databaseadapter.cpp \
    addclientprojectdialog.cpp

HEADERS  += dbregtoolwindow.h \
    ../Common/databaseadapter.h \
    addclientprojectdialog.h

FORMS    += \
    addClientProjectDialog.ui \
    addclientprojectdialog.ui \
    DbRegToolWindow.ui

