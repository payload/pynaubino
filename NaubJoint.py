import pymunk

class NaubJoint(object):
    def __init__(self, a, b, naubino):
        a = a.body
        b = b.body
        center = (0,0)
        joint = pymunk.PinJoint(a, b, center, center)
        joint.distance = 40
        joint.bias_coef
        joint.max_bias
        joint.max_force = 2000
        naubino.space.add(joint)

        self.alive = True
        self.joint = joint
        self.naubino = naubino

        self.naubino.add_naub_joint(self)

    def remove(self):
        if self.alive:
            self.alive = False
            self.naubino.pre_remove_naub_joint(self)
            self.naubino.space.remove(self.joint)
            self.naubino.remove_naub_joint(self)
