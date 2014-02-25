from kivy.app import App
from kivy.uix.widget import Widget
from kivy.properties import NumericProperty, ReferenceListProperty
from kivy.vector import Vector
from kivy.clock import Clock
from kivy.graphics import *
from Naubino import Naubino
from utils import *

from kivy.config import Config
Config.set('graphics', 'fullscreen', 'auto')

import os
DISPLAY     = os.getenv("DISPLAY")
WALL_DEVICE = "wall" # look into ~/.kivy/config.ini [input]
WALL_SIZE   = (7680., 3240.)
WALL_LEFT   = ":0.1"
WALL_RIGHT  = ":0.0"



class KivyNaub(object):

    def __init__(self, naub):
        self.naub       = naub
        self.color      = Color(*color_rgb1(naub.color))
        bb              = naub.shape.bb
        self.ellipse    = Ellipse(
            pos         = (bb.l, bb.b),
            size        = (bb.r - bb.l, bb.t - bb.b))

    def update(self):
        self.color.rgb  = color_rgb1(self.naub.color)
        bb              = self.naub.shape.bb
        ellipse         = self.ellipse
        ellipse.pos     = (bb.l, bb.b)
        ellipse.size    = (bb.r - bb.l, bb.t - bb.b)



class KivyNaubJoint(object):

    def __init__(self, joint):
        self.joint      = joint
        a, b            = joint.endpoints
        self.line       = Line(
            points      = [a.x, a.y, b.x, b.y],
            width       = joint.a.radius * 0.212)

    def update(self):
        a, b            = self.joint.endpoints
        line            = self.line
        line.points     = [a.x, a.y, b.x, b.y]



class NaubinoGame(Widget):

    def __init__(self, *args, **kwargs):
        super(NaubinoGame, self).__init__(*args, **kwargs)
        self.naubino        = Naubino()
        self.bind(size      = lambda self, size:
            setattr(self.naubino, "size", size))
        from kivy.core.window import Window
        Window.clearcolor   = (1, 1, 1, 1)
        self.naub_joints    = {}
        self.naubs          = {}
        with self.canvas:
            self.translate = Translate(*self.center)
            Scale(1 -1, 1)
            Color(0, 0, 0)
        cb = self.naubino.cb
        cb.add_naub         = self.add_naub
        cb.remove_naub      = self.remove_naub
        cb.add_naub_joint   = self.add_naub_joint
        cb.remove_naub_joint = self.remove_naub_joint

    def add_naub(self, naub):
        kivy                = KivyNaub(naub)
        self.naubs[naub]    = kivy
        self.canvas.add(kivy.color)
        self.canvas.add(kivy.ellipse)

    def remove_naub(self, naub):
        kivy                = self.naubs[naub]
        del self.naubs[naub]
        self.canvas.remove(kivy.color)
        self.canvas.remove(kivy.ellipse)

    def add_naub_joint(self, joint):
        kivy                = KivyNaubJoint(joint)
        self.naub_joints[joint] = kivy
        self.canvas.insert(3, kivy.line)

    def remove_naub_joint(self, joint):
        kivy                = self.naub_joints[joint]
        del self.naub_joints[joint]
        self.canvas.remove(kivy.line)

    def start(self):
        self.naubino.play()

    def update(self, dt):
        self.translate.xy = self.center
        self.naubino.step(dt)
        for naub in self.naubs.values():
            naub.update()
        for joint in self.naub_joints.values():
            joint.update()

    def on_touch_down(self, touch):
        pos                 = self.translate_touch_pos(touch)
        pos                 = Vec2d(*pos) - self.center
        touch.ud.update(
            naubino_touch   = self.naubino.touch_down(pos))

    def on_touch_move(self, touch):
        naubino_touch       = touch.ud.get('naubino_touch', None)
        if not naubino_touch: return
        pos                 = self.translate_touch_pos(touch)
        pos                 = Vec2d(*pos) - self.center
        naubino_touch.move(pos)

    def on_touch_up(self, touch):
        naubino_touch       = touch.ud.get('naubino_touch', None)
        if not naubino_touch: return
        naubino_touch.up()

    def translate_touch_pos(self, touch):
        if touch.device == WALL_DEVICE:
            x = touch.spos[0] * WALL_SIZE[0]
            y = touch.spos[1] * WALL_SIZE[1]
            if   WALL_LEFT  == DISPLAY:
                pass
            elif WALL_RIGHT == DISPLAY:
                x -= WALL_SIZE[0] * 0.5
        else:
            x = touch.x
            y = touch.y
        return (x, y)



class NaubinoApp(App):
    def build(self):
        game = NaubinoGame()
        game.start()
        Clock.schedule_interval(game.update, 1.0/60.0)
        return game



def main():
    app = NaubinoApp()
    app.run()

if __name__ == '__main__':
    main()
