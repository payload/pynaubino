# -*- coding: utf-8 -*-
import sys
from PyQt4.QtCore import *
from PyQt4.QtGui import *
from Naubino import Naubino
from Menu import NaubinoMenu

def main():
    #TODO use getopts
    #TODO style change:
    #  from Cute import Application, Foo →
    #  import Cute as Application
    #  app.Foo
    argv = sys.argv
    if u"pig" in argv:
        from Pig import Application, GraphicsScene, GraphicsView
    else:
        from Cute import Application, GraphicsScene, GraphicsView

    app = Application()
    scene = GraphicsScene()
    app.scene = scene
    naubino = Naubino(app)
    view = GraphicsView(scene)

    e = app.exec_()
    sys.exit(e)

if __name__ == u"__main__": main()
