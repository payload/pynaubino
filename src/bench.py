from Naubino import Naubino

def main():
    naubino = Naubino()
    for i in range(10):
        spam(naubino)
        step(naubino)

def spam(naubino):
    for i in xrange(10):
        naubino.spam_naub_pair()

def step(naubino):
    for i in xrange(60):
        naubino.step(0.0166)

if __name__ == '__main__':
    main()