import sys
from PyQt4.QtCore import *
from PyQt4.QtGui import *
from Naubino import Naubino
from GraphicsScene import GraphicsScene

def main():
    app = QApplication([])

    naubino = Naubino()
    scene = GraphicsScene(naubino.pointer)
    naubino.parent = scene

    frame = QFrame()
    frame.setGeometry(0, 0, 600, 400)

    view = QGraphicsView(frame)
    view.setGeometry(0, 0, 600, 400)
    view.setSceneRect(-290, -190, 580, 380)
    view.setScene(scene)
    #view.setRenderHints(QPainter.Antialiasing)

    timer = QTimer()
    timer.setInterval(50)
    timer.timeout.connect(lambda: naubino.step(1.0 / timer.interval()))

    view.show()
    frame.show()
    timer.start()
    naubino.play()
    
    sys.exit(app.exec_())

if __name__ == "__main__": main()