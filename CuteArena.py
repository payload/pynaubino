from PyQt4.QtCore import *
from PyQt4.QtGui import *

class CuteArena(QObject):
    def __init__(self, scene):
        super(CuteArena, self).__init__()
        self.naubino = naubino = scene.naubino
        self.__arena = arena = QGraphicsEllipseItem()
        self.color_ani = None
        self.min_pen_width = 3
        self.max_pen_width = 6
        self.width_ani = ani = QPropertyAnimation(self, "arena_pen_width")
        ani.setStartValue(self.min_pen_width)
        ani.setEndValue(self.max_pen_width)
        ani.setDuration(1000)

        scene.add_item(arena)
        r = 160
        arena.setRect(-r, -r, 2*r, 2*r)
        arena.setPen(QPen(QColor(*naubino.colors["grey"]), self.min_pen_width))
        arena.setZValue(-40)
        arena.show()

    def switch_ani_direction(self, ani):
        cdir = ani.direction()
        ani.setDirection(ani.Backward if cdir == ani.Forward else ani.Forward)
        ani.start()

    def warn_changed(self, warn):
        if self.color_ani: self.color_ani.stop()
        if warn:
            self.color_ani = ani = QPropertyAnimation(
                self, "arena_pen_color")
            ani.setEndValue(QColor(*self.naubino.colors["red"]))
            ani.setDuration(1000)
            ani.start()

            ani = self.width_ani
            ani.finished.connect(lambda: self.switch_ani_direction(ani))
            ani.start()
        else:
            self.color_ani = ani = QPropertyAnimation(
                self, "arena_pen_color")
            ani.setEndValue(QColor(*self.naubino.colors["grey"]))
            ani.setDuration(1000)
            ani.start()

            ani = self.width_ani
            ani.setDirection(ani.Backward)
            ani.finished.disconnect()

    def get_arena_pen(self):
        return self.__arena.pen()
    def set_arena_pen(self, pen):
        self.__arena.setPen(pen)
    arena_pen = pyqtProperty(QPen, get_arena_pen, set_arena_pen)

    def get_arena_pen_color(self):
        return self.get_arena_pen().color()
    def set_arena_pen_color(self, color):
        pen = self.get_arena_pen()
        pen.setColor(color)
        self.set_arena_pen(pen)
    arena_pen_color = pyqtProperty(QColor,
        get_arena_pen_color,
        set_arena_pen_color)

    def get_arena_pen_width(self):
        return self.get_arena_pen().widthF()
    def set_arena_pen_width(self, width):
        pen = self.get_arena_pen()
        pen.setWidthF(width)
        self.set_arena_pen(pen)
    arena_pen_width = pyqtProperty(float,
        get_arena_pen_width,
        set_arena_pen_width)