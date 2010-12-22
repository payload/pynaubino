import pymunk
from pymunk import Vec2d
from Cute import HoverArea, CuteJoint
from Space import Space
from Pointer import Pointer
from PyQt4.QtCore import *
from PyQt4.QtGui import *
from utils import *
from Naub import Naub
from MenuButtons import *
from GameStates import GameStateMachine
from math import cos, sin, pi

# TODO CuteJoint is missing a feature :D
# Cute.update_object is only called if scene.step is called
# which is only the case if naubino.step is called which is wrong
# cause naubino stops stepping if we call naubino.stop
class CuteJoint(CuteJoint):
    def __init__(self, scene, a, b):
        super(CuteJoint, self).__init__(scene, a, b)
        callback = lambda x: self.update_object()
        if hasattr(a, u"pos_changed"):
            self.a.pos_changed = callback
        if hasattr(b, u"pos_changed"):
            self.b.pos_changed = callback
        self.update_object()

class NaubinoMenu(object):
    def __init__(self, scene):
        self.scene = scene
        self.naubino = naubino = scene.naubino
        self.popped_out = True
        self.state_machine = state_machine = GameStateMachine(scene)

        naubino.fail = state_machine.fail

        state_machine.start()

        buttons = self.buttons = QGraphicsRectItem()
        scene.add_item(buttons)

        btn = self.highscore_btn = HighscoreButton(naubino, layer = 10)
        btn.pos = QPointF(0, 0)
        btn.pressed.connect(state_machine.highscore)
        btn.group.setParentItem(buttons)

        posis = [-0.066 + 0.22*x for x in range(0, 4)]
        posis = [x*pi for x in posis]
        posis = [(cos(x), sin(x)) for x in posis]
        posis = [(x[0]*r, x[1]*r) for x, r in zip(posis, [50, 50, 45, 50])]
        posis = [QPointF(*x) for x in posis]

        btns = self.btns = []

        btn = self.play_btn = PlayButton(naubino, layer = 9)
        btn.pos = btn.popped_out_pos = posis[0]
        btn.pressed.connect(state_machine.play)
        btn.group.setParentItem(buttons)
        btns.append(btn)

        btn = self.tutorial_btn = TutorialButton(naubino, layer = 9)
        btn.pos = btn.popped_out_pos = posis[1]
        btn.pressed.connect(state_machine.tutorial)
        btn.group.setParentItem(buttons)
        btns.append(btn)

        btn = self.mute_btn = MuteButton(naubino, layer = 9)
        btn.pos = btn.popped_out_pos = posis[2]
        #btn.pressed.connect(state_machine.tutorial)
        btn.group.setParentItem(buttons)
        btns.append(btn)

        btn = self.settings_btn = SettingsButton(naubino, layer = 9)
        btn.pos = btn.popped_out_pos = posis[3]
        #btn.pressed.connect(state_machine.tutorial)
        btn.group.setParentItem(buttons)
        btns.append(btn)

        for btn in btns:
            j = CuteJoint(scene, self.highscore_btn, btn)
            j.line.setParentItem(buttons)

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

        buttons.setPos(-265, -170)

    def enter(self):
        if self.popped_out: return
        self.popped_out = True
        btns = self.btns
        for btn in btns:
            ani = btn.ani = QPropertyAnimation(btn, u"pos")
            ani.setStartValue(btn.pos)
            ani.setEndValue(btn.popped_out_pos)
            ani.setDuration(300)
            ani.start()

    def leave(self):
        if not self.popped_out: return
        self.popped_out = False
        btns = self.btns
        for btn in btns:
            ani = btn.ani = QPropertyAnimation(btn, u"pos")
            ani.setStartValue(btn.pos)
            ani.setEndValue(QPointF(0, 0))
            ani.setDuration(300)
            ani.start()

    def score_changed(self, score):
        self.highscore_btn.score = score
        
