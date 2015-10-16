from naubino_base   import Timer
from utils          import *
from random         import random
import pymunk, Config, math

class FlybyMode(object):

    def __init__(self, naubino):
        spammer_interval        = Config.spammer_interval()
        self.spammer            = Timer(spammer_interval, self.spam_naub_bunch)
        self.naubino            = naubino
        naubino.space.gravity   = (0, 40)
        self.center             = FlybyCenter(self)
        self.naubino.mode       = self

    def play(self):
        self.spammer.start()
        self.spam_naub_pair()

    def stop(self):
        self.spammer.stop()

    def step(self, dt):
        self.spammer.step(dt)

    @property
    def size(self):
        return self.naubino.size

    def spam_naub_bunch(self):
        naubs_n     = Config.naubs_per_bunch()
        naubs_max   = Config.max_naubs()
        for i in xrange(naubs_n):
            if len(self.naubino.naubs) > naubs_max:
                return
            self.spam_naub_pair()

    def spam_naub_pair(self):
        pos         = self.random_naub_pos()
        rot         = random() * math.pi * 2
        naubs       = self.naubino.create_naub_chain(2, pos, rot)
        for naub in naubs:
            naub.color = self.naubino.random_naub_color()
        return naubs

    def random_naub_pos(self):
        a = Vec2d(self.size[0] * 0.5, 0)
        b = Vec2d(0, -(self.size[1] * 0.5 + 50))
        return random_vec(a.x, a.y) + b

    def add_naub(self, naub):
        pass

    def remove_naub(self, naub):
        pass



class FlybyCenter(object):

    def __init__(self, mode):
        naubino     = mode.naubino
        space       = naubino.space
        body        = pymunk.Body(None, None)
        body.data   = self
        radius      = Config.naub_radius()
        shape       = pymunk.Circle(body, radius)
        space.add(shape)
        self.body   = body
        self.space  = space

    @property
    def shape(self): return list(self.body.shapes)[0]

    def collide_naub(self, naub, arbiter):
        if not naub.pointer_joints: return
        join            = pymunk.DampedSpring(
            a           = naub.body,
            b           = self.body,
            anchr1      = (0, 0),
            anchr2      = (0, 0),
            rest_length = Config.naub_radius() * 2, 
            stiffness   = 8,
            damping     = 0.1)
        self.space.add(join)
