import pymunk, Config

class Space(pymunk.Space):
    def __init__(self, naubino):
        pymunk.Space.__init__(self)
        self.naubino = naubino
        self.damping = Config.space_damping()
        self.set_default_collision_handler(None, None, self.collide, None)

    def add(self, *objs):
        for obj in objs:
            pymunk.Space.add(self, obj)

    def remove(self, *objs):
        for obj in objs:
            pymunk.Space.remove(self, obj)

    def collide(self, space, arbiter, *args, **kwargs):
        if len(arbiter.shapes) != 2: return
        a, b = arbiter.shapes
        if a == None or b == None: return
        a, b = [self.naubino.body_obj_map.get(x.body) for x in [a, b]]

        if hasattr(a, u"collide"): a.collide(b, arbiter)
        if hasattr(b, u"collide"): b.collide(a, arbiter)

    def step(self, dt):
        pymunk.Space.step(self, dt * 0.5)
        pymunk.Space.step(self, dt * 0.5)