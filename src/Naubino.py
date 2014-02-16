import pymunk
from pymunk import Vec2d
from Space import Space
from Pointer import Pointer
from utils import Pos, random_vec, ColorRGB255
from Naub import Naub
from random import sample, random
import math

class Naubino(object):
    @property
    def score(self): return self.__score
    @score.setter
    def score(self, score):
        if self.__score == score: return
        self.__score = score
        self.score_changed(score)

    @property
    def warn(self): return self.__warn
    @warn.setter
    def warn(self, warn):
        if self.__warn == warn: return
        self.__warn = warn
        self.warn_changed(warn)
    
    def __init__(self, app = None):
        self.naubs = []
        self.naubjoints = set()
        self.naub_center_joints = {}
        self.playing = False
        self.app = app
        self.__score = 0
        self.score_changed = lambda score: None
        self.__warn = False
        self.warn_changed  = lambda warn: None
        self.fail = None
        
        self.naub_colors = (
            ("red",    (229,  53,  23)),
            ("pink",   (226,   0, 122)),
            ("green",  (151, 190,  13)),
            ("blue",   (  0, 139, 208)),
            ("purple", (100,  31, 128)),
            ("yellow", (255, 204,   0)))
        self.colors = (
            ("black",  (  0,   0,   0)),
            ("grey",   (160, 160, 160)),
            ("white",  (255, 255, 255)))
        self.naub_colors = dict((name, ColorRGB255(*color)) for name, color in self.naub_colors)
        self.colors      = dict((name, ColorRGB255(*color)) for name, color in self.colors)
        self.colors.update(self.naub_colors)    
        
        space = self.space = Space()

        pointer = self.pointer = Pointer()
        space.add(pointer.body)

        center = self.center = pymunk.Body(pymunk.inf, pymunk.inf)
        center.position = 0, 0

        self.spammer = Timer(3, self.spam_naub_pair)
        self.difficulty = Timer(20, self.inc_difficulty)

    def add_item(self, *items):
        self.app.add_item(*items)

    def remove_item(self, *items):
        self.app.remove_item(*items)

    def add_naub(self, naub):
        naub.naubino = self

        if naub not in self.naubs:
            self.naubs.append(naub)

        if naub not in self.naub_center_joints:
            a = naub.body
            b = self.center
            anchor = 0, 0
            joint = pymunk.PinJoint(a, b, anchor, anchor)
            joint.distance = 0
            joint.max_bias = 18
            joint.max_force = 100
            self.naub_center_joints[naub] = joint
            self.space.add(joint)

        self.app.add_naub(naub)

    def remove_naub(self, naub):
        self.app.remove_naub(naub)
            
        if naub in self.naub_center_joints:
            joint = self.naub_center_joints[naub]
            del self.naub_center_joints[naub]
            self.space.remove(joint)

        if naub in self.naubs:
            self.naubs.remove(naub)

    def pre_remove_naub(self, naub):
        self.app.pre_remove_naub(naub)

    def add_naubs(self, *naubs):
        for naub in naubs: self.add_naub(naub)

    def add_naub_joint(self, joint):
        self.naubjoints.add(joint)
        self.app.add_naub_joint(joint)

    def remove_naub_joint(self, joint):
        self.naubjoints.discard(joint)
        self.app.remove_naub_joint(joint)

    def pre_remove_naub_joint(self, joint):
        self.app.pre_remove_naub_joint(joint)

    def create_naub_pair(self, pos = (0, 0), rot = 0):
        pos = Vec2d(pos)
        a = Vec2d(-1, 0)
        b = Vec2d( 1, 0)
        a.rotate(rot)
        b.rotate(rot)
        a += pos
        b += pos
        a = Naub(self, a)
        b = Naub(self, b)
        self.add_naub(a)
        self.add_naub(b)
        a.join_naub(b)
        return a, b

    def spam_naub_pair(self):
        pos = self.random_naub_pos()
        rot = random() * math.pi * 2
        a, b = self.create_naub_pair(pos, rot)

        impulse = lambda: random_vec(50, 50)
        a.body.apply_impulse(impulse())
        b.body.apply_impulse(impulse())

        a.color = self.random_naub_color()
        b.color = self.random_naub_color()

        self.add_naubs(a, b)

    def random_naub_pos(self):
        a = Vec2d(350, 0)
        b = Vec2d(0, 220)
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
        self.space.step(dt)
        self.difficulty.step(dt)
        self.spammer.step(dt)
        danger = self.danger()
        self.warn = False if danger < 25 else True
        if danger > 40:
            self.stop()
            if self.fail: self.fail()

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

    def stop(self):
        self.spammer.stop()
        self.difficulty.stop()
        self.reset_difficulty()

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