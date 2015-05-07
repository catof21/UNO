
QT       += core
QT       += network
QT       -= gui

TARGET = TCPServer
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    frameData.cpp \
    myserver.cpp \
    mythread.cpp \
    threadFrame.cpp \
    card.cpp \
    table.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    frameData.h \
    myserver.h \
    mythread.h \
    threadFrame.h \
    card.h \
    table.h

