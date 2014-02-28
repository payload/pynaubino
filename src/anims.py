from __future__ import print_function
from kivy.animation     import Animation
from kivy.clock         import Clock
from utils              import try_many
import itertools

def sequence(
        duration = itertools.cycle([1]),
        anim_end = None, **attrs):
    try: iter(duration)
    except: duration = itertools.cycle([duration])
    attrs.update(duration = duration)
    items       = attrs.items()
    ks          = [k for k, vs in items]
    vss         = zip(*(vs for k, vs in items))
    anims_attrs = (dict(zip(ks, vs)) for vs in vss)
    anims       = [Animation(**anim_attrs) for anim_attrs in anims_attrs]
    seq_anim    = sum(anims[1:], anims[0])
    if anim_end:
        duration_end = try_many(
            lambda: anim_end['duration'],   # maybe not given in anim_end
            lambda: duration[len(ks)],      # maybe out of bounds
            lambda: next(duration),         # maybe iterator exhausted, not in case of itertools.cycle
            lambda: 1)                      # default
        anim    = Animation(duration = duration_end, **anim_end)
        seq_anim.bind(on_complete = lambda _, widget: anim.start(widget))
    return seq_anim

def cycle(**attrs):
    anim        = sequence(**attrs)
    anim.repeat = True
    return anim