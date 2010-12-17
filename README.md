# Naubino

## Ubuntu

* apt-get install python-qt4
* easy_install pymunk

## Windows 32 and 64 bit

Poor person.

Install the following:
* http://www.python.org/ftp/python/2.7.1/python-2.7.1.msi
* http://www.riverbankcomputing.co.uk/static/Downloads/PyQt4/PyQt-Py2.7-gpl-4.8.1-1.exe
* http://code.google.com/p/pymunk/downloads/detail?name=pymunk-1.0.0.win32.exe&can=2&q=

If it throws an error noting that msvcr71.dll is missing:
* search the internet for msvcr71.dll
* download it
* move it into C:\Windows\

## Dependencies
* Python 2.6 > http://python.org/

* PyQt4 http://www.riverbankcomputing.co.uk/software/pyqt/intro
** Qt 4.6 >

* pymunk 1.0.0 http://code.google.com/p/pymunk/
** chipmunk 5.3.2

## Python 3
* try 2to3 and think of Python 3 enabling the dependencies
* it works if you know what you do

## TODO
* abstract Qt dependencies away and implement stubs in Pig (QColor, ???)
* size of screen handling and placing of objects - rethink, 600x400 is spammed on several places
* grep -Hn TODO `find . -name '*py'` # ;-)

## DEV NOTES
* use pyqtProperty(type, get, set) instead of @pyqtProperty(type)… this is needed for Py2 compatibility
