#-------------------------------------------------
#
# Project created by QtCreator 2010-08-22T00:48:05
#
#-------------------------------------------------

QT       += testlib

TARGET = tst_Naubino
CONFIG   += console
CONFIG   -= app_bundle

LIBS += -L../../../cutenaubino-build-desktop/bin -lcutenaubino -lBox2D

INCLUDEPATH += ../../src/

TEMPLATE = app

DESTDIR = bin
MOC_DIR = temp/moc
OBJECTS_DIR = temp/o

SOURCES += tst_Naubino.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
