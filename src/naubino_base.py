import pymunk
from pymunk import Vec2d
from Space import Space
from Pointer import Pointer
from utils import *
from Naub import Naub
from random import sample, random
import math
import Config

class Naubino(object):

    class Callbacks(object):
        def score_changed       (self, score    ): pass
        def warn_changed        (self, warn     ): pass
        def add_naub            (self, naub     ): pass
        def remove_naub         (self, naub     ): pass
        def add_naub_joint      (self, joint    ): pass
        def remove_naub_joint   (self, joint    ): pass
        def pre_remove_naub     (self, naub     ): pass
        def pre_remove_naub_joint(self, joint   ): pass
        def fail                (self           ): pass

    @property
    def score(self): return self.__score
    @score.setter
    def score(self, score):
        if self.__score == score: return
        self.__score = score
        self.cb.score_changed(score)

    @property
    def warn(self): return self.__warn
    @warn.setter
    def warn(self, warn):
        if self.__warn == warn: return
        self.__warn = warn
        self.cb.warn_changed(warn)

    def __init__(self):
        self.naubs              = []
        self.naubjoints         = set()
        self.playing            = False
        self.cb                 = Naubino.Callbacks()
        self.__score            = 0
        self.__warn             = False
        self.space              = Space(self)
        self.pointers           = set()
        self.size               = Vec2d(0, 0)
        self.mode               = None
        self.naub_colors        = dict((name, ColorRGB255(*color)) for
            name        , color in (
            ("red"      , (229,  53,  23)),
            ("pink"     , (226,   0, 122)),
            ("green"    , (151, 190,  13)),
            ("blue"     , (  0, 139, 208)),
            ("purple"   , (100,  31, 128)),
            ("yellow"   , (255, 204,   0))))
        self.colors             = dict((name, ColorRGB255(*color)) for
            name        , color in (
            ("black"    , (  0,   0,   0)),
            ("grey"     , (160, 160, 160)),
            ("white"    , (255, 255, 255))))
        self.colors.update(self.naub_colors)

    def create_pointer(self, pos):
        pointer = Pointer(pos)
        self.space.add(pointer.body)
        self.pointers.add(pointer)
        return pointer

    def remove_pointer(self, pointer):
        self.pointers.remove(pointer)
        self.space.remove(pointer.body)

    def add_naub(self, naub):
        naub.naubino = self

        if naub not in self.naubs:
            self.naubs.append(naub)

        if self.mode: self.mode.add_naub(naub)

        self.cb.add_naub(naub)

    def remove_naub(self, naub):
        self.cb.remove_naub(naub)

        if self.mode: self.mode.remove_naub(naub)

        if naub in self.naubs:
            self.naubs.remove(naub)

    def pre_remove_naub(self, naub):
        self.cb.pre_remove_naub(naub)

    def add_naubs(self, *naubs):
        for naub in naubs: self.add_naub(naub)

    def add_naub_joint(self, joint):
        self.naubjoints.add(joint)
        self.cb.add_naub_joint(joint)

    def remove_naub_joint(self, joint):
        self.naubjoints.discard(joint)
        self.cb.remove_naub_joint(joint)

    def pre_remove_naub_joint(self, joint):
        self.cb.pre_remove_naub_joint(joint)

    def create_naub_pair(self, pos = (0, 0), rot = 0):
        return self.create_naub_chain(2, pos, rot)

    def create_naub_chain(self, n, pos = (0, 0), rot = 0):
        pos             = Vec2d(*pos)
        naubs           = [Naub(self) for i in xrange(n)]
        restl           = Config.naub_joint_rest_length
        restl           = [restl(a, b) for a, b in zip(naubs, naubs[1:])]
        restl           = tuple(sum(restl[:i]) for i in xrange(len(restl)+1))
        v               = Vec2d(1, 0).rotated(rot)
        for i, naub in enumerate(naubs):
            naub.pos    = pos + v * (-(restl[-1] * 0.5) + restl[i])
        for a, b in zip(naubs, naubs[1:]):
            a.join_naub(b)
        return naubs

    def random_naub_color(self):
        colors = self.naub_colors
        color = colors[sample(colors, 1)[0]]
        return color

    def score_cycle(self, cycle):
        # self.score += len(cycle)
        # property can't do +=
        self.score = self.score + len(cycle)

    def step(self, dt):
        for pointer in self.pointers:
            pointer.step(dt)
        if self.mode: self.mode.step(dt)
        self.space.step(dt)
        danger = self.danger()
        self.warn = Config.warn(danger)
        if Config.fail(danger):
            self.stop()
            self.cb.fail()

    def danger(self):
        danger = 0
        for j in self.naubjoints:
            if (j.a.pos.get_length() < 160
            or  j.b.pos.get_length() < 160):
                danger += 1
        return danger

    def play(self):
        self.mode.play()

    def stop(self):
        self.mode.stop()

    def touch_down(self, pos):
        pos = Vec2d(*pos)
        for naub in self.naubs:
            if naub.shape.point_query(pos):
                pointer = self.create_pointer(pos)
                naub.select(pointer)
                return Touch(self, naub, pointer)
        return None

    def touch_up(self, naub, pointer):
        if naub.alive:
            naub.deselect(pointer)
        self.remove_pointer(pointer)

    def pop_cycle(self, cycle):
        self.score_cycle(cycle)
        for naub in cycle:
            naub.remove()



class Touch(object):

    def __init__(self, naubino, naub, pointer):
        self.naubino        = naubino
        self.naub           = naub
        self.pointer        = pointer

    def move(self, pos):
        self.pointer.pos    = pos

    def up(self):
        self.naubino.touch_up(self.naub, self.pointer)



class Timer(object):

    def __init__(self, interval, callback):
        self.interval = interval
        self.callback = callback
        self.active   = False
        self.time     = 0

    def start(self):
        self.active = True
        return self

    def stop(self):
        self.active = False
        return self

    def step(self, dt):
        if not self.active:
            return self
        self.time += dt
        if self.time >= self.interval:
            self.time -= self.interval
            self.callback()
        return self