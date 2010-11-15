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

        state_machine.start()

        buttons = self.buttons = QGraphicsRectItem()
        scene.add_item(buttons)

        btn = self.highscore_btn = HighscoreButton(naubino, layer = 10)
        btn.pos = QPointF(0, 0)
        btn.pressed.connect(state_machine.highscore)
        btn.group.setParentItem(buttons)

        btn = self.play_btn = PlayButton(naubino, layer = 9)
        btn.pos = btn.popped_out_pos = QPointF(45, 10)
        btn.pressed.connect(state_machine.play)
        btn.group.setParentItem(buttons)

        btn = self.tutorial_btn = TutorialButton(naubino, layer = 9)
        btn.pos = btn.popped_out_pos = QPointF(5, 45)
        btn.pressed.connect(state_machine.tutorial)
        btn.group.setParentItem(buttons)

        j = CuteJoint(scene, self.highscore_btn, self.play_btn)
        j.line.setParentItem(buttons)
        j = CuteJoint(scene, self.highscore_btn, self.tutorial_btn)
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
            ani = btn.ani = QPropertyAnimation(btn, u"pos")
            ani.setStartValue(btn.pos)
            ani.setEndValue(btn.popped_out_pos)
            ani.setDuration(300)
            ani.start()

    def leave(self, event):
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
        