include(../cutenaubino.pri)

TEMPLATE = lib
TARGET = cutenaubino
DESTDIR = $$LIBRARYPATH
SOURCES += *.cpp
HEADERS += ../include/*.h \
    Naubino2.h \
    Joints.h
