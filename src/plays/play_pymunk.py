from pymunk import *
from pymunk.constraint import *

from guppy import hpy
h = hpy()
import gc

def heap():
    #gc.collect()
    print h.heap()

heap()

space = Space()
bodies = []

for i in xrange(1000):
    a = Body(1, 1)
    b = Body(1, 1)
    s = DampedSpring(a, b, (0, 0), (0, 0), 1, 1, 0.1)
    space.add(a)
    space.add(b)
    space.add(s)
    bodies.append(a)
    bodies.append(b)

heap()

for b in bodies:
    for c in b.constraints:
        try: space.remove(c)
        except: pass
    space.remove(b)
bodies = []

heap()