def impulse_good(arbiter):
    'arbiter : pymunk.Arbiter'
    return arbiter.total_impulse.length >= 1000

def naub_mass():
    return 5

def naub_radius():
    return 15

def naub_friction():
    return 0.1

def naub_elasticity():
    return 0.3

import math
def pointer_error_bias():
    return math.pow(0.5, 60)

def space_damping():
    return 0.1

def naub_joint_len_min(a, b):
    'a, b : Naub'
    return (a.radius + b.radius) * 1.2

def naub_joint_len_max(a, b):
    'a, b : Naub'
    return (a.radius + b.radius) * 2

def naub_joint_stiffness():
    return 10

def naub_joint_damping():
    return 30

def naub_center_joint_rest_length():
    return 30

def naub_center_joint_stiffness():
    return 7

def naub_center_joint_damping():
    return 7

def spammer_interval():
    return 3

def difficulty_interval():
    return 20

def warn(danger):
    'danger : int'
    return danger > 25

def fail(danger):
    'danger : int'
    return danger > 40