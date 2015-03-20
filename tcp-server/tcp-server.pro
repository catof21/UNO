TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle

QT += network
QT += core

SOURCES += main.cpp \
    gameserver.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    gameserver.h

