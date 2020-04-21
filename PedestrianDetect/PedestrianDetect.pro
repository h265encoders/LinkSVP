QT += core
QT -= gui

TARGET = PedestrianDetect
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

contains(DEFINES,HI3519A){
SOURCES += main.cpp
