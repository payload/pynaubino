import pymunk
from pymunk import Vec2d
from Cute import Cute, CuteNaub, CuteJoint
from Space import Space
from Pointer import Pointer
from PyQt4.QtCore import *
from PyQt4.QtGui import *
from utils import *
from Naub import Naub
from MenuButtons import *

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

class Menu(QObject):
    play = pyqtSignal()
    tutorial = pyqtSignal()
    highscore = pyqtSignal()
    
    def __init__(self, naubino):
        QObject.__init__(self)
        self.naubino = naubino
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
        state_machine.setInitialState(play)

class HoverArea(QObject):
    entered  = pyqtSignal(QGraphicsSceneHoverEvent)
    leaved   = pyqtSignal(QGraphicsSceneHoverEvent)
    
    def __init__(self, area = None, rect = None, scene = None):
        QObject.__init__(self)
        if not area:
            area = QGraphicsEllipseItem()
            area.setPen(QPen(Qt.NoPen))
        if not rect: rect = QRect(-0.5, -0.5, 1, 1)
        if scene: scene.add_item(area)
        
        self.area = area
        area.setRect(rect)
        area.setAcceptHoverEvents(True)
        
        def hoverEnterEvent(event):
            self.entered.emit(event)
        area.hoverEnterEvent = hoverEnterEvent

        def hoverLeaveEvent(event):
            self.leaved.emit(event)
        area.hoverLeaveEvent = hoverLeaveEvent

class NaubinoMenu(Menu):
    def __init__(self, naubino):
        Menu.__init__(self, naubino)
        self.popped_out = True

        buttons = self.buttons = QGraphicsRectItem()
        naubino.add_item(buttons)

        btn = self.highscore_btn = HighscoreButton(naubino, layer = 10)
        btn.pos = QPointF(0, 0)
        btn.pressed.connect(self.highscore)
        btn.group.setParentItem(buttons)

        btn = self.play_btn = PlayButton(naubino, layer = 9)
        btn.pos = btn.popped_out_pos = QPointF(45, 10)
        btn.pressed.connect(self.play)
        btn.group.setParentItem(buttons)

        btn = self.tutorial_btn = TutorialButton(naubino, layer = 9)
        btn.pos = btn.popped_out_pos = QPointF(5, 45)
        btn.pressed.connect(self.tutorial)
        btn.group.setParentItem(buttons)

        j = CuteJoint(naubino, self.highscore_btn, self.play_btn)
        j.line.setParentItem(buttons)
        j = CuteJoint(naubino, self.highscore_btn, self.tutorial_btn)
        j.line.setParentItem(buttons)

        self.btns = [self.play_btn, self.tutorial_btn]

        scene = self.naubino.scene
        btn = self.play_btn
        pos = btn.pos
        rect = btn.shape.rect()
        r = pos.x() + rect.width() * 0.5 + 5
        rect = QRectF(-r, -r, 2*r, 2*r)
        hover = self.hover = HoverArea(rect = rect, scene = scene)
        hover.area.setParentItem(buttons)
        hover.area.setZValue(100)
        hover.entered.connect(self.enter)
        hover.leaved.connect(self.leave)

        buttons.setPos(-270, -170)

    def enter(self, event):
        if self.popped_out: return
        self.popped_out = True
        btns = self.btns
        for btn in btns:
            ani = btn.ani = QPropertyAnimation(btn, "pos")
            ani.setStartValue(btn.pos)
            ani.setEndValue(btn.popped_out_pos)
            ani.setDuration(300)
            ani.start()

    def leave(self, event):
        if not self.popped_out: return
        self.popped_out = False
        btns = self.btns
        for btn in btns:
            ani = btn.ani = QPropertyAnimation(btn, "pos")
            ani.setStartValue(btn.pos)
            ani.setEndValue(QPointF(0, 0))
            ani.setDuration(300)
            ani.start()
