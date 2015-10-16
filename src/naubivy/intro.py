from kivy.base          import Builder
from kivy.uix.label     import Label
from kivy.properties    import *

class NaubinoLabel(Label):

    def get_o_center(self):
        o1x, o1y    = self.anchors.get('o1', (0, 0))
        o2x, o2y    = self.anchors.get('o2', (0, 0))
        ow          = (o2x - o1x) * 0.9
        oh          = ow
        w, h        = self.texture_size
        x           = self.x - w*0.5 + o1x + (o2x - o1x) * 0.05 + ow*0.4925
        y           = self.y + h * 0.2 + oh*0.515
        return x, y

    def get_o_radius(self):
        o1x, o1y    = self.anchors.get('o1', (0, 0))
        o2x, o2y    = self.anchors.get('o2', (0, 0))
        radius      = (o2x - o1x) * 0.363
        return radius

    o_center    = AliasProperty(get_o_center, None, bind = 'x y anchors'.split())
    o_radius    = AliasProperty(get_o_radius, None, bind = 'anchors'.split())

Builder.load_string('''
#:kivy 1.0

<NaubinoLabel>:
    text:           "naubin[anchor=o1]o[anchor=o2]"
    markup:         True
    font_name:      "Comfortaa-Light.ttf"
    font_size:      self.size[1]
    color:          0, 0, 0, 1
    pos_hint:       {'center_x': 0.5, 'center_y': 0.66}
    size_hint:      0, 0.2
    size:           0, 0
''')