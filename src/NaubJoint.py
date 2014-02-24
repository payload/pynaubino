import pymunk_, Config

class NaubJoint(object):

    def __init__(self, a, b, naubino):
        self.a = a
        self.b = b

        len_min = Config.naub_joint_len_min(a, b)
        len_max = Config.naub_joint_len_max(a, b)

        self.spring = pymunk_.DampedSpring(
            a           = a.body,
            b           = b.body,
            anchr1      = (0, 0),
            anchr2      = (0, 0),
            rest_length = Config.naub_joint_rest_length(a, b),
            stiffness   = Config.naub_joint_stiffness(),
            damping     = Config.naub_joint_damping())
        naubino.space.add(self.spring)

        self.alive = True
        self.naubino = naubino

        self.naubino.add_naub_joint(self)

    @property
    def endpoints(self):
        spring = self.spring
        return spring.a.position + spring.anchr1, spring.b.position + spring.anchr2

    def remove(self):
        if self.alive:
            self.alive = False
            self.naubino.pre_remove_naub_joint(self)
            self.naubino.space.remove(self.spring)
            self.naubino.remove_naub_joint(self)
