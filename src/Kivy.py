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



class KivyNaub(Widget):

    def __init__(self, naub):
        super(KivyNaub, self).__init__()
        self.naub       = naub
        with self.canvas:
            self.color      = Color()
            self.shape      = Ellipse()
        self.update     = self.update_first
        self.highlighted = 0

    def update_first(self):
        self.color.rgb  = color_rgb1(self.naub.color)
        self.update_always()
        self.update = self.update_always

    def update_always(self):
        shape, naub         = self.shape, self.naub
        bb                  = naub.shape.bb
        off                 = 2
        off2                = off*2
        pos                 = (bb.l + off, bb.b + off)
        size                = (bb.r - bb.l - off2, bb.t - bb.b - off2)
        shape.pos           = pos
        shape.size          = size

    def highlight(self):
        if self.highlighted == 0:
            self.color.v    = self.color.v * 1.2
        self.highlighted += 1

    def unhighlight(self):
        if self.highlighted == 1:
            self.color.v    = self.color.v / 1.2
        self.highlighted = max(0, self.highlighted - 1)



class KivyNaubJoint(Widget):

    def __init__(self, joint):
        super(KivyNaubJoint, self).__init__()
        self.joint      = joint
        a, b            = joint.endpoints
        with self.canvas:
            self.line = Line(
                points      = [a.x, a.y, b.x, b.y],
                width       = joint.a.radius * 0.212,
                cap         = 'none',
                joint       = 'none',
                close       = False)

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
        with self.canvas:
            self.translate      = Translate(*self.center)
            Scale(1 -1, 1)
            self.joins = Widget()
            with self.joins.canvas:
                Color(0, 0, 0)
            self.naubs = Widget()
        cb = self.naubino.cb
        cb.add_naub         = self.add_naub
        cb.remove_naub      = self.remove_naub
        cb.add_naub_joint   = self.add_naub_joint
        cb.remove_naub_joint = self.remove_naub_joint

    def add_naub(self, naub):
        kivy = naub.tag = KivyNaub(naub)
        self.naubs.add_widget(kivy)

    def remove_naub(self, naub):
        kivy, naub.tag = naub.tag, None
        self.naubs.remove_widget(kivy)

    def add_naub_joint(self, joint):
        kivy = joint.tag = KivyNaubJoint(joint)
        self.joins.add_widget(kivy)

    def remove_naub_joint(self, joint):
        kivy, joint.tag = joint.tag, None
        self.joins.remove_widget(kivy)

    def start(self):
        self.naubino.play()

    def update(self, dt):
        self.translate.xy = self.center
        self.naubino.step(dt)
        for naub in self.naubino.naubs:
            naub.tag.update()
        for joint in self.naubino.naubjoints:
            joint.tag.update()

    def on_touch_down(self, touch):
        pos                 = self.translate_touch_pos(touch)
        pos                 = Vec2d(*pos) - self.center
        naubino_touch       = self.naubino.touch_down(pos)
        if not naubino_touch: return
        naub                = naubino_touch.naub
        self.highlight_reachable_naubs(naub)
        touch.ud.update(
            naubino_touch   = naubino_touch)

    def on_touch_move(self, touch):
        naubino_touch       = touch.ud.get('naubino_touch', None)
        if not naubino_touch: return
        pos                 = self.translate_touch_pos(touch)
        pos                 = Vec2d(*pos) - self.center
        naubino_touch.move(pos)

    def on_touch_up(self, touch):
        try: naubino_touch       = touch.ud['naubino_touch']
        except: return
        naub                = naubino_touch.naub
        self.unhighlight_reachable_naubs(naub)
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

    def highlight_reachable_naubs(self, naub):
        naubs       = naub.reachable_naubs()
        for naub in naubs:
            kivy    = naub.tag
            kivy.highlight()

    def unhighlight_reachable_naubs(self, naub):
        naubs       = naub.reachable_naubs()
        for naub in naubs:
            kivy    = naub.tag
            try: kivy.unhighlight()
            except: pass



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
