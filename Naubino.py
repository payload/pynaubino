from __future__ import division
import pymunk
from Space import Space
from Pointer import Pointer
from PyQt4.QtCore import *
from PyQt4.QtGui import QColor
from utils import Pos, random_vec
from Naub import Naub
from Menu import NaubinoMenu

class Naubino(object):
    @property
    def score(self): return self.__score
    @score.setter
    def score(self, score):
        if self.__score == score: return
        self.__score = score
        if not self.score_changed: return
        self.score_changed(score)
    
    def __init__(self, app = None):
        self.naubs = []
        self.naub_center_joints = {}
        self.playing = False
        self.app = app
        self.scene = scene = app.scene
        self.__score = 0
        self.score_changed = None

        interval = 1 / 50.0
        def callback(): self.step(interval)
        self.stepper = app.Timer(interval, callback)
        
        pymunk.init_pymunk()
        space = self.space = Space()

        pointer = self.pointer = Pointer()
        space.add(pointer.body)

        center = self.center = pymunk.Body(pymunk.inf, pymunk.inf)
        center.position = 0, 0

        def callback(): self.spam_naub()
        self.spammer = app.Timer(1, callback)

        if scene: scene.naubino = self

    def add_item(self, *items):
        if self.scene: self.scene.add_item(*items)

    def remove_item(self, *items):
        if self.scene: self.scene.remove_item(*items)

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
            joint.max_bias = 100
            joint.max_force = 500
            self.naub_center_joints[naub] = joint
            self.space.add(joint)

        if self.scene: self.scene.add_naub(naub)

    def remove_naub(self, naub):
        if self.scene: self.scene.remove_naub(naub)
            
        if naub in self.naub_center_joints:
            joint = self.naub_center_joints[naub]
            del self.naub_center_joints[naub]
            self.space.remove(joint)

        if naub in self.naubs:
            self.naubs.remove(naub)

    def pre_remove_naub(self, naub):
        if self.scene: self.scene.pre_remove_naub(naub)

    def add_naubs(self, *naubs):
        for naub in naubs: self.add_naub(naub)

    def add_naub_joint(self, joint):
        if self.scene: self.scene.add_naub_joint(joint)

    def remove_naub_joint(self, joint):
        if self.scene: self.scene.remove_naub_joint(joint)

    def pre_remove_naub_joint(self, joint):
        if self.scene: self.scene.pre_remove_naub_joint(joint)

    def create_naub_pair(self, pos = (0, 0)):
        pos = Vec2d(pos)
        a = Vec2d(-30, 0) + pos
        b = Vec2d( 30, 0) + pos

        a = Naub(self, a)
        b = Naub(self, b)
        self.add_naub(a)
        self.add_naub(b)
        a.join_naub(b)
        return a, b

    def spam_naub(self):
        if len(self.naubs) > 16: return
        pos = random_vec(300, 200)
        naub = Naub(self, pos)
        naub.color = self.random_naub_color()
        self.add_naub(naub)

    def spam_naub_pair(self):
        if len(self.naubs) > 16: return
        pos = random_vec(300, 200)
        a, b = self.create_naub_pair(pos)

        impulse = lambda: random_vec(50, 50)
        a.body.apply_impulse(impulse())
        b.body.apply_impulse(impulse())

        a.color = self.random_naub_color()
        b.color = self.random_naub_color()

        self.add_naubs(a, b)

    # TODO
    def random_naub_color(self):
        return QColor(u"black")

    # TODO
    def score_cycle(self, cycle):
        self.score += len(cycle)

    def step(self, dt):
        self.space.step(dt)
        if self.scene: self.scene.step(dt)

    def play(self):
        self.spammer.start()
        self.stepper.start()

    def stop(self):
        self.spammer.stop()
        self.stepper.stop()