from Interfaces import *

from PyQt4.QtCore import *
from PyQt4.QtGui import *
import random
from utils import *
from CuteArena import CuteArena

class Cute(QObject):
    def __init__(self, scene):
        super(Cute, self).__init__()
        self.scene = scene
        self.naubino = scene.naubino

    def update_object(self):
        pass
        
    def qcolor(self, color):
        return qcolor(color, self.naubino.colors)

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

class Application(Application):
    def __init__(self, naubino):
        super(Application, self).__init__()
        from PyQt4.QtGui import QApplication
        self.__app = QApplication([])
        self.naubino = naubino
        naubino.app = self

        self.step_timer = timer = QTimer()
        timer.setInterval(20)
        timer.timeout.connect(lambda: self.step(0.02))
        timer.start()

        self.qscene = scene = QGraphicsScene()
        self.__items = []
        self.__objs_cutes = {}
        self.__cute_joints = []
        self.__update_objects = []
        from Highscore import Highscore
        self.__highscore = Highscore()

        scene.mousePressEvent = lambda e: self.mousePressEvent(e)
        scene.mouseReleaseEvent = lambda e: self.mouseReleaseEvent(e)
        scene.mouseMoveEvent = lambda e: self.mouseMoveEvent(e)
        
        self.qview = GraphicsView(self)

    def exec_(self):
        self.__app.exec_()

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
        from CuteNaub import CuteNaub
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
        self.naubino.step(dt)
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
        
        scene.menu = menu # TODO unclean

        naubino.score_changed = menu.score_changed

        view.setParent(frame)
        view.setScene(scene.qscene)
        view.setBackgroundBrush(QBrush(QColor("white")))
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
