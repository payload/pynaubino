import libavg as avg
from utils import *
import Config



class Application(object):

    def __init__(self, naubino):
        self.app                        = avg.app.App()
        self.main_div                   = MainDiv(self)
        self.naubino                    = naubino
        naubino.cb.score_changed        = self.score_changed
        naubino.cb.add_naub             = self.add_naub
        naubino.cb.remove_naub          = self.remove_naub
        naubino.cb.add_naub_joint       = self.add_naub_joint
        naubino.cb.remove_naub_joint    = self.remove_naub_joint

    @property
    def naub_div(self):
        return self.main_div.naub_div

    @property
    def joint_div(self):
        return self.main_div.joint_div

    @property
    def score_node(self):
        return self.main_div.score_node

    def exec_(self):
        self.app.run(self.main_div)

    def score_changed(self, score):
        self.score_node.text = unicode(score)

    def add_naub(self, naub):
        color = color_hex(Config.foreground_color())
        node = CircleNode(
            tag         = naub,
            pos         = lambda: (naub.pos.x, naub.pos.y),
            r           = lambda: naub.radius - 2,
            color       = lambda: color_hex(naub.color),
            parent      = self.naub_div)
        node.subscribe(node.CURSOR_DOWN, lambda e: self.cursor_down_on_naub(e, node))

    def cursor_down_on_naub(self, event, node):
        contact = event.contact
        if not contact: return # XXX contact could be None. I consider this a bug in libavg.
        pos     = self.naub_div.getRelPos(event.pos)
        pointer = self.naubino.create_pointer(Vec2d(pos))
        contact.subscribe(contact.CURSOR_MOTION, lambda e: self.cursor_motion_on_naub(e, node, pointer))
        contact.subscribe(contact.CURSOR_UP    , lambda e: self.cursor_up_on_naub(e, node, pointer))
        naub    = node.tag
        naub.select(pointer)

    def cursor_motion_on_naub(self, event, node, pointer):
        pos = self.naub_div.getRelPos(event.pos)
        pointer.pos = Vec2d(pos)

    def cursor_up_on_naub(self, event, node, pointer):
        naub = node.tag
        naub.deselect(pointer)
        self.naubino.remove_pointer(pointer)

    def remove_naub(self, naub):
        for node in self.naub_div.children():
            if node.tag == naub:
                node.unlink()

    def add_naub_joint(self, joint):
        LineNode(
            tag     = joint,
            pos1    = lambda: (joint.a.pos.x, joint.a.pos.y),
            pos2    = lambda: (joint.b.pos.x, joint.b.pos.y),
            strokewidth = lambda: 4,
            parent  = self.joint_div)

    def remove_naub_joint(self, joint):
        for node in self.joint_div.children():
            if node.tag == joint:
                node.unlink()

    def step(self, dt):
        self.naubino.step(dt)
        for node in self.naub_div.children() + self.joint_div.children():
            node.update()



class DivNode(avg.DivNode):

    def __init__(self, tag = None, parent = None, **kwargs):
        super(DivNode, self).__init__(**kwargs)
        self.registerInstance(self, parent)
        self.tag = tag

    def children(self):
        return [self.getChild(i) for i in xrange(self.getNumChildren())]



class CircleNode(avg.DivNode):

    def __init__(self,
            tag     = None,
            color   = lambda: color_hex(Config.background_color()),
            pos     = lambda: (0.0, 0.0),
            r       = lambda: 15,
            parent  = None):
        super(CircleNode, self).__init__()
        self.registerInstance(self, parent)
        self.circle         = avg.CircleNode(
            fillopacity     = 1,
            parent          = self)
        self.tag            = tag
        self.color_         = color
        self.pos_           = pos
        self.r_             = r
        self.update()

    def update(self):
        self.pos            = self.pos_()
        self.circle.r       = self.r_()
        self.circle.color   = self.circle.fillcolor = self.color_()



class LineNode(avg.LineNode):

    def __init__(self,
            tag     = None,
            pos1    = lambda: (0.0, 0.0),
            pos2    = lambda: (0.0, 0.0),
            strokewidth = lambda: 1,
            color   = lambda: color_hex(Config.foreground_color()),
            parent  = None, **kwargs):
        super(LineNode, self).__init__(**kwargs)
        self.registerInstance(self, parent)
        self.tag            = tag
        self.color_         = color
        self.pos1_          = pos1
        self.pos2_          = pos2
        self.strokewidth_   = strokewidth
        self.update()

    def update(self):
        self.pos1           = self.pos1_()
        self.pos2           = self.pos2_()
        self.strokewidth    = self.strokewidth_()
        self.color          = self.color_()



class MainDiv(avg.app.MainDiv):

    def __init__(self, app):
        super(MainDiv, self).__init__()
        self.registerInstance(self, None)
        self.app = app

    def onInit(self):
        self.app.naubino.size = tuple(self.size)
        bg = avg.RectNode(
            #pos         = (0, 0),
            size        = self.size,
            fillcolor   = color_hex(Config.background_color()),
            fillopacity = 1,
            parent      = self)
        center = self.size * 0.5
        self.joint_div = DivNode(
            pos    = center,
            parent = self)
        self.naub_div = DivNode(
            pos    = center,
            parent = self)
        self.menu_div = DivNode(
            parent = self)
        self.score_node = avg.WordsNode(
            pos    = (25, 25),
            text   = u"0",
            color  = color_hex(Config.foreground_color()),
            parent = self.menu_div)
        self.app.naubino.play()

    def onFrame(self):
        dt = avg.player.getFrameDuration()
        self.app.step(dt / 1000.0)