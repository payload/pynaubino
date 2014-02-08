import pymunk

class Space(pymunk.Space):
    def __init__(self):
        pymunk.Space.__init__(self)
        self.damping = 0.4
        self.set_default_collision_handler(None, None, self.collide, None)
        self.__objs = set()

    def add(self, *objs):
        myobjs = self.__objs
        for obj in objs:
            myobjs.add(obj)
            pymunk.Space.add(self, obj)

    def remove(self, *objs):
        myobjs = self.__objs
        for obj in objs:
            if obj not in myobjs: continue
            myobjs.remove(obj)
            pymunk.Space.remove(self, obj)

    def collide(self, space, arbiter, *args, **kwargs):
        if len(arbiter.shapes) != 2: return
        a, b = arbiter.shapes
        if a == None or b == None: return
        a, b = [x.body.naubino_obj for x in [a, b]]

        if hasattr(a, u"collide"): a.collide(b, arbiter)
        if hasattr(b, u"collide"): b.collide(a, arbiter)
