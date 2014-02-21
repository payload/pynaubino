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
        self.naubino.step(dt)
        self.canvas.clear()
        with self.canvas:
            ClearColor(1, 1, 1, 1)
            ClearBuffers(clear_color = True)
            Translate(*self.center)
            Scale(1 -1, 1)
            Color(0, 0, 0)
            for joint in self.naubino.naubjoints:
                a, b = joint.endpoints
                Line(points = [a.x , a.y, b.x, b.y], width = 4)
            for naub in self.naubino.naubs:
                bb = naub.shape.bb
                Color(*color_rgb1(naub.color))
                Ellipse(
                    pos     = (bb.left, bb.bottom),
                    size    = (bb.right - bb.left, bb.top - bb.bottom))

    def on_touch_down(self, touch):
        pos     = Vec2d(touch.pos) - self.center
        for naub in self.naubino.naubs:
            if (naub.pos - pos).length <= naub.radius:
                pointer = self.naubino.create_pointer(pos)
                naub.select(pointer)
                touch.ud.update(
                    pointer = pointer,
                    naub    = naub)

    def on_touch_move(self, touch):
        if 'pointer' in touch.ud:
            touch.ud['pointer'].pos = Vec2d(touch.pos) - self.center

    def on_touch_up(self, touch):
        if 'naub' in touch.ud and 'pointer' in touch.ud:
            touch.ud['naub'].deselect(touch.ud['pointer'])


class NaubinoApp(App):
    def build(self):
        game = NaubinoGame()
        game.start()
        Clock.schedule_interval(game.update, 1.0/60.0)
        return game




if __name__ == '__main__':
    app = NaubinoApp()
    app.run()