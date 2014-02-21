import pymunk
from pymunk import Vec2d
from Space import Space
from Pointer import Pointer
from utils import Pos, random_vec, ColorRGB255
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
        self.naub_center_joints = {}
        self.playing            = False
        self.cb                 = Naubino.Callbacks()
        self.__score            = 0
        self.__warn             = False
        self.space              = space = Space()
        self.pointers           = set()
        self.center             = center = pymunk.Body(pymunk.inf, pymunk.inf)
        self.size               = 600, 400
        self.px_per_mm          = 3.7839
        center.position = 0, 0
        self.spammer            = Timer(Config.spammer_interval(), self.spam_naub_bunch)
        self.difficulty         = Timer(Config.difficulty_interval(), self.inc_difficulty)
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

        if naub not in self.naub_center_joints:
            joint = pymunk.DampedSpring(
                a           = naub.body,
                b           = self.center,
                anchr1      = (0, 0),
                anchr2      = Config.naub_center_joint_anchor(naub),
                rest_length = Config.naub_center_joint_rest_length(),
                stiffness   = Config.naub_center_joint_stiffness(),
                damping     = Config.naub_center_joint_damping())
            self.naub_center_joints[naub] = joint
            self.space.add(joint)

        self.cb.add_naub(naub)

    def remove_naub(self, naub):
        self.cb.remove_naub(naub)

        if naub in self.naub_center_joints:
            joint = self.naub_center_joints[naub]
            del self.naub_center_joints[naub]
            self.space.remove(joint)

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
        pos = Vec2d(pos)
        naub_a          = Naub(self)
        naub_b          = Naub(self)
        rest_length     = Config.naub_joint_rest_length(naub_a, naub_b)
        v               = Vec2d(rest_length * 0.5, 0)
        v.rotate(rot)
        naub_a.pos      = pos - v
        naub_b.pos      = pos + v
        self.add_naub(naub_a)
        self.add_naub(naub_b)
        naub_a.join_naub(naub_b)
        return naub_a, naub_b

    def spam_naub_bunch(self):
        for i in xrange(Config.naubs_per_bunch()):
            if len(self.naubs) > Config.max_naubs():
                return
            self.spam_naub_pair()

    def spam_naub_pair(self):
        pos = self.random_naub_pos()
        rot = random() * math.pi * 2
        a, b = self.create_naub_pair(pos, rot)
        a.color = self.random_naub_color()
        b.color = self.random_naub_color()
        self.add_naubs(a, b)

    def random_naub_pos(self):
        a = Vec2d(self.size[0] * 0.45, 0)
        b = Vec2d(0, self.size[1] * 0.6)
        if random() < 0.5:
            a,b = b,a
        if random() < 0.5:
            b = -b
        return random_vec(a.x, a.y) + b

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
        self.difficulty.step(dt)
        self.spammer.step(dt)
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

    def inc_difficulty(self):
        self.spammer.interval = self.spammer.interval * 0.8

    def reset_difficulty(self):
        self.spammer.interval = 1

    def play(self):
        self.spammer.start()
        self.difficulty.start()
        self.spammer.callback()

    def stop(self):
        self.spammer.stop()
        self.difficulty.stop()
        self.reset_difficulty()

    def touch_down(self, pos):
        pos = Vec2d(pos)
        for naub in self.naubs:
            if naub.shape.point_query(pos):
                pointer = self.create_pointer(pos)
                naub.select(pointer)
                return Touch(self, naub, pointer)
        return None

    def touch_up(self, naub, pointer):
        naub.deselect(pointer)



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
