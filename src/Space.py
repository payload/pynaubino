import pymunk, Config

class Space(pymunk.Space):
    def __init__(self, naubino):
        pymunk.Space.__init__(self)
        self.naubino = naubino
        self.damping = Config.space_damping()
        self.todos   = []
        self.set_default_collision_handler(None, None, self.collide, None)

    def add(self, *objs):
        for obj in objs:
            pymunk.Space.add(self, obj)

    def remove(self, *objs):
        for obj in objs:
            pymunk.Space.remove(self, obj)

    def collide(self, _, arbiter, *args, **kwargs):
        a, b = [x.body.data for x in arbiter.shapes]
        # try except is faster than hasattr,
        # especially because hasattr is implemented via try except (hearsay)
        try:
            collide = a.collide
            self.todos.append(lambda: collide(b, arbiter))
        except AttributeError: pass
        try:
            collide = b.collide
            self.todos.append(lambda: collide(a, arbiter))
        except AttributeError: pass

    def step(self, dt):
        pymunk.Space.step(self, dt)
        for todo in self.todos:
            todo()
        self.todos = []