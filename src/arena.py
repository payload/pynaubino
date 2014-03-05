from naubino_base import *

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
        self.spam_initial_naubs()

    def stop(self):
        self.spammer.stop()

    def step(self, dt):
        self.spammer.step(dt)

    @property
    def size(self):
        return self.naubino.size

    def spam_initial_naubs(self):
        naubino     = self.naubino
        off         = 20
        pos_1       = (   0, -off)
        pos_2       = (-off,  off)
        pos_3       = ( off,  off)
        rot_1       = 0.00 * math.pi
        rot_2       = 0.25 * math.pi
        rot_3       = 0.75 * math.pi
        a,b         = naubino.create_naub_pair(pos_1, rot_1)
        c,d         = naubino.create_naub_pair(pos_2, rot_2)
        e,f         = naubino.create_naub_pair(pos_3, rot_3)
        import random
        colors      = random.sample(naubino.naub_colors.values(), 3)
        print colors
        a.color     = c.color       = colors[0]
        d.color     = f.color       = colors[1]
        e.color     = b.color       = colors[2]

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
        self.color_naubs_randomly(naubs)
        return naubs

    def color_naubs_randomly(self, naubs):
        for naub in naubs:
            naub.color = self.naubino.random_naub_color()

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
