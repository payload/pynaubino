import libavg as avg
from Interfaces import Application, GraphicsScene, GraphicsView, Timer

class Application(Application):
    
    def __init__(self):
        self.scene = None
        self.app = avg.app.App()
    
    def exec_(self):
        self.app.run(self.scene.main_div)
    
    def Timer(self, interval, callback):
        return Timer(interval, callback)

class MainDiv(avg.app.MainDiv):
    
    def __init__(self, scene):
        super(MainDiv, self).__init__()
        self.registerInstance(self, None)
        self.scene = scene
    
    def onInit(self):
        bg = avg.RectNode(
            #pos         = (0, 0),
            size        = self.size,
            fillcolor   = "ffffff",
            fillopacity = 1,
            parent      = self)
        self.reorderChild(bg, 0)
        self.scene.naubino.play()

class GraphicsScene(GraphicsScene):
    
    def __init__(self):
        self.main_div = MainDiv(self)
        self.naub_div = DivNode(
            pos    = (320, 240),
            parent = self.main_div)
        self.__naubino = None
    
    @property
    def naubino(self): return self.__naubino
    @naubino.setter
    def naubino(self, naubino):
        self.__naubino = naubino
    
    def add_item(self, *item): pass
    
    def remove_item(self, *item): pass
    
    def add_naub(self, naub):
        color = "000000"
        CircleNode(
            tag         = naub,
            pos         = lambda: (naub.pos.x, naub.pos.y),
            r           = lambda: naub.radius - 2,
            color       = lambda: ("{:02x}"*3).format(*naub.color.getRgb()),
            parent      = self.naub_div)
    
    def remove_naub(self, naub):
        for node in self.naub_div.children():
            if node.tag == naub:
                node.unlink()
    
    def pre_remove_naub(self, naub): pass
    
    def add_naub_joint(self, joint): pass
    
    def remove_naub_joint(self, joint): pass
    
    def pre_remove_naub_joint(self, joint): pass
    
    def add_update_object(self, obj): pass
    
    def remove_update_object(self, obj): pass
    
    def step(self, dt):
        for node in self.naub_div.children():
            node.update()

class GraphicsView(GraphicsView):
    
    def __init__(self, scene): pass

class Timer(Timer):
    
    
    def __init__(self, interval, callback):
        self.interval = int(interval * 1000)
        self.callback = callback
        self.timer_id = None
    
    def start(self):
        assert not self.timer_id
        self.timer_id = avg.player.setInterval(self.interval, self.callback)
    
    def stop(self):
        assert self.timer_id
        avg.player.clearInterval(self.timer_id)

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