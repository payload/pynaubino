import pymunk_, Config

class Space(pymunk_.Space):
    def __init__(self, naubino):
        pymunk_.Space.__init__(self)
        self.naubino = naubino
        self.lock    = False
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
        if len(arbiter.shapes) != 2: return
        a, b = arbiter.shapes
        if a == None or b == None: return
        a, b = [x.body.data for x in [a, b]]

        if hasattr(a, u"collide"):
            self.todos.append(lambda: a.collide(b, arbiter))
        if hasattr(b, u"collide"):
            self.todos.append(lambda: b.collide(a, arbiter))

    def step(self, dt):
        self.lock = True
        pymunk_.Space.step(self, dt * 0.5)
        pymunk_.Space.step(self, dt * 0.5)
        self.lock = False
        for todo in self.todos:
            todo()
        self.todos = []