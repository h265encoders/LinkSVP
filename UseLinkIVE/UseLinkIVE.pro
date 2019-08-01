QT += core
QT -= gui

TARGET = UseLinkIVE
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

include(../build.pri)

SOURCES += main.cpp \
    Sample.cpp

HEADERS += \
    Sample.h

