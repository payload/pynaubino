from kivy.uix.widget    import Widget
from kivy.graphics      import *
from utils              import *

class Arena(object):

    def __init__(self, naubino, mode, game):
        with game.back.canvas:
            self.layer = Widget()
            with self.layer.canvas:
                Color(0, 0, 0, 0.05)
                Ellipse(pos = (-50, -50), size = (100, 100))
