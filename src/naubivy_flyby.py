from kivy.uix.widget    import Widget
from kivy.graphics      import *
from utils              import *

class Flyby(object):

    def __init__(self, naubino, mode, game):
        with game.back.canvas:
            self.layer = Widget()
        self.bind_mode(mode)

    def bind_mode(self, mode):
        self.add_anchor(mode.center)

    def add_anchor(self, anchor):
        l, t, r, b      = get(anchor.shape.bb, 'left top right bottom')
        pos             = (l, b)
        size            = (r - l, t - b)
        widget          = Widget()
        with widget.canvas:
            Color(0, 0, 0, 1)
            Ellipse(pos = pos, size = size)
        self.layer.add_widget(widget)