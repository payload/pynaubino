#############################################################################
# Makefile for building: naubino2
# Generated by qmake (2.01a) (Qt 4.6.3) on: Mi. Aug 11 18:50:36 2010
# Project:  naubino2.pro
# Template: app
# Command: /usr/bin/qmake -unix -o Makefile naubino2.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -march=i686 -mtune=generic -O2 -pipe -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -march=i686 -mtune=generic -O2 -pipe -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt/mkspecs/linux-g++ -I. -I/usr/include/QtCore -I/usr/include/QtGui -I/usr/include -I. -I.
LINK          = g++
LFLAGS        = -Wl,-O1
LIBS          = $(SUBLIBS)  -L/usr/lib -lBox2D -lQtGui -L/usr/lib -L/usr/X11R6/lib -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = Joint.cpp \
		JointGraphics.cpp \
		main.cpp \
		Naub.cpp \
		NaubContext.cpp \
		NaubGraphics.cpp \
		NaubScene.cpp \
		NaubView.cpp \
		Vec.cpp moc_Joint.cpp \
		moc_JointGraphics.cpp \
		moc_NaubScene.cpp
OBJECTS       = Joint.o \
		JointGraphics.o \
		main.o \
		Naub.o \
		NaubContext.o \
		NaubGraphics.o \
		NaubScene.o \
		NaubView.o \
		Vec.o \
		moc_Joint.o \
		moc_JointGraphics.o \
		moc_NaubScene.o
DIST          = /usr/share/qt/mkspecs/common/g++.conf \
		/usr/share/qt/mkspecs/common/unix.conf \
		/usr/share/qt/mkspecs/common/linux.conf \
		/usr/share/qt/mkspecs/qconfig.pri \
		/usr/share/qt/mkspecs/features/qt_functions.prf \
		/usr/share/qt/mkspecs/features/qt_config.prf \
		/usr/share/qt/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt/mkspecs/features/default_pre.prf \
		/usr/share/qt/mkspecs/features/release.prf \
		/usr/share/qt/mkspecs/features/default_post.prf \
		/usr/share/qt/mkspecs/features/warn_on.prf \
		/usr/share/qt/mkspecs/features/qt.prf \
		/usr/share/qt/mkspecs/features/unix/thread.prf \
		/usr/share/qt/mkspecs/features/moc.prf \
		/usr/share/qt/mkspecs/features/resources.prf \
		/usr/share/qt/mkspecs/features/uic.prf \
		/usr/share/qt/mkspecs/features/yacc.prf \
		/usr/share/qt/mkspecs/features/lex.prf \
		/usr/share/qt/mkspecs/features/include_source_dir.prf \
		naubino2.pro
QMAKE_TARGET  = naubino2
DESTDIR       = 
TARGET        = naubino2

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: naubino2.pro  /usr/share/qt/mkspecs/linux-g++/qmake.conf /usr/share/qt/mkspecs/common/g++.conf \
		/usr/share/qt/mkspecs/common/unix.conf \
		/usr/share/qt/mkspecs/common/linux.conf \
		/usr/share/qt/mkspecs/qconfig.pri \
		/usr/share/qt/mkspecs/features/qt_functions.prf \
		/usr/share/qt/mkspecs/features/qt_config.prf \
		/usr/share/qt/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt/mkspecs/features/default_pre.prf \
		/usr/share/qt/mkspecs/features/release.prf \
		/usr/share/qt/mkspecs/features/default_post.prf \
		/usr/share/qt/mkspecs/features/warn_on.prf \
		/usr/share/qt/mkspecs/features/qt.prf \
		/usr/share/qt/mkspecs/features/unix/thread.prf \
		/usr/share/qt/mkspecs/features/moc.prf \
		/usr/share/qt/mkspecs/features/resources.prf \
		/usr/share/qt/mkspecs/features/uic.prf \
		/usr/share/qt/mkspecs/features/yacc.prf \
		/usr/share/qt/mkspecs/features/lex.prf \
		/usr/share/qt/mkspecs/features/include_source_dir.prf \
		/usr/lib/libQtGui.prl \
		/usr/lib/libQtCore.prl
	$(QMAKE) -unix -o Makefile naubino2.pro
/usr/share/qt/mkspecs/common/g++.conf:
/usr/share/qt/mkspecs/common/unix.conf:
/usr/share/qt/mkspecs/common/linux.conf:
/usr/share/qt/mkspecs/qconfig.pri:
/usr/share/qt/mkspecs/features/qt_functions.prf:
/usr/share/qt/mkspecs/features/qt_config.prf:
/usr/share/qt/mkspecs/features/exclusive_builds.prf:
/usr/share/qt/mkspecs/features/default_pre.prf:
/usr/share/qt/mkspecs/features/release.prf:
/usr/share/qt/mkspecs/features/default_post.prf:
/usr/share/qt/mkspecs/features/warn_on.prf:
/usr/share/qt/mkspecs/features/qt.prf:
/usr/share/qt/mkspecs/features/unix/thread.prf:
/usr/share/qt/mkspecs/features/moc.prf:
/usr/share/qt/mkspecs/features/resources.prf:
/usr/share/qt/mkspecs/features/uic.prf:
/usr/share/qt/mkspecs/features/yacc.prf:
/usr/share/qt/mkspecs/features/lex.prf:
/usr/share/qt/mkspecs/features/include_source_dir.prf:
/usr/lib/libQtGui.prl:
/usr/lib/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -unix -o Makefile naubino2.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/naubino21.0.0 || $(MKDIR) .tmp/naubino21.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/naubino21.0.0/ && $(COPY_FILE) --parents Joint.h JointGraphics.h Naub.h NaubContext.h NaubGraphics.h Naubino.h NaubScene.h NaubView.h Vec.h .tmp/naubino21.0.0/ && $(COPY_FILE) --parents Joint.cpp JointGraphics.cpp main.cpp Naub.cpp NaubContext.cpp NaubGraphics.cpp NaubScene.cpp NaubView.cpp Vec.cpp .tmp/naubino21.0.0/ && (cd `dirname .tmp/naubino21.0.0` && $(TAR) naubino21.0.0.tar naubino21.0.0 && $(COMPRESS) naubino21.0.0.tar) && $(MOVE) `dirname .tmp/naubino21.0.0`/naubino21.0.0.tar.gz . && $(DEL_FILE) -r .tmp/naubino21.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_Joint.cpp moc_JointGraphics.cpp moc_NaubScene.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_Joint.cpp moc_JointGraphics.cpp moc_NaubScene.cpp
moc_Joint.cpp: Joint.h
	/usr/bin/moc $(DEFINES) $(INCPATH) Joint.h -o moc_Joint.cpp

moc_JointGraphics.cpp: JointGraphics.h
	/usr/bin/moc $(DEFINES) $(INCPATH) JointGraphics.h -o moc_JointGraphics.cpp

moc_NaubScene.cpp: Naub.h \
		Joint.h \
		Vec.h \
		NaubContext.h \
		NaubScene.h
	/usr/bin/moc $(DEFINES) $(INCPATH) NaubScene.h -o moc_NaubScene.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean 

####### Compile

Joint.o: Joint.cpp Joint.h \
		JointGraphics.h \
		Naub.h \
		Vec.h \
		NaubContext.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Joint.o Joint.cpp

JointGraphics.o: JointGraphics.cpp JointGraphics.h \
		Joint.h \
		Naub.h \
		Vec.h \
		NaubContext.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o JointGraphics.o JointGraphics.cpp

main.o: main.cpp NaubScene.h \
		Naub.h \
		Joint.h \
		Vec.h \
		NaubContext.h \
		NaubView.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

Naub.o: Naub.cpp Naub.h \
		Joint.h \
		Vec.h \
		NaubContext.h \
		NaubGraphics.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Naub.o Naub.cpp

NaubContext.o: NaubContext.cpp NaubContext.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o NaubContext.o NaubContext.cpp

NaubGraphics.o: NaubGraphics.cpp NaubGraphics.h \
		Naub.h \
		Joint.h \
		Vec.h \
		NaubContext.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o NaubGraphics.o NaubGraphics.cpp

NaubScene.o: NaubScene.cpp NaubScene.h \
		Naub.h \
		Joint.h \
		Vec.h \
		NaubContext.h \
		NaubGraphics.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o NaubScene.o NaubScene.cpp

NaubView.o: NaubView.cpp NaubView.h \
		NaubScene.h \
		Naub.h \
		Joint.h \
		Vec.h \
		NaubContext.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o NaubView.o NaubView.cpp

Vec.o: Vec.cpp Vec.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Vec.o Vec.cpp

moc_Joint.o: moc_Joint.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_Joint.o moc_Joint.cpp

moc_JointGraphics.o: moc_JointGraphics.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_JointGraphics.o moc_JointGraphics.cpp

moc_NaubScene.o: moc_NaubScene.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_NaubScene.o moc_NaubScene.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

