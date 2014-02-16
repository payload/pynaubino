import pymunk

class NaubJoint(object):
    def __init__(self, a, b, naubino):
        self.a = a
        self.b = b

        len_min = (a.radius + b.radius) * 1.2
        len_max = (a.radius + b.radius) * 2

        self.spring = pymunk.DampedSpring(
            a           = a.body,
            b           = b.body,
            anchr1      = (0, 0),
            anchr2      = (0, 0),
            rest_length = len_min,
            stiffness   = 10,
            damping     = 30)
        self.slide = pymunk.SlideJoint(
            a           = a.body,
            b           = b.body,
            anchr1      = (0, 0),
            anchr2      = (0, 0),
            min         = len_min,
            max         = len_max)
        naubino.space.add(self.spring, self.slide)

        self.alive = True
        self.naubino = naubino

        self.naubino.add_naub_joint(self)

    def remove(self):
        if self.alive:
            self.alive = False
            self.naubino.pre_remove_naub_joint(self)
            self.naubino.space.remove(self.spring, self.slide)
            self.naubino.remove_naub_joint(self)
