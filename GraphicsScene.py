from PyQt4.QtGui import QGraphicsScene

class GraphicsScene(QGraphicsScene):

    def __init__(self):
        QGraphicsScene.__init__(self)
        self.pointer = None
        self.items = []

    def mousePressEvent(self, event):
        if not self.pointer: return
        event.naubino_pointer = self.pointer
        QGraphicsScene.mousePressEvent(self, event)

    def mouseReleaseEvent(self, event):
        if not self.pointer: return
        event.naubino_pointer = self.pointer
        QGraphicsScene.mouseReleaseEvent(self, event)

    def mouseMoveEvent(self, event):
        if self.pointer:
            pos = event.scenePos()
            pos = pos.x(), pos.y()
            self.pointer.pos = pos
        QGraphicsScene.mouseMoveEvent(self, event)
        
    def add_item(self, *items):
        for x in items:
            if x not in self.items:
                self.addItem(x)

    def remove_item(self, *items):
        for x in items:
            if x in self.items:
                self.removeItem(x)