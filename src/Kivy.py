from kivy.app import App
from kivy.uix.widget import Widget
from kivy.properties import NumericProperty, ReferenceListProperty
from kivy.vector import Vector
from kivy.clock import Clock
from kivy.graphics import *
from Naubino import Naubino
from utils import *



class NaubinoGame(Widget):

    def __init__(self, *args, **kwargs):
        super(NaubinoGame, self).__init__(*args, **kwargs)
        self.naubino        = Naubino()
        self.bind(size      = lambda self, size:
            setattr(self.naubino, "size", size))

    def start(self):
        self.naubino.play()

    def update(self, dt):
        self.naubino.size = self.size
        self.naubino.step(dt)
        self.canvas.clear()
        with self.canvas:
            ClearColor(1, 1, 1, 1)
            ClearBuffers(clear_color = True)
            Translate(self.size[0] * 0.5, self.size[1] * 0.5)
            Color(0, 0, 0)
            for joint in self.naubino.naubjoints:
                a = joint.a.pos + [joint.a.radius] * 2
                b = joint.b.pos + [joint.b.radius] * 2
                Line(points = [a.x , a.y, b.x, b.y], width = 4)
            for naub in self.naubino.naubs:
                Color(*color_rgb1(naub.color))
                pos         = naub.pos
                d           = naub.radius * 2
                Ellipse(
                    pos     = pos,
                    size    = (d, d))


class NaubinoApp(App):
    def build(self):
        game = NaubinoGame()
        game.start()
        Clock.schedule_interval(game.update, 1.0/60.0)
        return game




if __name__ == '__main__':
    app = NaubinoApp()
    app.run()