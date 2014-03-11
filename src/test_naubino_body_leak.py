import naubino_base, naubino_mode, ipdb
from utils import *

def main():
    naubino         = naubino_base.Naubino()
    naubino.size    = Vec2d(200, 120)
    mode            = naubino_mode.Autoplay(naubino)
    for i in range(100):
        spam(naubino)
        step(naubino)
        report(naubino)
    for i in range(100):
        step(naubino)
    report(naubino)
    ipdb.set_trace()

def spam(naubino):
    mode = naubino.mode
    for i in xrange(1):
        mode.spam_naub_pair()

def step(naubino):
    for i in xrange(60):
        naubino.step(0.0166)

def report(naubino):
    print
    print_pretty_dict(
        score   = naubino.score,
        naubs   = len(naubino.naubs),
        bodies  = len(naubino.space.bodies))

if __name__ == '__main__':
    main()