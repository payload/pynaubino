# -*- coding: utf-8 -*-
import sys

usage = '''
Usage: naubino [FRONTEND]
       naubino avg

FRONTEND can be "cute", "pig" or "avg"'''.strip()

def main():
    #TODO use getopts
    argv = sys.argv
    if u"pig" in argv:
        print 'pig'
        from Pig import Application
    elif u"avg" in argv:
        print 'avg'
        from Avg import Application
    elif u"cute" in argv:
        print 'cute'
        from Cute import Application
    else:
        print usage
        sys.exit(1)

    from Naubino import Naubino
    naubino = Naubino()
    app = Application(naubino)
    e = app.exec_()
    sys.exit(e)

if __name__ == u"__main__": main()
