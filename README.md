# Naubino - Work in Progress

An awesome 2D game with colors, basic physics and cycle tests in an undirected graph.

`pynaubino` is the multi front-end version of Naubino. It exists for fun.
As of some time I only maintain the Kivy version.
This is still a work in progress and not a complete game,
 but a fun experiment.

See also
* [ naubino.js ]( http://naubino.de/ ) for a somewhat polished HTML5 Canvas version of Naubino.
* [ Naubino ]( http://www.mmt.inf.tu-dresden.de/Lehre/Sommersemester_10/PMI/ergebnisse/gruppe2/index.html )
  for a polished Flash version and also the first public version of the game.

Run `naubino`.
In older versions you can also choose between front-ends.
Run with `naubino avg` or with `naubino` to see all possible front-ends.

## Dependencies

* Python 2.7 > https://python.org/
* pymunk 1.0.0 https://code.google.com/p/pymunk/
 * chipmunk 5.3.2
* [ Kivy 1.9.0 ]( https://kivy.org ) (fun!)

* or for historians you can search in the branchs and try one of the following:
 * [ PyQt4 ]( https://www.riverbankcomputing.co.uk/software/pyqt/intro ) (playable)
  * Qt 4.6 >
 * [ pygame ]( https://pygame.org/ ) 1.9 (not playable)
 * [ libavg ]( https://www.libavg.de ) 1.8 (playable)

## Ubuntu

    apt install build-essential python2.7 python-pip virtualenv libgstreamer1.0-dev libsdl2-dev libsdl2-ttf libsdl2-image libsdl2-mixer
    virtualenv --python=python2 .env
    source .env/bin/activate
    pip install -r requirements.txt
 
## Python 3
* try 2to3 and think of Python 3 enabling the dependencies if possible
* it worked once but is not tested in any way right now
* I didn't maintained it because libavg does not support Python 3
  and libavg was important at that time

## TODO
* size of screen handling and placing of objects - rethink, 600x400 is spammed on several places
* grep -RHn TODO --include=*py src # ;-)

## DEV NOTES
* in the old Qt variant use pyqtProperty(type, get, set) instead of @pyqtProperty(type)… this is needed for Py2 compatibility
