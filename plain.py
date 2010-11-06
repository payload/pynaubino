import sys
from PyQt4.QtCore import *
from PyQt4.QtGui import *
from Naubino import Naubino

def main():
    #from Cute import Application, GraphicsScene, GraphicsView
    from Pig import Application, GraphicsScene, GraphicsView
    app = Application()

    scene = GraphicsScene()
    #naubino = Naubino(scene)
    view = GraphicsView(scene)
    
    sys.exit(app.exec_())

if __name__ == "__main__": main()