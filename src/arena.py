from Naubino import *

class ArenaMode(object):

    def __init__(self, naubino):
        spammer_interval        = Config.spammer_interval()
        self.spammer            = Timer(spammer_interval, self.spam_naub_bunch)
        self.naub_center_joints = {}
        self.naubino            = naubino
        self.center             = pymunk.Body(pymunk.inf, pymunk.inf)
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
        a = Vec2d(self.size[0] * 0.5 - 30, 0)
        b = Vec2d(0, self.size[1] * 0.5 + 30)
        if random() < 0.5:
            a,b = b,a
        if random() < 0.5:
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
