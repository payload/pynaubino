from PyQt4.QtCore import (QStateMachine, QState, pyqtSignal, pyqtProperty,
    QPropertyAnimation)
from PyQt4.QtGui import *

class State(QState):
    def __init__(self, scene, state):
        QState.__init__(self, state)
        self.scene = scene
        self.naubino = scene.naubino

class HighscoreState(State):
    def onEntry(self, event):
        print("enter highscore")

    def onExit(self, event):
        print("exit highscore")

class StartState(State):
    @pyqtProperty(float)
    def splash_opacity(self): return self.splash.opacity()
    @splash_opacity.setter
    def splash_opacity(self, x): self.splash.setOpacity(x)
    
    def __init__(self, scene, state):
        super(StartState, self).__init__(scene, state)
        self.ani = None
        pixmap = QPixmap("splash.png")
        self.splash = splash = QGraphicsPixmapItem(pixmap)
        splash.setOpacity(0)
        splash.setPos(-300, -200)
    
    def onEntry(self, event):
        self.scene.add_item(self.splash)
        
        ani = self.ani = QPropertyAnimation(self, "splash_opacity")
        ani.setEndValue(1)
        ani.setDuration(1000)
        ani.start()

    def onExit(self, event):
        ani = self.ani = QPropertyAnimation(self, "splash_opacity")
        ani.setEndValue(0)
        ani.setDuration(1000)
        ani.finished.connect(lambda: self.scene.remove_item(self.splash))
        ani.start()

class PlayState(State):
    def onEntry(self, event):
        self.naubino.play()

    def onExit(self, event):
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

class GameStateMachine(QStateMachine):
    play = pyqtSignal()
    tutorial = pyqtSignal()
    highscore = pyqtSignal()
    
    def __init__(self, scene):
        super(GameStateMachine, self).__init__()
        self.scene = scene

        state_machine = self
        
        no_play = QState(state_machine)
        play    = PlayState(scene, state_machine)

        sf    = QState(no_play)
        start = StartState(scene, sf)
        fail  = FailState(scene, sf)

        tutorial  = TutorialState(scene, no_play)
        highscore = HighscoreState(scene, no_play)

        no_play.addTransition(self.play, play)
        play.addTransition(self.highscore, fail)
        sf.addTransition(self.tutorial, tutorial)
        sf.addTransition(self.highscore, highscore)
        tutorial.addTransition(self.highscore, highscore)
        highscore.addTransition(self.tutorial, tutorial)

        no_play.setInitialState(sf)
        sf.setInitialState(start)
        state_machine.setInitialState(no_play)
        