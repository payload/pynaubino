from kivy.app import App
from kivy.uix.widget import Widget
from kivy.properties import NumericProperty, ReferenceListProperty
from kivy.vector import Vector
from kivy.clock import Clock
from kivy.graphics import *
from kivy.metrics import mm
from Naubino import Naubino
from utils import *
import anims

from kivy.config import Config
#Config.set('graphics', 'fullscreen', 'auto')

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
        off                 = 0.4
        off2                = off*2
        bb                  = get(naub.shape.bb, 'left top right bottom')
        left, top, right, bottom = bb
        pos                 = (left + off, bottom + off)
        size                = (right - left - off2, top - bottom - off2)
        shape.pos           = pos
        shape.size          = size

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



class NaubinoGame(Widget):

    def __init__(self, *args, **kwargs):
        super(NaubinoGame, self).__init__(*args, **kwargs)
        self.naubino        = Naubino()
        self.bind(size      = lambda self, size:
            setattr(self.naubino, "size", Vector(size) / mm(1)))
        with self.canvas:
            self.translate      = Translate(*self.center)
            Scale(mm(1), mm(-1), 1)
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
        for naub in self.naubino.naubs:
            naub.tag.update()
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



from kivy.lang import Builder
from kivy.uix.screenmanager import Screen, ScreenManager

class MenuScreen(Screen):

    def __init__(self, **kwargs):
        super(MenuScreen, self).__init__(**kwargs)

class ArenaModeScreen(Screen):

    def on_enter(self):
        game = NaubinoGame()
        from Naubino import ArenaMode
        game.naubino.mode = ArenaMode(game.naubino)
        game.start()
        Clock.schedule_interval(game.update, 1.0/60.0)
        self.add_widget(game)

class FlybyModeScreen(Screen):

    def on_enter(self):
        game = NaubinoGame()
        from Naubino import FlybyMode
        game.naubino.mode = FlybyMode(game.naubino)
        game.start()
        Clock.schedule_interval(game.update, 1.0/60.0)
        self.add_widget(game)


Builder.load_string("""
<MenuScreen>:
    name:           "menu"
    AnchorLayout:
        anchor_x:       "center"
        anchor_y:       "center"
        BoxLayout:
            orientation:    "vertical"
            size_hint:  (0.1, 0.5)
            Label:
                text:       "Naubino"
                color:      (0, 0, 0, 1)
            Button:
                text:       "Arena Mode"
                on_press:   root.manager.current = "arena"
            Button:
                text:       "Flyby Mode"
                on_press:   root.manager.current = "flyby"
            Button:
                text:       "Quit"
                on_press:   root.quit()
""")



class NaubinoApp(App):
    def build(self):

        from kivy.core.window import Window
        Window.clearcolor   = (1, 1, 1, 1)

        menu_screen         = MenuScreen()
        arena_screen        = ArenaModeScreen(name = "arena")
        flyby_screen        = FlybyModeScreen(name = "flyby")

        sm                  = ScreenManager()
        sm.add_widget(menu_screen)
        sm.add_widget(arena_screen)
        sm.add_widget(flyby_screen)

        return sm




def main():
    app = NaubinoApp()
    app.run()

if __name__ == '__main__':
    main()
