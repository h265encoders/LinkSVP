QT += core
QT -= gui

TARGET = FaceRecognition
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

include(../build.pri)
include(../../libmaia-master/maia.pri)

SOURCES += main.cpp \
    Worker.cpp

HEADERS += \
    Worker.h

