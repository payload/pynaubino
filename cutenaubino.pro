#-------------------------------------------------
#
# Project created by QtCreator 2010-08-11T21:20:12
#
#-------------------------------------------------

QT       += core gui

TARGET = cutenaubino
TEMPLATE = app
LIBS += -lBox2D


SOURCES += main.cpp \
    Scene.cpp \
    View.cpp \
    QNaub.cpp \
    Naubino.cpp \
    Naub.cpp \
    Vec.cpp \
    Joint.cpp \
    QJoint.cpp \
    Pointer.cpp \
    Qb2DebugDraw.cpp \
    NaubinoContactListener.cpp \
    Event.cpp \
    MergeWithEvent.cpp \
    Cycler.cpp \
    Scorer.cpp

HEADERS  += \
    Scene.h \
    View.h \
    QNaub.h \
    Naubino.h \
    Naub.h \
    Vec.h \
    Joint.h \
    QJoint.h \
    Pointer.h \
    Qb2DebugDraw.h \
    NaubinoContactListener.h \
    Event.h \
    MergeWithEvent.h \
    Cycler.h \
    Scorer.h

FORMS    +=
