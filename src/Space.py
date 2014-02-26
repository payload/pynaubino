import pymunk_, Config

class Space(pymunk_.Space):
    def __init__(self, naubino):
        pymunk_.Space.__init__(self)
        self.naubino = naubino
        self.damping = Config.space_damping()
        self.todos   = []
        self.set_default_collision_handler(None, None, self.collide, None)

    def add(self, *objs):
        for obj in objs:
            pymunk_.Space.add(self, obj)

    def remove(self, *objs):
        for obj in objs:
            pymunk_.Space.remove(self, obj)

    def collide(self, arbiter, *args, **kwargs):
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
        pymunk_.Space.step(self, dt * 0.5)
        pymunk_.Space.step(self, dt * 0.5)
        for todo in self.todos:
            todo()
        self.todos = []