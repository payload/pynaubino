from naubivy_arena import Arena
from naubivy_flyby import Flyby



from kivy.app import App
from kivy.uix.widget import Widget
from kivy.properties import NumericProperty, ReferenceListProperty
from kivy.vector import Vector
from kivy.clock import Clock
from kivy.graphics import *
from kivy.metrics import mm
from utils import *
import anims

from kivy.config import Config

import os
DISPLAY     = os.getenv("DISPLAY")
WALL_DEVICE = "wall" # look into ~/.kivy/config.ini [input]
WALL_SIZE   = (7680., 3240.)
WALL_LEFT   = ":0.1"
WALL_RIGHT  = ":0.0"



class Game(Widget):

    def __init__(self, naubino, *args, **kwargs):
        super(Game, self).__init__(*args, **kwargs)
        self.naubino        = naubino
        self.bind(size      = lambda self, size:
            setattr(self.naubino, "size", Vec2d(size) / mm(1)))
        with self.canvas:
            self.translate      = Translate(*self.center)
            Scale(mm(1), mm(-1), 1)
            self.back   = Widget()
            self.joints = Widget()
            with self.joints.canvas:
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
        self.joints.add_widget(kivy)

    def remove_naub_joint(self, joint):
        kivy, joint.tag = joint.tag, None
        self.joints.remove_widget(kivy)

    def start(self):
        self.naubino.play()

    def update(self, dt):
        self.translate.xy = self.center
        self.naubino.step(dt)
        for joint in self.naubino.naubjoints:
            joint.tag.update()

    def on_touch_down(self, touch):
        pos                 = self.translate_touch_pos(touch)
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
        cx, cy  = self.center
        mm1     = 1 / mm(1)
        x       = (x - cx) *  mm1
        y       = (y - cy) * -mm1
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



class KivyNaub(Widget):

    def __init__(self, naub):
        super(KivyNaub, self).__init__()
        self.naub       = naub
        with self.canvas:
            self.color      = Color()
            self.shape      = Ellipse()
        naub.bind(
            color   = self.set_color,
            pos     = self.set_pos,
            radius  = self.set_radius)
        naub.property("pos").dispatch(naub)
        naub.property("color").dispatch(naub)
        naub.property("radius").dispatch(naub)
        self.highlighted = 0

    def set_color(self, naub, color):
        self.color.rgb  = color_rgb1(self.naub.color)

    def set_radius(self, naub, radius):
        self.shape.size = [(radius - 0.4)*2]*2

    def set_pos(self, naub, pos):
        self.shape.pos  = pos - 0.5*Vector(self.shape.size)

    def highlight(self):
        if self.highlighted == 0:
            v       = self.color.v
            self.anim = anims.cycle(
                v           = (v * 0.8, v * 1.2),
                duration    = 0.1,
                anim_end    = dict(v = v))
            self.anim.start(self.color)
        self.highlighted += 1

    def unhighlight(self):
        if self.highlighted == 1:
            self.anim.stop(self.color)
            self.anim.cancel(self.color)
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
