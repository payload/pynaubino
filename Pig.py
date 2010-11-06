from Interfaces import *
import pymunk
from pymunk import Vec2d

try:
    import pygame2
    from pygame2.sdl import constants
    from pygame2.sdl import image
    from pygame2.sdl import event
    from pygame2.sdl import video
    from pygame2.sdlext import draw
    from pygame2.sdl import time
except ImportError:
    raise ImportError("No pygame2.sdl support")

class Pos:
    @property
    def pos(self): return self.get_pos()
    @pos.setter
    def pos(self, pos): self.set_pos(pos)

    def __init__(self, x):
        if   isinstance(x, pymunk.Body):
            self.get_pos = lambda: x.position
            self.set_pos = lambda pos: setattr(x, "position", pos)
        else:
            raise TypeError(type(x))

class Timer(Timer):
    __timers = []

    def __init__(self, interval, callback):
        super(Timer, self).__init__(interval, callback)
        self.__interval = int(interval * 1000)
        self.__callback = callback
        self.__timer = None

    def start(self):
        if self.__timer: return
        if not time.was_init(): time.init()
        self.__timer = timer = time.add_timer(self.__interval, self.__my_callback)
        self.__timers.append(timer)

    def stop(self):
        timer = self.__timer
        if not __timer: return
        self.__timers.remove(timer)
        time.remove_timer(__timer)
        if not self.__timers: time.quit()

    def __my_callback(self):
        self.__callback()
        return self.__interval

class LineJoint:
    def __init__(self, scene, a, b):
        self.scene = scene
        self.color = pygame2.Color(0, 0, 0)
        self.a = a
        self.b = b
        self.width = 4

        scene.add_item(self)
        scene.add_update_object(self)
    
    def paint(self, surface):
        color = self.color
        a = self.a.pos + Vec2d(300, 200)
        b = self.b.pos + Vec2d(300, 200)
        width = self.width
        return draw.line(surface, color, a, b, width)

    def update_object(self):
        pass

class CircleNaub:
    def __init__(self, scene, naub):
        self.scene = scene
        self.naub = naub
        scene.add_item(self)
        scene.add_update_object(self)
    
    def paint(self, surface):
        pos = self.naub.pos + Vec2d(300, 200)
        return draw.circle(surface, pygame2.Color(0, 0, 0), pos, 15)

    def update_object(self):
        pass

class Application(Application):
    def __init__(self):
        super(Application, self).__init__()

    def exec_(self):
        okay = True
        while okay:
            for ev in event.get():
                if ev.type == constants.QUIT:
                    okay = False
                if ev.type == constants.KEYDOWN and ev.key == constants.K_ESCAPE:
                    okay = False
        video.quit()

    def Timer(self, interval, callback):
        return Timer(interval, callback)

    def CuteNaub(self, naubino, naub):
        return CuteNaub(naubino, naub)

    def CuteJoint(self, naubino, a, b):
        return CuteJoint(naubino, a, b)
 
class GraphicsScene(GraphicsScene):
    def __init__(self):
        super(GraphicsScene, self).__init__()
        self.__update_objects = []
        self.__items = []
        self.__objs_graphics = {}

    @property
    def items(self): return self.__items
    
    @property
    def naubino(self): return self.__naubino
    @naubino.setter
    def naubino(self, naubino):
        self.__naubino = naubino
        
    def add_item(self, *items):
        for x in items:
            if x not in self.__items:
                self.__items.append(x)
                
    def remove_item(self, *items):
        for x in items:
            if x in self.__items:
                self.__items.remove(x)

    def add_naub(self, naub):
        if naub not in self.__objs_graphics:
            graphic = CircleNaub(self, naub)
            self.__objs_graphics[naub] = graphic

    def remove_naub(self, naub):
        if naub in self.__objs_graphics:
            del self.__objs_graphics[naub]

    def pre_remove_naub(self, naub):
        if naub in self.__objs_graphics:
            self.__objs_graphics[naub].remove_naub()

    def add_naub_joint(self, joint):
        if joint not in self.__objs_graphics:
            a = Pos(joint.joint.a)
            b = Pos(joint.joint.b)
            graphic = LineJoint(self, a, b)
            self.__objs_graphics[joint] = graphic

    def remove_naub_joint(self, joint):
        if joint in self.__objs_graphics:
           del self.__objs_graphics[joint]

    def pre_remove_naub_joint(self, joint):
        if joint in self.__objs_graphics:
            self.__objs_graphics[joint].remove_joint()

    def add_update_object(self, obj):
        if obj not in self.__update_objects:
            self.__update_objects.append(obj)

    def remove_update_object(self, obj):
        if obj in self.__update_objects:
            self.__update_objects.remove(obj)

    def step(self, dt):
        for obj in self.__update_objects:
            obj.update_object()

class GraphicsView(GraphicsView):
    def __init__(self, scene : GraphicsScene):
        self.scene = scene
        
        video.init()
        screen = self.screen = video.set_mode(600, 400)
        timer = self.timer = Timer(0.02, self.paint)
        timer.start()

        screen.fill(pygame2.Color(255, 255, 255))
        screen.flip()
        self.paint()

    def paint(self):
        screen = self.screen
        
        rects = []
        surface = screen
        for item in self.scene.items:
            rect = item.paint(surface)
            rects.append(rect)
        
        screen.update(rects)