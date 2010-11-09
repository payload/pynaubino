from GameStates import State
from ItemFader import ItemFader
from PyQt4.QtCore import *
from PyQt4.QtGui import *

class StartState(State):
    def __init__(self, scene, state):
        super(StartState, self).__init__(scene, state)
        self.splash = splash = QGraphicsPixmapItem()
        self.fader = fader = ItemFader(splash)

        pixmap = QPixmap("splash.png")
        splash.setVisible(False)
        splash.setPixmap(pixmap)
        splash.setOpacity(0)
        splash.setPos(-300, -200)
        self.scene.add_item(self.splash)

    def onEntry(self, event):
        self.fader.fade_in()

    def onExit(self, event):
        self.fader.fade_out()
