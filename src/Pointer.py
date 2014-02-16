import pymunk

class Pointer(object):

    def __init__(self, pos):
        body = pymunk.Body(pymunk.inf, pymunk.inf)
        body.position = pos
        self.body = body
        self.pos  = pymunk.Vec2d(body.position)

    def step(self, dt):
        body_pos = self.body.position.interpolate_to(self.pos, 0.25)
        self.body.velocity = (body_pos - self.body.position)
        self.body.position = body_pos