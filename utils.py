import random
from PyQt4.QtCore import *
from pymunk import Vec2d
from PyQt4.QtGui import QColor

def random_vec(xv, yv):
    return Vec2d(
        random.uniform(-xv, xv),
        random.uniform(-yv, yv))

def are_colors_alike(a, b):
    a = a.getRgbF()
    b = b.getRgbF()
    return all([(max(a[i], b[i]) - min(a[i], b[i])) < 0.25
        for i in range(3)])

def random_byte():
    return random.randint(0, 255)

def random_not_white():
    r = random_byte
    white = QColor("white")
    while True:
        color = QColor(r(), r(), r())
        if not are_colors_alike(color, white):
            return color

def random_naub_color():
    c = ["red", "green", "blue"]#, "purple", "yellow", "aqua"]
    random.shuffle(c)
    return QColor(c[0])

class Pos:
    @property
    def pos(self): return self.__x.position
    @pos.setter
    def pos(self, pos): self.__x.position = pos

    def __init__(self, x):
        self.__x = x