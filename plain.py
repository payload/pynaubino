import sys
from PyQt4.QtCore import *
from PyQt4.QtGui import *
from Naubino import Naubino
from Menu import NaubinoMenu

def main():
    #from Cute import Application, GraphicsScene, GraphicsView
    from Pig import Application, GraphicsScene, GraphicsView
    app = Application()

    scene = GraphicsScene()
    app.scene = scene
    naubino = Naubino(app)
    view = GraphicsView(scene)
    naubino.play()
    
    sys.exit(app.exec_())

if __name__ == "__main__": main()