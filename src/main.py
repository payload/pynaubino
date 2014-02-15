# -*- coding: utf-8 -*-
import sys
from PyQt4.QtCore import *
from PyQt4.QtGui import *
from Naubino import Naubino
from Menu import NaubinoMenu

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
        print 'cute, pig or avg?'
        sys.exit(1)

    naubino = Naubino()
    app = Application(naubino)
    e = app.exec_()
    sys.exit(e)

if __name__ == u"__main__": main()
