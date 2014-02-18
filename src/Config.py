from utils import *

def background_color():
    return ColorRGB1(1.0, 1.0, 1.0)

def foreground_color():
    return ColorRGB1(0.0, 0.0, 0.0)

def max_naubs():
    return 8000

def impulse_good(arbiter):
    'arbiter : pymunk.Arbiter'
    return arbiter.total_impulse.length >= 1000

def naub_mass():
    return 5

def naub_radius(px_per_mm):
    return 5 * px_per_mm

def naub_friction():
    return 0.1

def naub_elasticity():
    return 0.3

import math
def pointer_error_bias():
    return math.pow(0.5, 60)

def space_damping():
    return 0.1

def naubs_per_bunch():
    return 1

def naub_joint_len_min(a, b):
    'a, b : Naub'
    return (a.radius + b.radius) * 1.6

def naub_joint_len_max(a, b):
    'a, b : Naub'
    return (a.radius + b.radius) * 2

def naub_joint_stiffness():
    return 10

def naub_joint_damping():
    return 30

def naub_center_joint_rest_length():
    return 100

def naub_center_joint_stiffness():
    #return 1
    return 7

def naub_center_joint_damping():
    return 7

def naub_center_joint_anchor(naub):
    #return (naub.body.position.x, 0)
    return (0, 0)

def spammer_interval():
    return 0.1

def difficulty_interval():
    return 20

def warn(danger):
    'danger : int'
    return False#danger > 25

def fail(danger):
    'danger : int'
    return False#danger > 40
