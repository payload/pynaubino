from PyQt4.QtCore import QStateMachine, QState, pyqtSignal

class State(QState):
    def __init__(self, scene, state):
        super(QState, self).__init__(state)
        self.scene = scene
        self.naubino = scene.naubino

class PlayState(State):
    def onEntry(self, event):
        self.naubino.play()

    def onExit(self, event):
        self.naubino.stop()

class TutorialState(State):
    def onEntry(self, event):
        print u"enter tutorial"

    def onExit(self, event):
        print u"exit tutorial"

class GameStateMachine(QStateMachine):
    play = pyqtSignal()
    tutorial = pyqtSignal()
    highscore = pyqtSignal()
    fail = pyqtSignal()
    
    def __init__(self, scene):
        from FailState import FailState
        from HighscoreState import HighscoreState
        from StartState import StartState
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
        play.addTransition(self.fail, fail)
        sf.addTransition(self.tutorial, tutorial)
        sf.addTransition(self.highscore, highscore)
        tutorial.addTransition(self.highscore, highscore)
        highscore.addTransition(self.tutorial, tutorial)

        no_play.setInitialState(sf)
        sf.setInitialState(start)
        state_machine.setInitialState(no_play)
        