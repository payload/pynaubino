from Interfaces import *
import pymunk
from pymunk import Vec2d

import pygame
from pygame import constants
from pygame import image
from pygame import event
from pygame import display
from pygame import draw
from pygame import time

class Pos(object):
    @property
    def pos(self): return self.get_pos()
    @pos.setter
    def pos(self, pos): self.set_pos(pos)

    def __init__(self, x):
        if   isinstance(x, pymunk.Body):
            self.get_pos = lambda: x.position
            self.set_pos = lambda pos: setattr(x, u"position", pos)
        else:
            raise TypeError(type(x))

class LineJoint(object):
    def __init__(self, scene, a, b):
        self.scene = scene
        self.color = pygame.Color(0, 0, 0)
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

class CircleNaub(object):
    def __init__(self, scene, naub):
        self.scene = scene
        self.naub = naub
        scene.add_item(self)
        scene.add_update_object(self)
    
    def paint(self, surface):
        pos = self.naub.pos + Vec2d(300, 200)
        pos = map(int, pos)
        return draw.circle(surface, pygame.Color(0, 0, 0), pos, 15)

    def update_object(self):
        pass

class Application(Application):
    def __init__(self, naubino):
        super(Application, self).__init__()
        self.naubino = naubino
        naubino.app  = self
        self.__update_objects = []
        self.__items = []
        self.__objs_graphics = {}
        
        display.init()
        screen = self.screen = display.set_mode((600, 400))
        pygame.time.set_timer(pygame.USEREVENT+1, 20)

        screen.fill(pygame.Color(255, 255, 255))
        display.flip()
        self.paint()

    def exec_(self):
        self.naubino.play()
        okay = True
        clock = pygame.time.Clock()
        while okay:
            for ev in event.get():
                if False: pass
                elif ev.type == constants.QUIT:
                    okay = False
                elif ev.type == constants.KEYDOWN and ev.key == constants.K_ESCAPE:
                    okay = False
            dt = clock.tick(60) / 1000.0
            self.step(dt)
        display.quit()

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
        self.naubino.step(dt)
        for obj in self.__update_objects:
            obj.update_object()
        self.paint()

    def paint(self):
        screen = self.screen
        screen.fill(pygame.Color(255, 255, 255))
        
        rects = []
        surface = screen
        for item in self.items:
            rect = item.paint(surface)
            rects.append(rect)
        
        display.update() # TODO use rects as parameter?