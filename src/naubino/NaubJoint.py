import pymunk, Config

class NaubJoint(object):

    def __init__(self, a, b, naubino = None):
        self.a = a
        self.b = b

        len_min = Config.naub_joint_len_min(a, b)
        len_max = Config.naub_joint_len_max(a, b)

        self.spring = pymunk.DampedSpring(
            a           = a.body,
            b           = b.body,
            anchr1      = (0, 0),
            anchr2      = (0, 0),
            rest_length = Config.naub_joint_rest_length(a, b),
            stiffness   = Config.naub_joint_stiffness(),
            damping     = Config.naub_joint_damping())

        self.alive = True
        self.tag        = None # fill with whatever you like
        self.__naubino  = None
        self.naubino    = naubino

    @property
    def naubino(self):
        return self.__naubino

    @naubino.setter
    def naubino(self, naubino):
        assert not self.__naubino
        self.__naubino = naubino
        if naubino:
            naubino.space.add(self.spring)
            naubino.add_naub_joint(self)

    @property
    def endpoints(self):
        spring = self.spring
        return spring.a.position + spring.anchr1, spring.b.position + spring.anchr2

    def endpoints_fast(self):
        spring = self.spring
        a, b   = spring.a.position, spring.b.position
        aa, ba = spring.anchr1, spring.anchr2
        return a.x + aa.x, a.y + aa.y, b.x + ba.x, b.y + ba.y

    def remove(self):
        if self.alive:
            self.alive = False
            self.naubino.pre_remove_naub_joint(self)
            self.naubino.space.remove(self.spring)
            self.naubino.remove_naub_joint(self)
