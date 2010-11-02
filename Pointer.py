import pymunk

class Pointer:
    @property
    def pos(self): return self.body.position
    @pos.setter
    def pos(self, x): self.body.position = x

    def __init__(self):
        body = pymunk.Body(pymunk.inf, pymunk.inf)
        body.position = 0, 0
        self.body = body
