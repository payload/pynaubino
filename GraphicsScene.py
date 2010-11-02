from PyQt4.QtGui import QGraphicsScene

class GraphicsScene(QGraphicsScene):

    def __init__(self, pointer):
        QGraphicsScene.__init__(self)
        self.pointer = pointer

    def mousePressEvent(self, event):
        event.naubino_pointer = self.pointer
        QGraphicsScene.mousePressEvent(self, event)

    def mouseReleaseEvent(self, event):
        event.naubino_pointer = self.pointer
        QGraphicsScene.mouseReleaseEvent(self, event)

    def mouseMoveEvent(self, event):
        pos = event.scenePos()
        pos = pos.x(), pos.y()
        self.pointer.pos = pos
        QGraphicsScene.mouseMoveEvent(self, event)
        
    def addCute(self, cute):
        for x in cute.graphics:
            self.addItem(x)

    def removeCute(self, cute):
        for x in cute.graphics:
            self.removeItem(x)