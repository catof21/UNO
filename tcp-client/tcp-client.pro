#-------------------------------------------------
#
# Project created by QtCreator 2015-03-06T14:01:25
#
#-------------------------------------------------

QT       += core
QT       += network
QT       -= gui

TARGET = tcp-client
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    cli_socket.cpp

HEADERS += \
    cli_socket.h
