from testify import *
from Naubino import Naubino



class SomeTests(TestCase):

    def test_contract_stretched_naub_pair(self):
        naubino = Naubino()
        a, b    = naubino.create_naub_pair()
        a.pos   = a.pos * 2
        b.pos   = b.pos * 2
        before  = a.pos.length, b.pos.length
        naubino.step(0.1)
        after   = a.pos.length, b.pos.length
        for la, lb in zip(after, before):
            assert_lt(la, lb)

    def test_contract_stretched_naub_chain(self):
        naubino = Naubino()
        for length in xrange(2, 10):
            naubs   = naubino.create_naub_chain(length)
            for naub in naubs:
                naub.pos = naub.pos * 2
            before  = sum(naub.pos.length for naub in naubs)
            naubino.step(0.1)
            after   = sum(naub.pos.length for naub in naubs)
            assert_lt(after, before)



if __name__ == '__main__':
    run()
