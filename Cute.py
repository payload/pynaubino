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
    @pyqtProperty(float)
    def pen_width(self): return self.__pen_width
    @pen_width.setter
    def pen_width(self, x):
        if self.__pen_width != x:
            self.__pen_width = x
            if x == 0: pen = QPen(Qt.NoPen)
            else: pen = QPen(self.brush, x)
            self.line.setPen(pen)
    
    def __init__(self, naubino, joint, layer = -2):
        line = QGraphicsLineItem()
        Cute.__init__(self, line)

        line.hide()
        line.setZValue(layer)
        self.brush = QBrush(QColor("black"))
        self.__pen_width = 4.0
        pen = QPen(self.brush, self.__pen_width)
        line.setPen(pen)
        self.line = line
        self.joint = joint
        self.naubino = naubino
        self.naubino.add_cute_joint(self)

    def update_object(self):
        self.line.show()
        a = self.joint.a.position
        b = self.joint.b.position
        self.line.setLine(a.x, a.y, b.x, b.y)

    def remove(self):
        self.naubino.remove_cute_joint(self)

    def remove_joint(self):
        ani = QPropertyAnimation(self, "pen_width")
        ani.setStartValue(self.pen_width)
        ani.setEndValue(0)
        ani.setDuration(500)
        ani.finished.connect(self.remove)
        ani.start()
        self.ani = ani

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
        ani.setStartValue(self.scale)
        ani.setEndValue(0)
        ani.setDuration(500)
        ani.finished.connect(self.remove)
        ani.start()
        self.ani = ani

    def select_naub(self, pointer):
        pass

    def deselect_naub(self, pointer):
        pass