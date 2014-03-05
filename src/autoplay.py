from naubino_base   import *
from utils          import *
from arena          import ArenaMode

class Hunter(object):

    def __init__(self, naubino, naub_a, naub_b):
        self.naubino    = naubino
        self.naub_a     = naub_a
        self.naub_b     = naub_b
        self.touch      = naubino.touch_down(naub_a.pos)
        self.force      = random.uniform(8, 12)

    def step(self):
        touch, naub_a, naub_b = get(self, "touch naub_a naub_b")
        if not touch:
            return False
        if not (naub_a.alive and naub_a.good_merge_naub(naub_b)):
            touch.up()
            return False
        a, b = naub_a.pos, naub_b.pos
        touch.move(a + self.force*(b - a).normalized())
        return True

class AutoplayMode(ArenaMode):

    def __init__(self, naubino):
        self.super.__init__(naubino)
        spammer_interval        = 0.2
        self.spammer            = Timer(spammer_interval, self.spam_naub_bunch)
        self.hunters            = []

    @property
    def super(self): return super(AutoplayMode, self)

    def step(self, dt):
        self.super.step(dt)
        self.touch_a_naub()
        for hunter in self.hunters[:]:
            if not hunter.step():
                self.hunters.remove(hunter)

    def is_in_sight(self, naub):
        return naub.pos.length < self.naubino.size.length / 3

    def is_in_hunt(self, naub):
        for hunter in self.hunters:
            if naub in [hunter.naub_a, hunter.naub_b]:
                return True
        return False

    def touch_a_naub(self):
        naubino = self.naubino
        naubs   = filter(self.is_in_sight, naubino.naubs)
        naubs   = [naub for naub in naubs if not self.is_in_hunt(naub)]
        if not naubs:
            return
        naub_a  = random.choice(naubs)
        naubs.remove(naub_a)
        random.shuffle(naubs)
        for naub_b in naubs:
            if naub_a.good_merge_naub(naub_b):
                hunter = Hunter(naubino, naub_a, naub_b)
                self.hunters.append(hunter)
                break