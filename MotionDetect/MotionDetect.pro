QT += core
QT -= gui

TARGET = MotionDetect
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

include(../build.pri)

SOURCES += main.cpp \
    MotionDetect.cpp

HEADERS += \
    MotionDetect.h

