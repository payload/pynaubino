include(../tests.pri)

QT       += testlib
TARGET = tst_Naubino
CONFIG   += qtestlib qt debug
CONFIG   -= app_bundle
SOURCES += tst_Naubino.cpp
TEMPLATE += app
LIBS += -lcutenaubino
