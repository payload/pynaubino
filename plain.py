import sys
from PyQt4.QtCore import *
from PyQt4.QtGui import *
import random
import pymunk
from pymunk import Vec2d

class Pointer:
    @property
    def pos(self): return self.body.position
    @pos.setter
    def pos(self, x): self.body.position = x

    def __init__(self):
        body = pymunk.Body(pymunk.inf, pymunk.inf)
        body.position = 0, 0
        self.body = body

class Cute(QGraphicsObject):    
    def __init__(self):
        QGraphicsObject.__init__(self)
        self.setAcceptHoverEvents(True)
        self.setAcceptTouchEvents(True)

    def boundingRect(self):
        return self.graphics_item.boundingRect()

    def update_object(self):
        pass

    def paint(self, painter, option, widget = 0):
        self.update_object()
        self.graphics_item.paint(painter, option, widget)

class CuteJoint(Cute):
    def __init__(self, joint, layer = -2):
        Cute.__init__(self)
        self.setZValue(layer)
        line = QGraphicsLineItem()
        line.setParentItem(self)
        brush = QBrush(QColor("black"))
        pen = QPen(brush, 4.0)
        line.setPen(pen)
        self.line = line
        self.graphics_item = line
        self.joint = joint

    def update_object(self):
        a = self.joint.a.position
        b = self.joint.b.position
        self.line.setLine(a.x, a.y, b.x, b.y)

class CuteNaub(Cute):
    def __init__(self, naub, layer = -1):
        Cute.__init__(self)        
        self.setZValue(layer)
        elli = QGraphicsEllipseItem()
        elli.setParentItem(self)
        elli.setRect(-15, -15, 30, 30)
        elli.setPen(QPen(Qt.NoPen))
        self.color = None
        self.elli = elli
        self.graphics_item = elli
        self.naub = naub
        self.select = None
        self.deselect = None
        self.update_object()

    def update_object(self):
        naub = self.naub
        pos = naub.body.position
        self.setPos(pos.x, pos.y)
        if naub.color != self.color:
            self.color = naub.color
            self.elli.setBrush(QBrush(self.color))

    def mousePressEvent(self, event):
        self.naub.select(event.naubino_pointer)

    def mouseReleaseEvent(self, event):
        self.naub.deselect(event.naubino_pointer)

class Naub:
    @property
    def pos(self): return self.body.position
    @pos.setter
    def pos(self, x): self.body.position = x
    
    def __init__(self, space):
        mass = 1
        radius = 15
        inertia = pymunk.moment_for_circle(mass, 0, radius)
        body = pymunk.Body(mass, inertia)
        body.position = 0, 0
        shape = pymunk.Circle(body, radius)
        color = QColor("black")
        space.add(body, shape)

        self.body = body
        self.shape = shape
        self.color = color
        self.space = space
        self.pointer_joints = {}

    def select(self, pointer):
        pj = self.pointer_joints
        if pointer in pj: return
        a = self.body
        b = pointer.body
        center = (0,0)
        joint = pymunk.PinJoint(a, b, center, center)
        joint.distance = 0
        self.space.add(joint)
        pj[pointer] = joint

    def deselect(self, pointer):
        pj = self.pointer_joints
        if pointer not in pj: return
        self.space.remove(pj[pointer])
        del pj[pointer]

class NaubJoint:
    def __init__(self, a, b):
        a = a.body
        b = b.body
        center = (0,0)
        joint = pymunk.PinJoint(a, b, center, center)
        joint.distance = 60
        self.joint = joint

def random_vec(xv, yv):
    return Vec2d(
        random.uniform(-xv, xv),
        random.uniform(-yv, yv))

def are_colors_alike(a, b):
    rgb0 = a.getRgbF()
    rgb1 = b.getRgbF()
    return sum([ rgb0[i]*rgb1[i] for i in range(3) ]) < 0.5

def random_byte():
    return random.randint(0, 255)

def random_not_white():
    r = random_byte
    white = QColor("white")
    while True:
        color = QColor(r(), r(), r())
        if not are_colors_alike(color, white):
            return color

class QGraphicsScene(QGraphicsScene):
    __QGraphicsScene = QGraphicsScene

    def __init__(self, pointer):
        self.__QGraphicsScene.__init__(self)
        self.pointer = pointer

    def mousePressEvent(self, event):
        event.naubino_pointer = self.pointer
        self.__QGraphicsScene.mousePressEvent(self, event)

    def mouseReleaseEvent(self, event):
        event.naubino_pointer = self.pointer
        self.__QGraphicsScene.mouseReleaseEvent(self, event)
    
    def mouseMoveEvent(self, event):
        pos = event.scenePos()
        pos = pos.x(), pos.y()
        self.pointer.pos = pos
        self.__QGraphicsScene.mouseMoveEvent(self, event)

def main():
    pymunk.init_pymunk()
    space = pymunk.Space()

    app = QApplication([])

    pointer = Pointer()
    space.add(pointer.body)

    scene = QGraphicsScene(pointer)

    naubs = []
    joints = []
    cute_naubs = []
    cute_joints = []

    def add_naub(pos = (0, 0)):
        naub = Naub(space)
        naub.pos = pos
        cute = CuteNaub(naub)
        
        naubs.append(naub)
        cute_naubs.append(cute)
        scene.addItem(cute)
        return naub

    def join_naubs(a, b):
        joint = NaubJoint(a, b)
        cute = CuteJoint(joint.joint)
        
        joints.append(joint)
        space.add(joint.joint)
        cute_joints.append(cute)
        scene.addItem(cute)

    def add_naub_pair(pos = (0, 0)):
        pos = Vec2d(pos)
        a = Vec2d(-30, 0) + pos
        b = Vec2d( 30, 0) + pos
        
        a = add_naub(a)
        b = add_naub(b)
        join_naubs(a, b)
        return a, b

    def spam():
        pos = random_vec(300, 200)
        a, b = add_naub_pair(pos)

        impulse = lambda: random_vec(50, 50)
        a.body.apply_impulse(impulse())
        b.body.apply_impulse(impulse())
        
        a.color = random_not_white()
        b.color = random_not_white()

    spammer = QTimer()
    spammer.setInterval(1000)
    spammer.timeout.connect(spam)

    def play():
        spammer.start()

    frame = QFrame()
    frame.setGeometry(0, 0, 600, 400)

    view = QGraphicsView(frame)
    view.setGeometry(0, 0, 600, 400)
    view.setSceneRect(-290, -190, 580, 380)
    view.setScene(scene)
    #view.setRenderHints(QPainter.Antialiasing)

    timer = QTimer()
    timer.setInterval(50)
    def frame_step():
        space.step(1.0 / timer.interval())
        cutes = cute_naubs + cute_joints
        for cute in cutes:
            cute.update_object()
            cute.update()

    timer.timeout.connect(frame_step)

    view.show()
    frame.show()
    timer.start()
    play()
    
    e = app.exec_()
    sys.exit(e)

if __name__ == "__main__": main()