import sys
from PyQt4.QtCore import (
    QObject, pyqtSignal, SIGNAL,
    QTimer, QRectF)
from PyQt4.QtGui import (
    QApplication, QGraphicsView, QGraphicsScene,
    QGraphicsEllipseItem, QBrush, QColor,
    QGraphicsItem, QGraphicsObject, QPushButton,
    QFrame, QVBoxLayout, QPainter,
    QGraphicsLineItem, QPen)
import random
import pymunk
from pymunk import Vec2d

class Naub(QObject):
    def __init__(self):
        QObject.__init__(self)

        mass = 1
        radius = 15
        inertia = pymunk.moment_for_circle(mass, 0, radius)
        body = pymunk.Body(mass, inertia)
        body.position = 0, 0
        shape = pymunk.Circle(body, radius)

        self.body = body
        self.shape = shape

class NaubJoint(QObject): pass
class NaubJoint(NaubJoint):
    joined = pyqtSignal( NaubJoint )

    def join(self, nauba, naubb):
        a = nauba.body
        b = naubb.body
        center = (0,0)
        joint = pymunk.PinJoint(a, b, center, center)
        joint.distance = 40
        self.joint = joint
        self.joined.emit(self)

class Naubino(QObject):
    addedNaub = pyqtSignal( Naub )
    addedNaubJoint = pyqtSignal( NaubJoint )

    def __init__(self):
        QObject.__init__(self)

    def addNaub(self, naub):
        self.addedNaub.emit(naub)

    def addNaubJoint(self, joint):
        self.addedNaubJoint.emit(joint)

class NaubSimulator(QObject):
    def __init__(self):
        QObject.__init__(self)

        pymunk.init_pymunk()

        self.space = pymunk.Space()
        self.space.gravity = 0, -10

    def addNaub(self, naub):
        self.space.add(naub.body, naub.shape)

    def addJoint(self, joint):
        joint.joined.connect(self.join)
        if joint.joint is None: return
        self.join(joint)

    def join(self, joint):
        self.space.add(joint.joint)

    def step(self, dt):
        self.space.step(dt)

class Spammer(QObject):
    addedNaub = pyqtSignal( Naub )
    addedNaubJoint = pyqtSignal( NaubJoint )

    def spamPair(self, pos = None):
        if pos is None:
            pos = Vec2d(
                random.uniform(-300, 300),
                random.uniform(-200, 200))
        
        naub = Naub()
        naub.body.position = Vec2d(-40, 0) + pos
        naub.body.apply_impulse((80, -20))
        self.addedNaub.emit(naub)
        a = naub

        naub = Naub()
        naub.body.position = Vec2d(40, 0) + pos
        naub.body.apply_impulse((-80, 20))
        self.addedNaub.emit(naub)
        b = naub

        joint = NaubJoint()
        joint.join(a, b)
        self.addedNaubJoint.emit(joint)

    def start(self, interval):
        timer = QTimer()
        timer.setInterval(interval)
        timer.timeout.connect(self.spamPair)
        timer.start()
        self.timer = timer

class Cute(QGraphicsObject):
    def __init__(self):
        QGraphicsObject.__init__(self)
        #self.setFlags(self.ItemIsMovable)
        self.setAcceptHoverEvents(True)
        self.setAcceptTouchEvents(True)
    
    def setGraphicsItem(self, graphics_item):
        self.graphics_item = graphics_item
    
    def boundingRect(self):
        return self.graphics_item.boundingRect()

    def pre_paint(self):
        pass

    def paint(self, painter, option, widget = 0):
        self.pre_paint()
        self.graphics_item.paint(painter, option, widget)

    def full_connect(self, obj):
        pass

    def mousePressEvent(self, event):
        pass

    def mouseReleaseEvent(self, event):
        pass

class CuteJoint(Cute):
    def __init__(self):
        Cute.__init__(self)

        self.hide()

        line = QGraphicsLineItem()
        line.setParentItem(self)
        color = QColor(0, 0, 0)
        brush = QBrush(color)
        pen = QPen(brush, 4.0)
        line.setPen(pen)
        self.line = line
        self.setGraphicsItem(line)

    def pre_paint(self):
        self.update_joint()

    def update_joint(self):
        joint = self.joint
        if joint is None: return
        joint = joint.joint
        if joint is None: return
        a = joint.a.position
        b = joint.b.position
        self.line.setLine(a.x, a.y, b.x, b.y)

    def full_connect(self, joint):
        self.joint = joint
        self.update_joint()
        self.show()

class CuteNaub(Cute):
    def __init__(self):
        Cute.__init__(self)

        self.hide()

        elli = QGraphicsEllipseItem()
        elli.setParentItem(self)
        elli.setRect(-15, -15, 30, 30)
        color = QColor(0, 0, 0)
        brush = QBrush(color)
        elli.setBrush(brush)
        self.setGraphicsItem(elli)

    def pre_paint(self):
        self.update_naub()

    def update_naub(self):
        self.setPos(*self.naub.body.position)

    def full_connect(self, naub):
        self.naub = naub
        self.update_naub()
        self.show()

class CuteNaubino(QObject):
    addedCute = pyqtSignal( Cute )

    def addJoint(self, joint):
        cute = CuteJoint()
        self.__addCute(joint, cute)

    def addNaub(self, naub):
        cute = CuteNaub()
        self.__addCute(naub, cute)

    def __addCute(self, obj, cute):
        cute.full_connect(obj)
        self.addedCute.emit(cute)

class QGraphicsScene(QGraphicsScene):
    __QGraphicsScene = QGraphicsScene

    def mouseMoveEvent(self, event):
        self.__QGraphicsScene.mouseMoveEvent(self, event)

def main():
    app = QApplication([])

    frame = QFrame()
    frame.setGeometry(0, 0, 600, 400)
    frame.show()

    scene = QGraphicsScene()
    cute_naubino = CuteNaubino()
    naubino = Naubino()
    naub_simulator = NaubSimulator()
    spammer = Spammer()

    cute_naubino.addedCute.connect(scene.addItem)

    # original C++ Qt 4 code would be this :D
    # cute_naubino.connect(&naubino, SIGNAL("addedNaub(Naub&)"), SLOT("addNaub(Naub&)")
    naubino.addedNaub     .connect(cute_naubino  .addNaub )
    naubino.addedNaubJoint.connect(cute_naubino  .addJoint)
    naubino.addedNaub     .connect(naub_simulator.addNaub )
    naubino.addedNaubJoint.connect(naub_simulator.addJoint)

    spammer.addedNaub     .connect(naubino.addNaub)
    spammer.addedNaubJoint.connect(naubino.addNaubJoint)
    
    timer = QTimer()
    timer.setInterval(50)
    def sim_step():
        naub_simulator.step(1.0 / timer.interval())
    timer.timeout.connect(sim_step)
    timer.timeout.connect(scene.update)

    def foo():
        button.hide()

        view = QGraphicsView(frame)
        view.setGeometry(0, 0, 600, 400)
        view.setSceneRect(-290, -190, 580, 380)
        view.setScene(scene)
        #view.setRenderHints(QPainter.Antialiasing)
        view.show()

        timer.start()
        spammer.start(1000)

    button = QPushButton(frame)
    button.clicked.connect(foo)
    button.show()

    e = app.exec_()
    sys.exit(e)

if __name__ == "__main__": main()
