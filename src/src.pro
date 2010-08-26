include(../cutenaubino.pri)

TEMPLATE = lib
TARGET = cutenaubino
DESTDIR = $$LIBRARYPATH
SOURCES += *.cpp
HEADERS += ../include/*.h \
    ../include/QNaub.h
CONFIG -= app_bundle
CONFIG += qt debug
