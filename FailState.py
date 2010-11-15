from GameStates import State
from ItemFader import ItemFader
from PyQt4.QtCore import Qt
from PyQt4.QtGui import (QGraphicsRectItem, QPixmap, QGraphicsPixmapItem,
    QGraphicsTextItem, QGraphicsSimpleTextItem)

class FailState(State):
    def __init__(self, scene, state):
        super(FailState, self).__init__(scene, state)
        self.__score = 0
        self.layer = layer = QGraphicsRectItem()
        layer.setVisible(False)
        layer.setOpacity(0)
        self.fader = ItemFader(layer)
        scene.add_item(layer)

        if False:
            pixmap = QPixmap("fail.png")
            self.splash = g = QGraphicsPixmapItem()
            g.setPixmap(pixmap)
            self.__relpos(g)
            g.setParentItem(layer)

        self.title = g = QGraphicsSimpleTextItem()
        g.setText("Naub Overflow")
        font = g.font()
        font.setPixelSize(30)
        font.setBold(True)
        g.setFont(font)
        r = g.boundingRect()
        w, h = r.width(), r.height()
        self.__relpos(g, y = -1.33)
        g.setParentItem(layer)

        self.name_input = g = QGraphicsTextItem()
        font = g.font()
        font.setPixelSize(20)
        g.setFont(font)
        g.setPlainText('Anony Mous')
        self.__relpos(g)
        g.setTextInteractionFlags(Qt.TextEditable)
        g.setParentItem(layer)

        def callback(e):
            key, text = e.key(), e.text()
            g = self.name_input
            type(g).keyPressEvent(g, e)
            self.__relpos(g)
            
        g.keyPressEvent = callback

    def __relpos(self, g, x = -0.5, y = -0.5):
        r = g.boundingRect()
        w, h = r.width(), r.height()
        g.setPos(x * w, y * h)

    def onEntry(self, event):
        self.__score = self.naubino.score
        
        g = self.name_input
        g.setPlainText('Anony Mous')
        self.__relpos(g)
        
        self.fader.fade_in()
        naubino = self.scene.naubino
        naubs = naubino.naubs[:]
        for naub in naubs: naub.remove()

    def onExit(self, event):
        name, score = self.name_input.toPlainText(), self.__score
        self.scene.highscore.submit_score(name, score)
        self.fader.fade_out()
