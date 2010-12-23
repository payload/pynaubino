# -*- coding: utf-8 -*-
from Cute import Cute
from Pointer import Pointer
from PyQt4.QtCore import *
from PyQt4.QtGui import *

class Button(Cute):
    pressed  = pyqtSignal(QGraphicsSceneMouseEvent)
    released = pyqtSignal(QGraphicsSceneMouseEvent)

    # pos
    def get_pos(self): return self.group.pos()
    def set_pos(self, pos):
        if self.group.pos() == pos: return
        self.group.setPos(pos)
        if self.pos_changed: self.pos_changed(pos)
    pos = pyqtProperty(QPointF, get_pos, set_pos)

    # radius
    @property
    def radius(self): return self.__radius
    @radius.setter
    def radius(self, radius):
        if radius == self.__radius: return
        self.__radius = radius
        rect = QRectF(-radius, -radius, radius*2, radius*2)
        self.shape.setRect(rect)

    # color
    @property
    def color(self): return self.__color
    @color.setter
    def color(self, color):
        color = self.qcolor(color)
        if self.__color == color: return
        self.__color = color
        if not self.shape: return
        self.shape.setBrush(QBrush(color))

    # layer
    @property
    def layer(self): return self.group.zValue()
    @layer.setter
    def layer(self, layer):
        if self.layer == layer: return
        self.group.setZValue(layer)

    def __init__(self, scene):
        super(Button, self).__init__(scene)
        self.__radius = 0
        self.shape = None
        self.text = None
        self.pos_changed = None # callback, see pos property
        self.__color = None
        self.color = "black"

        # group config
        self.group = group = QGraphicsItemGroup()
        
        def mousePressEvent(event):
            if not hasattr(event, "naubino_pointer"): return
            if event.button() == Qt.LeftButton:
                self.pressed.emit(event)
        group.mousePressEvent   = mousePressEvent

        def mouseReleaseEvent(event):
            if not hasattr(event, "naubino_pointer"): return
            if event.button() == Qt.LeftButton:
                self.released.emit(event)
        group.mouseReleaseEvent = mouseReleaseEvent
        
        group.setAcceptHoverEvents(True)
        group.setAcceptTouchEvents(True)
        
        self.scene.add_item(group)
        
        # text config
        self.text = text = QGraphicsTextItem("???", self.group)
        font = text.font()
        font.setBold(True)
        text.setFont(font)
        text.setDefaultTextColor(self.qcolor("white"))

class MenuButton(Button):

    # plaintext
    @property
    def plaintext(self):
        return self.text.plainText()
    @plaintext.setter
    def plaintext(self, plaintext):
        self.text.setPlainText(plaintext)

    # fontsize
    @property
    def fontsize(self): return self.__fontsize
    @fontsize.setter
    def fontsize(self, fontsize):
        if self.__fontsize == fontsize: return
        font = self.text.font()
        font.setPixelSize(self.radius * fontsize)
        self.text.setFont(font)
        
    def text_center(self, *text_center):
        rect = self.shape.boundingRect()
        pos = rect.topLeft()
        pos += QPointF(self.radius, self.radius)
        rect = self.text.boundingRect()
        w, h = rect.width(), rect.height()
        cw, ch = text_center
        pos -= QPointF(cw*w, ch*h)
        self.text.setPos(pos)

    def __init__(self, scene):
        super(MenuButton, self).__init__(scene)
        self.__fontsize = 0

class CircleButton(MenuButton):
    def __init__(self, scene):
        super(CircleButton, self).__init__(scene)
        self.shape = shape = QGraphicsEllipseItem(self.group)
        shape.setPen(QPen(Qt.NoPen))
        shape.setBrush(self.color)
        shape.setZValue(-1)

class QuadButton(MenuButton):
    def __init__(self, scene):
        super(QuadButton, self).__init__(scene)
        self.shape = shape = QGraphicsRectItem(self.group)
        shape.setPen(QPen(Qt.NoPen))
        shape.setBrush(self.color)
        shape.setZValue(-1)

class PlayButton(CircleButton):
    def __init__(self, scene):
        super(PlayButton, self).__init__(scene)
        self.radius = 13
        self.fontsize = 1.8
        self.plaintext = u"▸"
        self.text_center(0.43, 0.565)
        self.color = "green"

class TutorialButton(CircleButton):
    def __init__(self, scene):
        super(TutorialButton, self).__init__(scene)
        self.radius = 13
        self.fontsize = 1.5
        self.plaintext = u"¿"
        self.text_center(0.55, 0.5)
        self.color = "pink"

class MuteButton(CircleButton):
    def __init__(self, scene):
        super(MuteButton, self).__init__(scene)
        self.radius = 13
        self.fontsize = 1.5
        self.plaintext = "M"
        self.text_center(0.51, 0.54)
        self.color = "purple"

class SettingsButton(CircleButton):
    def __init__(self, scene):
        super(SettingsButton, self).__init__(scene)
        self.radius = 13
        self.fontsize = 1.5
        self.plaintext = "S"
        self.text_center(0.52, 0.54)
        self.color = "blue"

class HighscoreButton(QuadButton):
    def __init__(self, scene):
        super(HighscoreButton, self).__init__(scene)
        self.shape.setRotation(15)
        self.radius = 15
        self.fontsize = 2.3
        self.plaintext = "0"
        self.text_center(0.46, 0.59)
        self.__score = 0
        self.__shown_score = 0
        self.set_score(0)
        self.color = "yellow"
        self.score_ani = ani = QPropertyAnimation(self, "shown_score")
        ani.setDuration(1000)
        
    # score
    @property
    def score(self): return self.__score
    @score.setter
    def score(self, score):
        if self.__score == score: return
        self.__score = score
        ani = self.score_ani
        ani.stop()
        ani.setStartValue(self.shown_score)
        ani.setEndValue(score)
        ani.start()
            
    # shown score
    def get_shown_score(self): return self.__shown_score
    def set_shown_score(self, score):
        if self.__shown_score == score: return
        self.__shown_score = score
        self.set_score(score)
    shown_score = pyqtProperty(int, get_shown_score, set_shown_score)

    def set_score(self, score):
        self.text.setPlainText(unicode(score))
