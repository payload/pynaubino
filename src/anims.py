from kivy.animation     import Animation
from kivy.clock         import Clock

import itertools
def sequence(duration = itertools.cycle([1]), **attrs):
    try: iter(duration)
    except: duration = itertools.cycle([duration])
    attrs.update(duration = duration)
    items       = attrs.items()
    ks          = [k for k, vs in items]
    vss         = zip(*(vs for k, vs in items))
    anims_attrs = (dict(zip(ks, vs)) for vs in vss)
    anims       = [Animation(**anim_attrs) for anim_attrs in anims_attrs]
    anim        = sum(anims[1:], anims[0])
    return anim

def cycle(**attrs):
    anim        = sequence(**attrs)
    anim.repeat = True
    return anim