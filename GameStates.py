class State(object):
    def __init__(self, machine):
        self.machine = machine
        self.scene   = machine.scene
        self.naubino = machine.naubino
        
    def enter(self):
        print self, "enter"
        
    def leave(self):
        print self, "leave"

from PyQt4.QtCore import *
from PyQt4.QtGui import *
from ItemFader import ItemFader

class OverlayFader(object):
    def __init__(self, scene, overlay):
        self.overlay = overlay
        self.fader = fader = ItemFader(overlay)
        self.fade_in  = fader.fade_in
        self.fade_out = fader.fade_out
        
        overlay.setVisible(False)
        overlay.setOpacity(0)
        overlay.setPos(-300, -200)
        scene.add_item(overlay)

class SplashFader(OverlayFader):
    def __init__(self, scene, splash_filename):
        overlay = QGraphicsPixmapItem()
        pixmap = QPixmap(splash_filename)
        overlay.setPixmap(pixmap)
        super(SplashFader, self).__init__(scene, overlay)
        
class ColorFader(OverlayFader):
    def __init__(self, scene, color):
        overlay = QGraphicsRectItem()
        overlay.setRect(0, 0, 600, 400)
        overlay.setPen(QPen(Qt.NoPen))
        color = QColor(color) if type(color) is str else QColor(*color)
        overlay.setBrush(QBrush(color))
        super(ColorFader, self).__init__(scene, overlay)

class StartState(State):
    def __init__(self, machine):
        super(StartState, self).__init__(machine)
        self.splash = SplashFader(self.scene, "splash.png")

    def enter(self):
        self.splash.fade_in()

    def leave(self):
        self.splash.fade_out()

class PlayState(State):
    def enter(self):
        self.scene.menu.leave()
        self.scene.menu.play_btn.text.setPlainText("p")
        self.naubino.play()

    def leave(self):
        self.naubino.stop()
        self.scene.menu.play_btn.text.setPlainText("P")

class TutorialState(State):
    pass
 
from HighscoreState import HighscoreState   
#class HighscoreState(State):
#    pass

class SettingsState(State):
    pass        

class PauseState(State):
    def __init__(self, machine):
        super(PauseState, self).__init__(machine)
        self.splash = ColorFader(self.scene, "white")

    def enter(self):
        self.splash.fade_in()

    def leave(self):
        self.splash.fade_out()

from FailState import FailState
#class FailState(State):
#    pass

class DictP(dict):
    def __add__(self, other):
        c = self.copy()
        c.update(other)
        return c
        
    def __sub__(self, other):
        c = self.copy()
        for x in other:
            if x in c:
                del c[x]
        return c

class GameStateMachine(object):
    def __init__(self, scene):
        self.scene = scene
        self.naubino = scene.naubino
    
        self.start_s     = start_s     = StartState(self)
        self.play_s      = play_s      = PlayState(self)
        self.tutorial_s  = tutorial_s  = TutorialState(self)
        self.highscore_s = highscore_s = HighscoreState(self)
        self.settings_s  = settings_s  = SettingsState(self)
        self.pause_s     = pause_s     = PauseState(self)
        self.fail_s      = fail_s      = FailState(self)
        
        self.current_states = set([start_s])
        start_s.enter()
            
        direct = DictP({
            "play"     : [play_s],
            "tutorial" : [tutorial_s],
            "highscore": [highscore_s],
            "settings" : [settings_s],
        })
            
        start_s    .transitions = direct
        play_s     .transitions = direct + {"play": [pause_s], "fail": [fail_s]}
        tutorial_s .transitions = direct - ["tutorial"]
        highscore_s.transitions = direct - ["highscore"]
        settings_s .transitions = direct - ["settings"]
        pause_s    .transitions = direct
        fail_s     .transitions = {"highscore": [highscore_s]}

    def signal(self, signal):
        current_s = self.current_states
        # all states which are triggered
        triggered_s = set([state for state in current_s
            if signal in state.transitions])
        # all transitions of the triffered states
        after_s = [state.transitions[signal] for state in triggered_s]
        # all states which get activated by the transitions
        after_s = set([state for state in sum(after_s, [])])
        # all states which doesnt change their activation
        not_changed_s = triggered_s.intersection(after_s)
        # triggered_s contains now only states which get inactive
        triggered_s.difference_update(not_changed_s)
        # inactive states are deleted from the currently active states
        current_s.difference_update(triggered_s)
        # after_s contains now only newly activated states
        after_s.difference_update(not_changed_s)
        # active states are added to the currently active states
        current_s.update(after_s)
        for state in triggered_s: state.leave()
        for state in after_s: state.enter()
        
    def fail(self): self.signal("fail")
    def play(self): self.signal("play")
    def start(self): self.signal("start")
    def highscore(self): self.signal("highscore")
    def tutorial(self): self.signal("tutorial")
