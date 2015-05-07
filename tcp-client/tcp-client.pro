#-------------------------------------------------
#
# Project created by QtCreator 2015-03-06T14:01:25
#
#-------------------------------------------------

QT       += core
QT       += network
QT       += gui

TARGET = tcp-client


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app


SOURCES += main.cpp \
    cli_socket.cpp \
    startdialog.cpp \
    mainwindow.cpp \
    card.cpp \
    table.cpp

HEADERS += \
    startdialog.h \
    mainwindow.h \
    card.h \
    table.h

FORMS += \
    mainwindow.ui \
    startdialog.ui
