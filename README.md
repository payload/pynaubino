# Naubino

An awesome 2D game with colors, basic physics and cycle tests in an undirected graph.

`pynaubino` is the multi front-end version of Naubino. It exists for fun.

See also [ naubino.js ]( http://naubino.de/ ) for a somewhat polished HTML5 Canvas version of Naubino.

Run with `naubino avg` or with `naubino` to see all possible front-ends.

## Dependencies
* Python 2.6 > http://python.org/
* pymunk 1.0.0 http://code.google.com/p/pymunk/
 * chipmunk 5.3.2

* at least one of the following:
 * [ PyQt4 ]( https://www.riverbankcomputing.co.uk/software/pyqt/intro ) (playable)
  * Qt 4.6 >
 * [ pygame ]( https://pygame.org/ ) 1.9 (not playable)
 * [ libavg ]( https://www.libavg.de ) 1.8pre SVN (playable)

## Ubuntu

* pip install pymunk

* do at least one of the following:
 * `apt-get install python-qt4` (playable)
 * `apt-get install python-pygame`
 * https://www.libavg.de/site/projects/libavg/wiki/UbuntuSourceInstall
 
## Python 3
* try 2to3 and think of Python 3 enabling the dependencies if possible
* it worked once but is not tested in any way right now

## TODO
* size of screen handling and placing of objects - rethink, 600x400 is spammed on several places
* grep -Hn TODO `find . -name '*py'` # ;-)

## DEV NOTES
* use pyqtProperty(type, get, set) instead of @pyqtProperty(type)… this is needed for Py2 compatibility
