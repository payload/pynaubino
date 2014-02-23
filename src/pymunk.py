from cymunk import *
inf = float("inf")

__DampedSpring = DampedSpring
def DampedSpring(a, b,
        anchr1      = (0, 0),
        anchr2      = (0, 0),
        rest_length = 0,
        stiffness   = 0,
        damping     = 0):
    return __DampedSpring(a, b, anchr1, anchr2, rest_length, stiffness, damping)