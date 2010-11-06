from Interfaces import *

try:
    import pygame2.sdl.constants as constants
    import pygame2.sdl.image as image
    import pygame2.sdl.event as event
    import pygame2.sdl.video as video
except ImportError:
    raise ImportError("No pygame2.sdl support")

from pygame2.sdl import time
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
    def naubino(self): return self.__naubino
    @naubino.setter
    def naubino(self, naubino):
        self.__naubino = naubino
        
    def add_item(self, *item):
        for x in items:
            if x not in self.__items:
                self.__items.append(x)
                
    def remove_item(self, *item):
        for x in items:
            if x in self.__items:
                self.__items.remove(x)

    def add_naub(self, naub):
        if naub not in self.__objs_graphics:
            graphic = None
            self.__objs_graphics[naub] = graphic

    def remove_naub(self, naub):
        if naub in self.__objs_graphics:
            del self.__objs_graphics[naub]

    def pre_remove_naub(self, naub):
        if naub in self.__objs_graphics:
            self.__objs_graphics[naub].remove_naub()

    def add_naub_joint(self, joint):
        if joint not in self.__objs_graphics:
            #a = Pos(joint.joint.a)
            #b = Pos(joint.joint.b)
            #graphic = LineJoint(self, a, b)
            #self.__objs_cutes[joint] = graphic
            pass

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
        video.init()

        import pygame2.examples
        imgresource = pygame2.examples.RESOURCES.get("logo.bmp")
        surface = image.load_bmp(imgresource)

        screen = video.set_mode(surface.width + 10, surface.height + 10)

        screen.fill(pygame2.Color (255, 255, 255))
        screen.blit(surface, (5, 5))
        screen.flip()