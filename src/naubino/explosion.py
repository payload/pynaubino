from naubino_base       import  *
from kivy.animation     import  Animation
import                          naub_spec



class FirstNaub(Naub): pass

class MyNaub(Naub): pass

class ExplodingNaub(Naub):

    def explode(self):
        self.remove()
        naubino         = self.naubino
        spec            = naub_spec.spec("a-b b-c c-d d-e e-f f-g g-h h-i i-j j-a")
        palette         = naubino.naub_colors.values()
        spec.colorize(palette)
        spec.position_on_circle(10)

        for naub in spec.naubs:
            naub.naubino    = naubino
        for join in spec.joins:
            join.naubino    = naubino

        for naub in spec.naubs:
            naub.shape.group    = id(self)

            away            = naub.pos * 15
            move_away       = Animation(
                pos             = away,
                duration        = 3,
                transition      = "out_quad")
            move_away.start(naub)
            move_away.bind(
                on_complete     = lambda anim, naub: self.moved_away(naub))

    def moved_away(self, naub):
        naub.shape.group    = 0
        self.naubino.mode.naub_attach_to_center(naub)



class Mode(object):

    def __init__(self, naubino):
        spammer_interval        = Config.spammer_interval()
        self.spammer            = Timer(spammer_interval, self.spam_naub_bunch)
        self.naub_center_joints = {}
        self.naubino            = naubino
        self.center             = pymunk.Body(pymunk.inf, pymunk.inf)
        naubino.space.add(self.center)
        self.naubino.mode       = self

    def create_first_naub(self, pos):
        naub            = FirstNaub(pos = pos)
        #naub.radius     = 0
        naub.color      = self.naubino.naub_colors['red']
        grow            = Animation(
            radius      = 8,
            transition  = "in_cubic",
            duration    = 3)
        #grow.start(naub)
        self.naubino.add_naub(naub)

    def create_start_naub(self):
        naubino         = self.naubino
        naub            = ExplodingNaub(naubino)
        naub.color      = naubino.naub_colors['red']
        return naub

    def play(self):
        #self.spammer.start()
        #self.spam_initial_naubs()
        pass

    def stop(self):
        self.spammer.stop()

    def step(self, dt):
        #self.spammer.step(dt)
        pass

    @property
    def size(self):
        return self.naubino.size

    def spam_initial_naubs(self):
        naubino     = self.naubino
        import naub_spec, random
        spec        = naub_spec.spec("a-b b-c c-a")
        palette     = list(naubino.naub_colors.values())
        random.shuffle(palette)
        spec.colorize(palette)
        spec.position_on_circle(radius = 20)
        for naub in spec.naubs:
            naub.naubino    = naubino
        for join in spec.joins:
            join.naubino    = naubino

    def spam_naub_bunch(self):
        naubs_n     = Config.naubs_per_bunch()
        naubs_max   = Config.max_naubs()
        for i in xrange(naubs_n):
            if len(self.naubino.naubs) > naubs_max:
                return
            self.spam_naub_pair()

    def spam_naub_pair(self):
        pos         = self.random_naub_pos()
        rot         = random() * math.pi * 2
        naubs       = self.naubino.create_naub_chain(2, pos, rot)
        self.color_naubs_randomly(naubs)
        return naubs

    def color_naubs_randomly(self, naubs):
        for naub in naubs:
            naub.color = self.naubino.random_naub_color()

    def random_naub_pos(self):
        a = Vec2d(self.size[0] * 0.5 - 30, 0)
        b = Vec2d(0, self.size[1] * 0.5 + 30)
        if random() < 0.5:
            a,b = b,a
        if random() < 0.5:
            b   = -b
        return random_vec(a.x, a.y) + b

    def naub_attach_to_center(self, naub):
        joint = pymunk.DampedSpring(
            a           = naub.body,
            b           = self.center,
            anchr1      = (0, 0),
            anchr2      = Config.naub_center_joint_anchor(naub),
            rest_length = Config.naub_center_joint_rest_length(),
            stiffness   = Config.naub_center_joint_stiffness(),
            damping     = Config.naub_center_joint_damping())
        self.naub_center_joints[naub] = joint
        self.naubino.space.add(joint)

    def naub_detach_from_center(self, naub):
        joint = self.naub_center_joints[naub]
        del self.naub_center_joints[naub]
        self.naubino.space.remove(joint)

    def naub_attached_to_center(self, naub):
        return naub in self.naub_center_joints

    def add_naub(self, naub):
        if isinstance(naub, MyNaub):
            self.naub_attach_to_center(naub)
        elif isinstance(naub, FirstNaub):
            pass

    def remove_naub(self, naub):
        if self.naub_attached_to_center(naub):
            self.naub_detach_from_center(naub)