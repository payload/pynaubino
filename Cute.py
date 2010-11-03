from PyQt4.QtCore import *
from PyQt4.QtGui import *
import random

class Cute(QObject):
    def __init__(self, *graphics):
        QObject.__init__(self)
        self.graphics = graphics

    def set_clickable(self, graphic, clickable):
        graphic.setAcceptHoverEvents(clickable)
        graphic.setAcceptTouchEvents(clickable)

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
        Cute.__init__(self)
        self.joint = joint
        self.naubino = naubino

        line = self.line = QGraphicsLineItem()
        line.hide()
        line.setZValue(layer)
        
        brush = self.brush = QBrush(QColor("black"))
        pen_width = self.__pen_width = 4.0
        pen = QPen(brush, pen_width)
        line.setPen(pen)

        self.naubino.add_cute_joint(self)
        self.naubino.add_item(line)

    def update_object(self):
        self.line.show()
        a = self.joint.a.position
        b = self.joint.b.position
        self.line.setLine(a.x, a.y, b.x, b.y)

    def remove(self):
        self.naubino.remove_cute_joint(self)
        self.naubino.remove_item(self.line)

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
        info = QGraphicsItemGroup()
        Cute.__init__(self, elli, info)

        def mousePressEvent(event):
            if not hasattr(event, "naubino_pointer"): return
            if event.button() == Qt.LeftButton:
                self.naub.select(event.naubino_pointer)
            if event.button() == Qt.RightButton:
                self.info_show()

        def mouseReleaseEvent(event):
            if not hasattr(event, "naubino_pointer"): return
            if event.button() == Qt.LeftButton:
                self.naub.deselect(event.naubino_pointer)
            if event.button() == Qt.RightButton:
                self.info_hide()

        elli.mousePressEvent = mousePressEvent
        elli.mouseReleaseEvent = mouseReleaseEvent

        self.set_clickable(info, False)
        info.hide()
        info.setZValue(layer+1)
        self.info = info

        info_bg = QGraphicsRectItem(self.info)
        info_bg.setBrush(QColor("white"))
        self.info_bg = info_bg
        self.info_text = QGraphicsTextItem("info", self.info)

        self.set_clickable(elli, True)
        elli.hide()
        elli.setZValue(layer)
        elli.setRect(-15, -15, 30, 30)
        elli.setPen(QPen(Qt.NoPen))
        self.elli = elli
        
        self.color = None
        self.naub = naub
        self.select = None
        self.deselect = None
        self.naubino = naubino
        self.update_object()
        self.naubino.add_cute_naub(self)

    def update_object(self):
        naub = self.naub
        pos = naub.body.position
        
        self.elli.setPos(pos.x, pos.y)
        self.elli.show()
        
        if self.info.isVisible():
            self.update_info()
            
        if naub.color != self.color:
            self.color = naub.color
            self.elli.setBrush(QBrush(self.color))

    def update_info(self):
        text = "links: "+ str(len(self.naub.naubs_joints))
        self.info_text.setPlainText(text)

        self.info_bg.setRect(self.info_text.boundingRect())

        pos = self.elli.pos()
        rect = self.elli.rect()
        w = rect.width()
        x = pos.x() + w*0.6
        y = pos.y()
        self.info.setPos(x, y)

    def info_show(self):
        self.update_info()
        self.info.show()

    def info_hide(self):
        self.info.hide()

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