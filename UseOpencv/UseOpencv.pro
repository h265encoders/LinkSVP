QT += core
QT -= gui

TARGET = UseOpencv
CONFIG += console c++11
CONFIG -= app_bundle

TEMPLATE = app

include(../build.pri)

SOURCES += main.cpp \
    Sample.cpp

HEADERS += \
    Sample.h

