from Cute import Cute
from PyQt4.QtCore import *
from PyQt4.QtGui import *
import random
from utils import *

class CuteNaub(Cute):
    def get_scale(self): return self.elli.scale()
    def set_scale(self, x): self.elli.setScale(x)
    scale = pyqtProperty(float, get_scale, set_scale)

    def __init__(self, scene, naub, layer = -1):
        Cute.__init__(self, scene)
        self.naub = naub
        self.color = None
        self.select = None
        self.deselect = None

        elli = self.elli = QGraphicsEllipseItem()

        def mousePressEvent(event):
            if not hasattr(event, u"naubino_pointer"): return
            if event.button() == Qt.LeftButton:
                self.naub.select(event.naubino_pointer)
            if event.button() == Qt.RightButton:
                self.info_show()
        elli.mousePressEvent = mousePressEvent

        def mouseReleaseEvent(event):
            if not hasattr(event, u"naubino_pointer"): return
            if event.button() == Qt.LeftButton:
                self.naub.deselect(event.naubino_pointer)
            if event.button() == Qt.RightButton:
                self.info_hide()
        elli.mouseReleaseEvent = mouseReleaseEvent

        info = self.info = QGraphicsItemGroup()
        info.hide()
        info.setZValue(layer+1)

        info_bg = self.info_bg = QGraphicsRectItem(self.info)
        info_bg.setBrush(QColor(u"white"))
        self.info_text = QGraphicsTextItem(u"info", self.info)

        elli.setAcceptHoverEvents(True)
        elli.setAcceptTouchEvents(True)
        elli.hide()
        elli.setZValue(layer)
        r = naub.radius - 2
        elli.setRect(-r, -r, 2*r, 2*r)
        elli.setPen(QPen(Qt.NoPen))

        self.update_object()
        scene.add_item(elli, info)
        scene.add_update_object(self)

    def update_object(self):
        naub = self.naub
        elli = self.elli

        pos = naub.body.position

        elli.setPos(pos.x, pos.y)
        elli.show()

        if self.info.isVisible():
            self.update_info()

        if naub.color != self.color:
            color = self.color = naub.color
            elli.setBrush(QBrush(color))

    def update_info(self):
        text = u"links: "+ unicode(len(self.naub.naubs_joints))
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
        self.scene.remove_update_object(self)
        self.scene.remove_item(self.elli, self.info)

    def remove_naub(self):
        ani = self.ani = QPropertyAnimation(self, "scale")
        ani.setStartValue(self.scale)
        ani.setEndValue(0)
        ani.setDuration(500)
        ani.finished.connect(self.remove)
        ani.start()

    def select_naub(self, pointer):
        pass

    def deselect_naub(self, pointer):
        pass

