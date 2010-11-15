import random
from PyQt4.QtCore import *
import pymunk
from pymunk import Vec2d
from PyQt4.QtGui import QColor, QGraphicsItem

def random_vec(xv, yv):
    return Vec2d(
        random.uniform(-xv, xv),
        random.uniform(-yv, yv))

def are_colors_alike(a, b):
    a = a.getRgbF()
    b = b.getRgbF()
    return all([(max(a[i], b[i]) - min(a[i], b[i])) < 0.25
        for i in xrange(3)])

def random_byte():
    return random.randint(0, 255)

def random_not_white():
    r = random_byte
    white = QColor(u"white")
    while True:
        color = QColor(r(), r(), r())
        if not are_colors_alike(color, white):
            return color

def toVec2d(v):
    if isinstance(v, Vec2d): return v
    else: return Vec2d(v.x(), v.y())

class Pos(object):
    @property
    def pos(self): return self.get_pos()
    @pos.setter
    def pos(self, pos): self.set_pos(pos)

    def __init__(self, x):
        if   isinstance(x, pymunk.Body):
            self.get_pos = lambda: x.position
            self.set_pos = lambda pos: setattr(x, u"position", pos)
        elif isinstance(x, QGraphicsItem):
            def get_pos():
                pos = x.pos()
                return Vec2d(pos.x(), pos.y())
            self.get_pos = get_pos
            def set_pos(pos):
                x.setPos(pos.x, pos.y)
        else:
            raise TypeError(type(x))
