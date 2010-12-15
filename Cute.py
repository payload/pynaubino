from Interfaces import *

from PyQt4.QtCore import *
from PyQt4.QtGui import *
import random
from utils import *
from CuteArena import CuteArena

class Cute(QObject):
    def __init__(self, scene):
        QObject.__init__(self)
        self.scene = scene

    def update_object(self):
        pass

class CuteJoint(Cute):
    def get_pen_width(self): return self.__pen_width
    def set_pen_width(self, x):
        if self.__pen_width != x:
            self.__pen_width = x
            if x == 0: pen = QPen(Qt.NoPen)
            else: pen = QPen(self.brush, x)
            self.line.setPen(pen)
    pen_width = pyqtProperty(float, get_pen_width, set_pen_width)

    def __init__(self, scene, a, b, layer = -2):
        Cute.__init__(self, scene)
        self.a = a
        self.b = b

        line = self.line = QGraphicsLineItem()
        line.hide()
        line.setZValue(layer)

        brush = self.brush = QBrush(QColor(u"black"))
        pen_width = self.__pen_width = 4.0
        pen = QPen(brush, pen_width)
        line.setPen(pen)

        scene.add_item(line)
        scene.add_update_object(self)

    def update_object(self):
        self.line.show()
        a = toVec2d(self.a.pos)
        b = toVec2d(self.b.pos)
        self.line.setLine(a.x, a.y, b.x, b.y)

    def remove(self):
        self.scene.remove_update_object(self)
        self.scene.remove_item(self.line)

    def remove_joint(self):
        ani = self.ani = QPropertyAnimation(self, u"pen_width")
        ani.setStartValue(self.pen_width)
        ani.setEndValue(0)
        ani.setDuration(500)
        ani.finished.connect(self.remove)
        ani.start()

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
        ani = self.ani = QPropertyAnimation(self, u"scale")
        ani.setStartValue(self.scale)
        ani.setEndValue(0)
        ani.setDuration(500)
        ani.finished.connect(self.remove)
        ani.start()

    def select_naub(self, pointer):
        pass

    def deselect_naub(self, pointer):
        pass

class Timer(Timer):
    def __init__(self, interval, callback):
        super(Timer, self).__init__(interval, callback)
        self.__timer = timer = QTimer()
        timer.setInterval(int(interval * 1000))
        timer.timeout.connect(callback)

    def start(self):
        self.__timer.start()

    def stop(self):
        self.__timer.stop()

    @property
    def interval(self): return self.__timer.interval()

class Application(Application):
    def __init__(self):
        super(Application, self).__init__()
        from PyQt4.QtGui import QApplication
        self.__app = QApplication([])

    def exec_(self):
        self.__app.exec_()

    def Timer(self, interval, callback):
        return Timer(interval, callback)

class GraphicsScene(GraphicsScene):
    def __init__(self):
        super(GraphicsScene, self).__init__()
        self.qscene = scene = QGraphicsScene()
        self.__items = []
        self.__naubino = None
        self.__objs_cutes = {}
        self.__cute_joints = []
        self.__update_objects = []
        from Highscore import Highscore
        self.__highscore = Highscore()

        scene.mousePressEvent = lambda e: self.mousePressEvent(e)
        scene.mouseReleaseEvent = lambda e: self.mouseReleaseEvent(e)
        scene.mouseMoveEvent = lambda e: self.mouseMoveEvent(e)

    @property
    def highscore(self): return self.__highscore

    @property
    def naubino(self): return self.__naubino
    @naubino.setter
    def naubino(self, naubino):
        self.__naubino = naubino

    def mousePressEvent(self, event):
        scene = self.qscene
        naubino = self.__naubino
        if not naubino: return
        event.naubino_pointer = naubino.pointer
        QGraphicsScene.mousePressEvent(scene, event)

    def mouseReleaseEvent(self, event):
        scene = self.qscene
        naubino = self.__naubino
        if not naubino: return
        event.naubino_pointer = naubino.pointer
        QGraphicsScene.mouseReleaseEvent(scene, event)

    def mouseMoveEvent(self, event):
        scene = self.qscene
        naubino = self.__naubino
        if naubino:
            pos = event.scenePos()
            pos = pos.x(), pos.y()
            naubino.pointer.pos = pos
        QGraphicsScene.mouseMoveEvent(scene, event)

    def add_item(self, *items):
        for x in items:
            if x not in self.__items:
                self.__items.append(x)
                self.qscene.addItem(x)

    def remove_item(self, *items):
        for x in items:
            if x in self.__items:
                self.__items.remove(x)
                self.qscene.removeItem(x)

    def add_naub(self, naub):
        if naub not in self.__objs_cutes:
            cute = CuteNaub(self, naub)
            self.__objs_cutes[naub] = cute

    def remove_naub(self, naub):
        if naub in self.__objs_cutes:
            del self.__objs_cutes[naub]

    def pre_remove_naub(self, naub):
        if naub in self.__objs_cutes:
            self.__objs_cutes[naub].remove_naub()

    def add_naub_joint(self, joint):
        if joint not in self.__objs_cutes:
            a = Pos(joint.joint.a)
            b = Pos(joint.joint.b)
            cute = CuteJoint(self, a, b)
            self.__objs_cutes[joint] = cute

    def remove_naub_joint(self, joint):
        if joint in self.__objs_cutes:
           del self.__objs_cutes[joint]

    def pre_remove_naub_joint(self, joint):
        if joint in self.__objs_cutes:
            self.__objs_cutes[joint].remove_joint()

    def add_update_object(self, obj):
        if obj not in self.__update_objects:
            self.__update_objects.append(obj)

    def remove_update_object(self, obj):
        if obj in self.__update_objects:
            self.__update_objects.remove(obj)

    def step(self, dt):
        for obj in self.__update_objects:
            obj.update_object()

class GraphicsView(GraphicsView):
    def __init__(self, scene):
        from Menu import NaubinoMenu
        super(GraphicsView, self).__init__(scene)
        self.__scene = scene
        self.__frame = frame = QFrame()
        self.__view = view = QGraphicsView()
        self.__naubino = naubino = scene.naubino
        self.__menu = menu = NaubinoMenu(scene)
        self.__arena = arena = CuteArena(scene)

        naubino.score_changed = menu.score_changed

        view.setParent(frame)
        view.setScene(scene.qscene)
        view.setGeometry(0, 0, 600, 400)
        view.setSceneRect(-290, -190, 580, 380)
        view.setRenderHints(QPainter.Antialiasing)
        view.setViewportUpdateMode(view.FullViewportUpdate)
        view.show()

        naubino.warn_changed = arena.warn_changed
        
        frame.show()

#######################################################

class HoverArea(QObject):
    entered  = pyqtSignal(QGraphicsSceneHoverEvent)
    leaved   = pyqtSignal(QGraphicsSceneHoverEvent)

    def __init__(self, area = None, rect = None, scene = None):
        QObject.__init__(self)
        if not area:
            area = QGraphicsEllipseItem()
            area.setPen(QPen(Qt.NoPen))
        if not rect: rect = QRect(-0.5, -0.5, 1, 1)
        if scene: scene.add_item(area)

        self.area = area
        area.setRect(rect)
        area.setAcceptHoverEvents(True)

        def hoverEnterEvent(event):
            self.entered.emit(event)
        area.hoverEnterEvent = hoverEnterEvent

        def hoverLeaveEvent(event):
            self.leaved.emit(event)
        area.hoverLeaveEvent = hoverLeaveEvent
