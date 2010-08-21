#-------------------------------------------------
#
# Project created by QtCreator 2010-08-11T21:20:12
#
#-------------------------------------------------

QT       += core gui

TARGET = cutenaubino
TEMPLATE = lib
LIBS += -lBox2D

SOURCES += *.cpp
HEADERS  += *.h

DESTDIR = bin
MOC_DIR = temp/moc
OBJECTS_DIR = temp/o
CONFIG += staticlib
