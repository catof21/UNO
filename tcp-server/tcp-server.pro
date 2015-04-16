
QT       += core
QT       += network
QT       -= gui

TARGET = TCPServer
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    data.cpp \
    frameData.cpp \
    myserver.cpp \
    mythread.cpp \
    threadFrame.cpp \
    user.cpp \
    card.cpp \
    table.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    data.h \
    frameData.h \
    myserver.h \
    mythread.h \
    threadFrame.h \
    user.h \
    card.h \
    table.h

