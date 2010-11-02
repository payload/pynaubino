import pymunk
from pymunk import Vec2d
from Cute import Cute, CuteNaub, CuteJoint
from Space import Space
from Pointer import Pointer
from PyQt4.QtCore import *
from PyQt4.QtGui import *
from utils import *
from Naub import Naub

class Button(Cute):
    pressed  = pyqtSignal(QGraphicsSceneMouseEvent)
    released = pyqtSignal(QGraphicsSceneMouseEvent)
    
    @property
    def pos(self):
        pos = self.group.pos()
        pos = pos.x(), pos.y()
        return Vec2d(pos)
    @pos.setter
    def pos(self, pos):
        pos = Vec2d(pos)
        self.group.setPos(pos.x, pos.y)

    @property
    def radius(self): return self.__radius
    @radius.setter
    def radius(self, radius):
        if radius != self.__radius:
            self.__radius = radius
            rect = QRectF(-radius, -radius, radius*2, radius*2)
            self.elli.setRect(rect)

    def __init__(self, naubino, layer = 1, rect = False):
        self.naubino = naubino
        self.group = group = QGraphicsItemGroup()
        Cute.__init__(self, group)

        self.set_clickable(group, True)
        def mousePressEvent(event):
            if not hasattr(event, "naubino_pointer"): return
            if event.button() == Qt.LeftButton:
                self.pressed.emit(event)

        def mouseReleaseEvent(event):
            if not hasattr(event, "naubino_pointer"): return
            if event.button() == Qt.LeftButton:
                self.released.emit(event)
            
        group.mousePressEvent = mousePressEvent
        group.mouseReleaseEvent = mouseReleaseEvent
        
        group.setZValue(layer)

        self.__radius = 0

        self.elli = elli = QGraphicsRectItem(group) if rect else QGraphicsEllipseItem(group)
        elli.setPen(QPen(Qt.NoPen))
        elli.setBrush(QColor("black"))
        elli.setRotation(5)

        self.text = text = QGraphicsTextItem("???", group)
        font = text.font()
        font.setBold(True)
        text.setFont(font)
        text.setDefaultTextColor(QColor("white"))

        naubino.add_cute(self)

class State(QState):
    def __init__(self, naubino, state):
        QState.__init__(self, state)
        self.naubino = naubino

class HighscoreState(State):
    def onEntry(self, event):
        print("enter highscore")

    def onExit(self, event):
        print("exit highscore")

class StartState(State):
    def onEntry(self, event):
        print("enter start")

    def onExit(self, event):
        print("exit start")

class PlayState(State):
    def onEntry(self, event):
        print("enter play")
        self.naubino.play()

    def onExit(self, event):
        print("exit play")
        self.naubino.stop()

class TutorialState(State):
    def onEntry(self, event):
        print("enter tutorial")

    def onExit(self, event):
        print("exit tutorial")

class FailState(State):
    def onEntry(self, event):
        print("enter fail")

    def onExit(self, event):
        print("exit fail")

class MenuButton(Button):
    def __init__(self, naubino, radius, fontsize, text, cw, ch, rect = False):
        Button.__init__(self, naubino, rect = rect)

        self.radius = radius

        font = self.text.font()
        font.setPixelSize(self.radius * fontsize)
        self.text.setFont(font)
        self.text.setPlainText(text)

        rect = self.elli.boundingRect()
        pos = Vec2d(rect.x(), rect.y())
        pos += Vec2d(radius, radius)
        rect = self.text.boundingRect()
        w, h = rect.width(), rect.height()
        pos -= Vec2d(cw*w, ch*h)
        self.text.setPos(pos.x, pos.y)

class PlayButton(MenuButton):
    def __init__(self, naubino):
        MenuButton.__init__(self, naubino, 15, 1.8, "▸", 0.43, 0.565)

class TutorialButton(Button):
    def __init__(self, naubino):
        MenuButton.__init__(self, naubino, 15, 1.5, "¿", 0.55, 0.5)

class HighscoreButton(Button):
    def __init__(self, naubino):
        MenuButton.__init__(self, naubino, 17, 1.8, "5", 0.53, 0.5, rect=True)

class Menu(QObject):
    play = pyqtSignal()
    tutorial = pyqtSignal()
    highscore = pyqtSignal()
    
    def __init__(self, naubino):
        QObject.__init__(self)
        self.naubino = naubino
        
        self.highscore_btn = btn = HighscoreButton(naubino)
        btn.pos = -270, -170
        btn.pressed.connect(self.highscore)

        self.play_btn = btn = PlayButton(naubino)
        btn.pos = -225, -160
        btn.pressed.connect(self.play)

        self.tutorial_btn = btn = TutorialButton(naubino)
        btn.pos = -265, -125
        btn.pressed.connect(self.tutorial)

        self.__init_state_machine()
        self.state_machine.start()

    def __init_state_machine(self):
        self.state_machine = state_machine = QStateMachine()
        naubino = self.naubino

        no_play = QState(state_machine)
        play    = PlayState(naubino, state_machine)

        sf    = QState(no_play)
        start = StartState(naubino, sf)
        fail  = FailState(naubino, sf)

        tutorial  = TutorialState(naubino, no_play)
        highscore = HighscoreState(naubino, no_play)

        no_play.addTransition(self.play, play)
        play.addTransition(self.highscore, fail)
        sf.addTransition(self.tutorial, tutorial)
        sf.addTransition(self.highscore, highscore)
        tutorial.addTransition(self.highscore, highscore)
        highscore.addTransition(self.tutorial, tutorial)

        no_play.setInitialState(sf)
        sf.setInitialState(start)
        state_machine.setInitialState(no_play)