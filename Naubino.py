import pymunk
from Cute import CuteNaub, CuteJoint
from Space import Space
from Pointer import Pointer
from PyQt4.QtCore import *
from utils import Pos, random_vec
from Naub import Naub
from Menu import NaubinoMenu

class Naubino:
    def __init__(self, scene):
        self.cutes = []
        self.cute_naubs = []
        self.cute_joints = []
        self.objs_cutes = {}
        self.naub_center_joints = {}
        self.playing = False
        self.scene = scene

        timer = self.stepper = QTimer()
        timer.setInterval(50)
        timer.timeout.connect(lambda: self.step(1.0 / timer.interval()))
        
        pymunk.init_pymunk()
        space = self.space = Space()

        pointer = self.pointer = Pointer()
        self.space.add(pointer.body)

        center = self.center = pymunk.Body(pymunk.inf, pymunk.inf)
        center.position = 0, 0

        spammer = self.spammer = QTimer()
        spammer.setInterval(1000)
        spammer.timeout.connect(self.spam_naub)

        self.menu = NaubinoMenu(self)

    def add_item(self, *items):
        if self.scene: self.scene.add_item(*items)

    def remove_item(self, *items):
        if self.scene: self.scene.remove_item(*items)
    
    def add_cute(self, cute):
        if cute not in self.cutes:
            self.cutes.append(cute)

    def remove_cute(self, cute):
        if cute in self.cutes:
            self.cutes.remove(cute)

    def add_cute_naub(self, cute):
        if cute not in self.cute_naubs:
            self.cute_naubs.append(cute)
            self.add_cute(cute)

    def remove_cute_naub(self, cute):
        if cute in self.cute_naubs:
            self.cute_naubs.remove(cute)
            self.remove_cute(cute)

    def add_naub(self, naub):
        naub.naubino = self

        if naub not in self.objs_cutes:
            cute = CuteNaub(self, naub)
            self.objs_cutes[naub] = cute

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

    def remove_naub(self, naub):
        if naub in self.objs_cutes:
            del self.objs_cutes[naub]
            # dont remove the cute naub now, it will remind you by calling
            # remove_cute_naub
            
        if naub in self.naub_center_joints:
            joint = self.naub_center_joints[naub]
            del self.naub_center_joints[naub]
            self.space.remove(joint)

    def pre_remove_naub(self, naub):
        if naub in self.objs_cutes:
            self.objs_cutes[naub].remove_naub()

    def add_naubs(self, *naubs):
        for naub in naubs: self.add_naub(naub)

    def add_cute_joint(self, cute):
        if cute not in self.cute_joints:
            self.cute_joints.append(cute)
        self.add_cute(cute)

    def remove_cute_joint(self, cute):
        if cute in self.cute_joints:
            self.cute_joints.remove(cute)
        self.remove_cute(cute)

    def add_naub_joint(self, joint):
        if joint not in self.objs_cutes:
            a = Pos(joint.joint.a)
            b = Pos(joint.joint.b)
            cute = CuteJoint(self, a, b)
            self.objs_cutes[joint] = cute

    def remove_naub_joint(self, joint):
        if joint in self.objs_cutes:
           del self.objs_cutes[joint]

    def pre_remove_naub_joint(self, joint):
        if joint in self.objs_cutes:
            self.objs_cutes[joint].remove_joint()

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
        if len(self.cute_naubs) > 16: return
        pos = random_vec(300, 200)
        naub = Naub(self, pos)
        #naub.color = random_naub_color()
        self.add_naub(naub)

    def spam_naub_pair(self):
        if len(self.cute_naubs) > 16: return
        pos = random_vec(300, 200)
        a, b = self.create_naub_pair(pos)

        impulse = lambda: random_vec(50, 50)
        a.body.apply_impulse(impulse())
        b.body.apply_impulse(impulse())

        a.color = random_naub_color()
        b.color = random_naub_color()

        self.add_naubs(a, b)

    def step(self, dt):
        self.space.step(dt)
        cutes = self.cute_naubs + self.cute_joints
        for cute in cutes:
            cute.update_object()
            #cute.update()

    def play(self):
        self.spammer.start()
        self.stepper.start()

    def stop(self):
        self.spammer.stop()
        self.stepper.stop()