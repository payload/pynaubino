import pymunk

class Space(pymunk.Space):
    def __init__(self):
        pymunk.Space.__init__(self)
        self.damping = 0.4
        self.set_default_collision_handler(None, None, self.collide, None)
        self.__to_remove = set()

    def remove(self, *objs):
        to_remove = self.__to_remove
        for obj in objs:
            if obj in to_remove: continue
            to_remove.add(obj)
            def callback(obj):
                to_remove.remove(obj)
                pymunk.Space.remove(self, obj)
            self.add_post_step_callback(callback, obj)

    def collide(self, space, arbiter, *args, **kwargs):
        if len(arbiter.shapes) != 2: return
        a, b = arbiter.shapes
        if a == None or b == None: return
        a, b = [x.body.naubino_obj for x in [a, b]]

        if hasattr(a, "collide"): a.collide(b, arbiter)
        if hasattr(b, "collide"): b.collide(a, arbiter)