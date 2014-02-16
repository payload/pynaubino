import libavg as avg
from utils import *



class Application(object):

    def __init__(self, naubino):
        self.app = avg.app.App()
        self.main_div = MainDiv(self)
        self.joint_div = DivNode(
            pos    = (320, 240),
            parent = self.main_div)
        self.naub_div = DivNode(
            pos    = (320, 240),
            parent = self.main_div)
        self.menu_div = DivNode(
            parent = self.main_div)
        self.score_node = avg.WordsNode(
            pos    = (25, 25),
            text   = u"0",
            color  = "000000",
            parent = self.menu_div)
        self.naubino                    = naubino
        naubino.cb.score_changed        = self.score_changed
        naubino.cb.add_naub             = self.add_naub
        naubino.cb.remove_naub          = self.remove_naub
        naubino.cb.add_naub_joint       = self.add_naub_joint
        naubino.cb.remove_naub_joint    = self.remove_naub_joint

    def exec_(self):
        self.app.run(self.main_div)

    def score_changed(self, score):
        self.score_node.text = unicode(score)

    def add_naub(self, naub):
        color = "000000"
        node = CircleNode(
            tag         = naub,
            pos         = lambda: (naub.pos.x, naub.pos.y),
            r           = lambda: naub.radius - 2,
            color       = lambda: ("{:02x}"*3).format(*naub.color),
            parent      = self.naub_div)
        node.subscribe(node.CURSOR_DOWN,   lambda e: self.cursor_down_on_naub(e, node))
        node.subscribe(node.CURSOR_MOTION, lambda e: self.cursor_motion_on_naub(e, node))
        node.subscribe(node.CURSOR_UP,     lambda e: self.cursor_up_on_naub(e, node))

    def cursor_down_on_naub(self, event, node):
        node.setEventCapture(event.cursorid)
        naub = node.tag
        naub.select(self.naubino.pointer)

    def cursor_motion_on_naub(self, event, node):
        pos = event.pos
        pos = self.naub_div.getRelPos(pos)
        pos = Vec2d(pos)
        self.naubino.pointer.pos = pos

    def cursor_up_on_naub(self, event, node):
        naub = node.tag
        naub.deselect(self.naubino.pointer)
        try: node.releaseEventCapture(event.cursorid)
        except: pass

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



class CircleNode(avg.CircleNode):

    def __init__(self,
            tag     = None,
            color   = lambda: "ffffff",
            pos     = lambda: (0.0, 0.0),
            r       = lambda: 15,
            parent  = None, **kwargs):
        super(CircleNode, self).__init__(**kwargs)
        self.registerInstance(self, parent)
        self.tag            = tag
        self.color_         = color
        self.pos_           = pos
        self.r_             = r
        self.fillopacity    = 1
        self.update()

    def update(self):
        self.pos    = self.pos_()
        self.r      = self.r_()
        self.color  = self.fillcolor = self.color_()



class LineNode(avg.LineNode):

    def __init__(self,
            tag     = None,
            pos1    = lambda: (0.0, 0.0),
            pos2    = lambda: (0.0, 0.0),
            strokewidth = lambda: 1,
            color   = lambda: "000000",
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
        bg = avg.RectNode(
            #pos         = (0, 0),
            size        = self.size,
            fillcolor   = "ffffff",
            fillopacity = 1,
            parent      = self)
        self.reorderChild(bg, 0)
        self.app.naubino.play()

    def onFrame(self):
        dt = avg.player.getFrameDuration()
        self.app.step(dt / 1000.0)