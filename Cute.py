from PyQt4.QtCore import *
from PyQt4.QtGui import *

class Cute(QObject):
    def __init__(self, graphics_item):
        QObject.__init__(self)
        self.graphics_item = graphics_item
        self.graphics_item.setAcceptHoverEvents(True)
        self.graphics_item.setAcceptTouchEvents(True)

    def update_object(self):
        pass

class CuteJoint(Cute):
    def __init__(self, joint, layer = -2):
        line = QGraphicsLineItem()
        Cute.__init__(self, line)

        line.hide()
        line.setZValue(layer)
        brush = QBrush(QColor("black"))
        pen = QPen(brush, 4.0)
        line.setPen(pen)
        self.line = line
        self.joint = joint

    def update_object(self):
        self.line.show()
        a = self.joint.a.position
        b = self.joint.b.position
        self.line.setLine(a.x, a.y, b.x, b.y)

class CuteNaub(Cute):
    @pyqtProperty(float)
    def scale(self): return self.elli.scale()
    @scale.setter
    def scale(self, x): self.elli.setScale(x)
    
    def __init__(self, naubino, naub, layer = -1):
        elli = QGraphicsEllipseItem()
        Cute.__init__(self, elli)

        def mousePressEvent(event):
            if hasattr(event, "naubino_pointer"):
                self.naub.select(event.naubino_pointer)

        def mouseReleaseEvent(event):
            if hasattr(event, "naubino_pointer"):
                self.naub.deselect(event.naubino_pointer)

        elli.mousePressEvent = mousePressEvent
        elli.mouseReleaseEvent = mouseReleaseEvent

        elli.hide()
        elli.setZValue(layer)
        elli.setRect(-15, -15, 30, 30)
        elli.setPen(QPen(Qt.NoPen))
        self.color = None
        self.elli = elli
        self.naub = naub
        self.select = None
        self.deselect = None
        self.naubino = naubino
        self.update_object()
        self.naubino.add_cute_naub(self)

    def update_object(self):
        self.elli.show()
        naub = self.naub
        pos = naub.body.position
        self.elli.setPos(pos.x, pos.y)
        if naub.color != self.color:
            self.color = naub.color
            self.elli.setBrush(QBrush(self.color))

    def remove(self):
        self.naubino.remove_cute_naub(self)

    def remove_naub(self):
        ani = QPropertyAnimation(self, "scale")
        ani.setStartValue(1)
        ani.setEndValue(0)
        ani.setDuration(500)
        ani.finished.connect(self.remove)
        ani.start()
        self.ani = ani

    def select_naub(self, pointer):
        pass

    def deselect_naub(self, pointer):
        pass