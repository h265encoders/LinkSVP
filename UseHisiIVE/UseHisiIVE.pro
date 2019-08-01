QT += core
QT -= gui

TARGET = UseHisiIVE
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

include(../build.pri)

SOURCES += main.cpp \
    Sample.cpp

HEADERS += \
    Sample.h

