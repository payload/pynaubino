from plain import *
import unittest
from Naub import Naub

class TestNaub(unittest.TestCase):
    def setUp(self):
        self.naubino = Naubino()

    def tearDown(self):
        pass
    
    def test_add_and_remove(self):
        naubino = self.naubino
        naub = Naub(naubino)
        self.assertIn( naub, naubino.cutes )
        self.assertIn( naub.body, naubino.space.bodies )
        self.assertIn( naub.shape, naubino.space.shapes )
        naub.remove()
        self.assertNotIn( naub, naubino.cutes )
        self.assertIn( naub.body, naubino.space.bodies )
        self.assertIn( naub.shape, naubino.space.shapes )
        naubino.step(1)
        self.assertNotIn( naub, naubino.cutes )
        self.assertNotIn( naub.body, naubino.space.bodies )
        self.assertNotIn( naub.shape, naubino.space.shapes )

    def test_merge(self):
        naubino = self.naubino
        a = Naub(naubino)
        b = Naub(naubino)
        self.assertIn( a.body, naubino.space.bodies )
        self.assertIn( b.body, naubino.space.bodies )
        a.merge_naub(b)
        naubino.step(1)
        self.assertIn( a.body, naubino.space.bodies )
        self.assertNotIn( b.body, naubino.space.bodies )

if __name__ == "__main__": unittest.main()