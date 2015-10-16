from __future__         import print_function
from kivy.uix.widget    import Widget
from kivy.graphics      import *
from kivy.clock         import Clock
from kivy.animation     import Animation
from kivy.metrics       import mm
from kivy.vector        import Vector
from kivy.event         import EventDispatcher
from kivy.properties    import *
from utils              import *
from .                  import intro
from naubino.Naub       import Naub

class Explosion(EventDispatcher):

    def __init__(self, naubino, mode, game):
        super(Explosion, self).__init__()
        self.naubino    = naubino
        self.mode       = mode
        self.game       = game
        self.label      = intro.NaubinoLabel()

        label           = self.label
        game.add_widget(label)

        naub        = mode.create_start_naub()

        fade_in         = Animation(
            opacity         = 1,
            transition      = "in_cubic",
            duration        = 1)
        fade_out        = Animation(
            opacity         = 0,
            transition      = "in_quad",
            duration        = 3)
        move_center = Animation(
            pos         = Vector(0, 0),
            duration    = 3,
            transition  = "in_cubic")
        def move_center_phase(anim, obj):
            if obj == label:
                move_center.start(naub)
                fade_out.start(label)
        def explode_phase(anim, obj):
            naub.explode()
        def set_o_naub(*_):
            naub.pos    = self.get_o_naub_pos()
            naub.radius = self.label.o_radius / mm(1)

        label.opacity       = 0
        game.naubs.opacity  = 0
        fade_in.start(label)
        fade_in.start(game.naubs)
        # TODO get_o_naub_pos is only available after first frame
        Clock.schedule_once(set_o_naub, 0.01)
        fade_in.bind(
            on_complete     = move_center_phase)
        move_center.bind(
            on_complete     = explode_phase)

    def get_o_naub_pos(self):
        label, game = self.label, self.game
        x, y        = Vector(label.o_center) - game.center
        x, y        = x / mm(1), y / mm(-1)
        return x, y
