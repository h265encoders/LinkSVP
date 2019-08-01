QT += core
QT -= gui

TARGET = FaceDetect
CONFIG += console c++11
CONFIG -= app_bundle

TEMPLATE = app

include(../build.pri)

SOURCES += main.cpp \
    FaceDetect.cpp \
    MTCNN.cpp

HEADERS += \
    FaceDetect.h \
    MTCNN.h

