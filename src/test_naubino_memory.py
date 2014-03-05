import naubino_base, naubino_mode, autoplay
from utils import *
import guppy.heapy.RM # is magic!
# README ####################################################################
#
# Run this and in another terminal do following:
#
# $ python -c "from guppy import hpy; hpy().monitor()"
# <Monitor>
# *** Connection 1 opened ***
# <Monitor> sc 1
# <Annex>   int
# >>>       hp.setref()
#
# hit enter in here to pass raw_input("start")
#
# >>>       hp.heap()
#
# look at all the memory leaks!
#
# look at docs: http://guppy-pe.sourceforge.net/
#
#############################################################################

def main():
    naubino         = naubino_base.Naubino()
    naubino.size    = Vec2d(2000, 2000)
    raw_input("start")
    doit(naubino)
    raw_input("end")

def doit(naubino):
    chain_a         = naubino.create_naub_chain(100, (0, -10))
    chain_b         = naubino.create_naub_chain(100, (0,  10))
    for naub in chain_a + chain_b:
        naubino.add_naub(naub)
    naubino.step(0.0166)
    hunter_0        = autoplay.Hunter(naubino, chain_a[ 0], chain_b[ 0])
    hunter_1        = autoplay.Hunter(naubino, chain_a[-1], chain_b[-1])
    hunters         = [hunter_0, hunter_1]
    while hunters:
        for h in hunters[:]:
            if not h.step():
                hunters.remove(h)
        naubino.step(0.0166)
    assert not naubino.naubs
    assert not naubino.pointers

main()