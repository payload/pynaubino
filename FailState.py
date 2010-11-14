from GameStates import State
from ItemFader import ItemFader
from PyQt4.QtGui import QGraphicsRectItem, QPixmap, QGraphicsPixmapItem

class FailState(State):
    def __init__(self, scene, state):
        super(FailState, self).__init__(scene, state)
        self.layer = layer = QGraphicsRectItem()
        layer.setVisible(False)
        layer.setOpacity(0)
        self.fader = ItemFader(layer)
        scene.add_item(layer)

        pixmap = QPixmap("fail.png")
        self.splash = splash = QGraphicsPixmapItem()
        splash.setPixmap(pixmap)
        r = splash.boundingRect()
        w, h = r.width(), r.height()
        splash.setPos(-0.5 * w, -0.5 * h)
        splash.setParentItem(layer)

    def onEntry(self, event):
        self.fader.fade_in()
        naubino = self.scene.naubino
        naubs = naubino.naubs[:]
        for naub in naubs: naub.remove()

    def onExit(self, event):
        self.fader.fade_out()
