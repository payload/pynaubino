from naubino_base   import *
from utils          import *

class Hunter(object):

    def __init__(self, naubino, naub_a, naub_b):
        self.naubino    = naubino
        self.naub_a     = naub_a
        self.naub_b     = naub_b
        self.touch      = naubino.touch_down(naub_a.pos)

    def step(self):
        touch, naub_a, naub_b = get(self, "touch naub_a naub_b")
        if not touch:
            return False
        if not (naub_a.alive and naub_a.good_merge_naub(naub_b)):
            touch.up()
            return False
        a, b = naub_a.pos, naub_b.pos
        touch.move(a + 10*(b - a).normalized())
        return True

class AutoplayMode(object):

    def __init__(self, naubino):
        spammer_interval        = 0.2
        self.spammer            = Timer(spammer_interval, self.spam_naub_bunch)
        self.naub_center_joints = {}
        self.naubino            = naubino
        self.center             = pymunk.Body(pymunk.inf, pymunk.inf)
        self.naubino.mode       = self
        self.hunters            = []

    def play(self):
        self.spammer.start()
        self.spam_naub_pair()

    def stop(self):
        self.spammer.stop()

    def step(self, dt):
        self.spammer.step(dt)
        self.touch_a_naub()
        for hunter in self.hunters[:]:
            if not hunter.step():
                self.hunters.remove(hunter)

    def is_in_sight(self, naub):
        return naub.pos.length < self.naubino.size.length / 3

    def is_in_hunt(self, naub):
        for hunter in self.hunters:
            if naub in [hunter.naub_a, hunter.naub_b]:
                return True
        return False

    def touch_a_naub(self):
        naubino = self.naubino
        naubs   = filter(self.is_in_sight, naubino.naubs)
        naubs   = [naub for naub in naubs if not self.is_in_hunt(naub)]
        if not naubs:
            return
        naub_a  = random.choice(naubs)
        naubs.remove(naub_a)
        random.shuffle(naubs)
        for naub_b in naubs:
            if naub_a.good_merge_naub(naub_b):
                hunter = Hunter(naubino, naub_a, naub_b)
                self.hunters.append(hunter)
                break

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
        rot         = random.random() * math.pi * 2
        naubs       = self.naubino.create_naub_chain(2, pos, rot)
        for naub in naubs:
            naub.color = self.naubino.random_naub_color()
        return naubs

    def random_naub_pos(self):
        a = Vec2d(self.size[0] * 0.5 - 30, 0)
        b = Vec2d(0, self.size[1] * 0.5 + 30)
        if random.random() < 0.5:
            a,b = b,a
        if random.random() < 0.5:
            b   = -b
        return random_vec(a.x, a.y) + b

    def add_naub(self, naub):
        joint = pymunk.DampedSpring(
            a           = naub.body,
            b           = self.center,
            anchr1      = (0, 0),
            anchr2      = Config.naub_center_joint_anchor(naub),
            rest_length = Config.naub_center_joint_rest_length(),
            stiffness   = Config.naub_center_joint_stiffness(),
            damping     = Config.naub_center_joint_damping())
        self.naub_center_joints[naub] = joint
        self.naubino.space.add(joint)

    def remove_naub(self, naub):
        joint = self.naub_center_joints[naub]
        del self.naub_center_joints[naub]
        self.naubino.space.remove(joint)
