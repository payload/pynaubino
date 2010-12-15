# -*- coding: utf-8 -*-
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

    def get_pos(self): return self.group.pos()
    def set_pos(self, pos):
        self.group.setPos(pos)
        if self.pos_changed: self.pos_changed(pos)
    pos = pyqtProperty(QPointF, get_pos, set_pos)

    @property
    def radius(self): return self.__radius
    @radius.setter
    def radius(self, radius):
        if radius != self.__radius:
            self.__radius = radius
            rect = QRectF(-radius, -radius, radius*2, radius*2)
            self.shape.setRect(rect)

    def __init__(self, naubino, layer = 0, rect = False):
        Cute.__init__(self, naubino)
        self.__radius = 0
        self.pos_changed = None

        group = self.group = QGraphicsItemGroup()
        
        def mousePressEvent(event):
            if not hasattr(event, u"naubino_pointer"): return
            if event.button() == Qt.LeftButton:
                self.pressed.emit(event)
        group.mousePressEvent   = mousePressEvent

        def mouseReleaseEvent(event):
            if not hasattr(event, u"naubino_pointer"): return
            if event.button() == Qt.LeftButton:
                self.released.emit(event)
        group.mouseReleaseEvent = mouseReleaseEvent
        
        group.setZValue(layer)
        group.setAcceptHoverEvents(True)
        group.setAcceptTouchEvents(True)

        shape = self.shape = QGraphicsRectItem(group) if rect else QGraphicsEllipseItem(group)
        shape.setPen(QPen(Qt.NoPen))
        shape.setBrush(QColor(u"black"))
        shape.setRotation(5)

        text = self.text = QGraphicsTextItem(u"???", group)
        font = text.font()
        font.setBold(True)
        text.setFont(font)
        text.setDefaultTextColor(QColor(u"white"))

        naubino.scene.add_item(group)

class MenuButton(Button):
    def __init__(self, naubino, radius, fontsize, plaintext, cw, ch,
            layer = 0, rect = False):
        Button.__init__(self, naubino, layer = layer, rect = rect)

        self.radius = radius

        text = self.text
        font = text.font()
        font.setPixelSize(self.radius * fontsize)
        text.setFont(font)
        text.setPlainText(plaintext)

        rect = self.shape.boundingRect()
        pos = rect.topLeft()
        pos += QPointF(radius, radius)
        rect = text.boundingRect()
        w, h = rect.width(), rect.height()
        pos -= QPointF(cw*w, ch*h)
        text.setPos(pos)

class PlayButton(MenuButton):
    def __init__(self, naubino, layer = 0):
        MenuButton.__init__(self, naubino, 13, 1.8, u"▸", 0.43, 0.565,
            layer = layer)

class TutorialButton(MenuButton):
    def __init__(self, naubino, layer = 0):
        MenuButton.__init__(self, naubino, 13, 1.5, u"¿", 0.55, 0.5,
            layer = layer)

class HighscoreButton(MenuButton):
    def __init__(self, naubino, layer = 0):
        p = super(HighscoreButton, self)
        p.__init__(naubino, 15, 1.8, u"5", 0.53, 0.5,
            layer = layer, rect=True)
        self.__score = score = 0
        self.__shown_score = score
        self.set_score(score)
        
    @property
    def score(self): return self.__score
    @score.setter
    def score(self, score):
        if self.__score != score:
            self.__score = score
            ani = self.ani = QPropertyAnimation(self, u"shown_score")
            ani.setStartValue(self.shown_score)
            ani.setEndValue(score)
            ani.setDuration(1000)
            ani.start()
            
    def get_shown_score(self): return self.__shown_score
    def set_shown_score(self, score):
        if self.__shown_score != score:
            self.__shown_score = score
            self.set_score(score)
    shown_score = pyqtProperty(int, get_shown_score, set_shown_score)

    def set_score(self, score):
        self.text.setPlainText(unicode(score))
