import pymunk
import random, math
from NaubJoint import NaubJoint
from utils import *

class Naub(object): pass
class Naub(Naub):
    @property
    def pos(self): return self.body.position
    @pos.setter
    def pos(self, x): self.body.position = x

    def __init__(self, naubino, pos = (0, 0)):
        mass = 5
        radius = self.radius = 15
        inertia = pymunk.moment_for_circle(mass, radius, radius)
        body = pymunk.Body(mass, inertia)
        body.naubino_obj = self
        body.position = pos
        shape                   = pymunk.Circle(body, radius)
        shape.friction          = 0.1
        shape.elasticity        = 0.3
        self.color = ColorRGB255(0, 0, 0)
        naubino.space.add(body, shape)

        self.alive = True
        self.cute = None
        self.body = body
        self.shape = shape
        self.cycle_check = 0
        self.cycle_number = 0
        self.naubino = naubino
        self.pointer_joints = {}
        self.naubs_joints = {}
        self.merge_remove = None # callback, see merge

        self.naubino.add_naub(self)

    def remove(self):
        if self.alive:
            self.alive = False
            self.naubino.pre_remove_naub(self)
            self.naubino.space.remove(*self.pointer_joints.values())
            self.unjoin_naubs(*self.naubs_joints)
            self.naubino.space.remove(self.body, self.shape)
            self.naubino.remove_naub(self)

    def select(self, pointer):
        if not self.alive: return
        if pointer in self.pointer_joints: return
        joint               = pymunk.PivotJoint(
            pointer.body, self.body, (0,0), (0,0))
        joint.error_bias    = math.pow(0.5, 60)
        self.naubino.space.add(joint)
        self.pointer_joints[pointer] = joint

    def deselect(self, pointer):
        if not self.alive: return
        if pointer not in self.pointer_joints: return
        joint = self.pointer_joints[pointer]
        self.naubino.space.remove(joint)
        del self.pointer_joints[pointer]

    def join_naub(self, naub, joint = None):
        if not self.alive or not naub.alive: return
        if not joint:
            joint = NaubJoint(self, naub, self.naubino)
            self.naubino.add_naub_joint(joint)
        if naub not in self.naubs_joints:
            self.naubs_joints[naub] = joint
            naub.join_naub(self, joint)

    def unjoin_naub(self, naub):
        if naub not in self.naubs_joints: return
        joint = self.naubs_joints[naub]
        joint.remove()
        self.naubino.remove_naub_joint(joint)
        del self.naubs_joints[naub]
        naub.unjoin_naub(self)

    def unjoin_naubs(self, *naubs):
        for naub in naubs: self.unjoin_naub(naub)

    def merge_naub(self, naub):
        # copy is necessary cause unjoin_naub changes the naubs_joints table
        naubs_joints = naub.naubs_joints.copy()
        for n in naubs_joints:
            naub.unjoin_naub(n)
            self.join_naub(n)
        if naub.merge_remove: naub.merge_remove(self)
        naub.remove()

    def collide(self, other, arbiter):
        if not self.alive or not other.alive: return
        if isinstance(other, Naub):
            self.collide_naub(other, arbiter)

    def collide_naub(self, naub, arbiter):
        if not self.alive or not naub.alive: return

        if not self.pointer_joints: return

        # joker naub behaviour
        if len(self.naubs_joints) == 0 or len(naub.naubs_joints) == 0:
            self.join_naub(naub)
            return

        colors_alike    = are_colors_alike(self.color, naub.color)
        naub_near       = self.is_naub_near(naub)
        impulse_good    = arbiter.total_impulse.length >= 1000

        if colors_alike and not naub_near and impulse_good:
            self.merge_naub(naub)
            cycle = self.test_cycle()
            if cycle: self.pop_cycle(cycle)

    def pop_cycle(self, cycle):
        self.naubino.score_cycle(cycle)
        for naub in cycle:
            naub.remove()

    def test_cycle(self):
        naubs = self.reachable_naubs()
        for naub in naubs:
            naub.cycle_check = 0
            naub.cycle_number = 0
        progress = 1
        for naub in naubs:
            if naub.cycle_number == 0:
                cycle = self.test_cycle_(naub, None, progress, naubs)
                if cycle: return cycle

    def test_cycle_(self, v, pre, progress, naubs):
        v.cycle_number = progress;
        progress += 1;
        v.cycle_check = 1;
        post = v.naubs_joints.keys()
        if pre: post.remove(pre)
        for w in post:
            if w.cycle_number == 0:
                cycle = self.test_cycle_(w, v, progress, naubs)
                if cycle: return cycle
            if w.cycle_check == 1:
                cycle = [naub
                    for naub in naubs
                    if (naub.cycle_number >= w.cycle_number
                    and naub.cycle_check == 1)]
                if cycle: return cycle
        v.cycle_check = 2

    def is_naub_near(self, naub):
        if naub in self.naubs_joints: return True
        for n in self.naubs_joints:
            if naub in n.naubs_joints: return True
        return False

    def reachable_naubs(self, visited = None):
        if not visited: visited = []
        elif self in visited: return []
        visited.append(self)
        nodes = [self]
        for x in self.naubs_joints:
            nodes.extend(x.reachable_naubs(visited))
        return nodes

