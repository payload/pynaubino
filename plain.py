import sys
from PyQt4.QtCore import *
from PyQt4.QtGui import *
from Naubino import Naubino
from GraphicsScene import GraphicsScene

def main():
    app = QApplication([])

    scene = GraphicsScene()
    naubino = Naubino(scene)
    scene.pointer = naubino.pointer

    frame = QFrame()
    frame.setGeometry(0, 0, 600, 400)

    view = QGraphicsView(frame)
    view.setGeometry(0, 0, 600, 400)
    view.setSceneRect(-290, -190, 580, 380)
    view.setScene(scene)
    view.setRenderHints(QPainter.Antialiasing)

    view.show()
    frame.show()
    
    sys.exit(app.exec_())

if __name__ == "__main__": main()