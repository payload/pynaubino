import pymunk
from pymunk import Vec2d
from Cute import Cute, CuteNaub, CuteJoint
from Space import Space
from Pointer import Pointer
from PyQt4.QtCore import *
from PyQt4.QtGui import *
from utils import *
from Naub import Naub

class Button(Cute):
    pressed  = pyqtSignal(QGraphicsSceneMouseEvent)
    released = pyqtSignal(QGraphicsSceneMouseEvent)
    entered  = pyqtSignal(QGraphicsSceneHoverEvent)
    leaved   = pyqtSignal(QGraphicsSceneHoverEvent)

    @property
    def pos(self):
        pos = self.group.pos()
        pos = pos.x(), pos.y()
        return Vec2d(pos)
    @pos.setter
    def pos(self, pos):
        pos = Vec2d(pos)
        self.group.setPos(pos.x, pos.y)

    @property
    def radius(self): return self.__radius
    @radius.setter
    def radius(self, radius):
        if radius != self.__radius:
            self.__radius = radius
            rect = QRectF(-radius, -radius, radius*2, radius*2)
            self.elli.setRect(rect)

    def __init__(self, naubino, layer = 0, rect = False):
        self.naubino = naubino
        self.group = group = QGraphicsItemGroup()
        Cute.__init__(self, group)

        self.set_clickable(group, True)
        def mousePressEvent(event):
            if not hasattr(event, "naubino_pointer"): return
            if event.button() == Qt.LeftButton:
                self.pressed.emit(event)

        def mouseReleaseEvent(event):
            if not hasattr(event, "naubino_pointer"): return
            if event.button() == Qt.LeftButton:
                self.released.emit(event)

        def hoverEnterEvent(event):
            self.entered.emit(event)

        def hoverLeaveEvent(event):
            self.leaved.emit(event)

        group.mousePressEvent   = mousePressEvent
        group.mouseReleaseEvent = mouseReleaseEvent
        group.hoverEnterEvent   = hoverEnterEvent
        group.hoverLeaveEvent   = hoverLeaveEvent

        group.setZValue(layer)

        self.__radius = 0

        self.elli = elli = QGraphicsRectItem(group) if rect else QGraphicsEllipseItem(group)
        elli.setPen(QPen(Qt.NoPen))
        elli.setBrush(QColor("black"))
        elli.setRotation(5)

        self.text = text = QGraphicsTextItem("???", group)
        font = text.font()
        font.setBold(True)
        text.setFont(font)
        text.setDefaultTextColor(QColor("white"))

        naubino.add_cute(self)

class MenuButton(Button):
    def __init__(self, naubino, radius, fontsize, text, cw, ch,
            layer = 0, rect = False):
        Button.__init__(self, naubino, layer = layer, rect = rect)

        self.radius = radius

        font = self.text.font()
        font.setPixelSize(self.radius * fontsize)
        self.text.setFont(font)
        self.text.setPlainText(text)

        rect = self.elli.boundingRect()
        pos = Vec2d(rect.x(), rect.y())
        pos += Vec2d(radius, radius)
        rect = self.text.boundingRect()
        w, h = rect.width(), rect.height()
        pos -= Vec2d(cw*w, ch*h)
        self.text.setPos(pos.x, pos.y)

class PlayButton(MenuButton):
    def __init__(self, naubino, layer = 0):
        MenuButton.__init__(self, naubino, 15, 1.8, "▸", 0.43, 0.565,
            layer = layer)

class TutorialButton(Button):
    def __init__(self, naubino, layer = 0):
        MenuButton.__init__(self, naubino, 15, 1.5, "¿", 0.55, 0.5,
            layer = layer)

class HighscoreButton(Button):
    def __init__(self, naubino, layer = 0):
        MenuButton.__init__(self, naubino, 17, 1.8, "5", 0.53, 0.5,
            layer = layer, rect=True)
