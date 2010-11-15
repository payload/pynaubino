from PyQt4.QtCore import QObject, QPropertyAnimation, pyqtProperty

class ItemFader(QObject):
    def get_opacity(self): return self.item.opacity()
    def set_opacity(self, x): self.item.setOpacity(x)
    opacity = pyqtProperty(float, get_opacity, set_opacity)

    def __init__(self, item):
        super(ItemFader, self).__init__()
        self.item = item

        ani = self.fade_in_ani = QPropertyAnimation(self, "opacity")
        def fade_in_finished():
            pass
        ani.finished.connect(fade_in_finished)

        ani = self.fade_out_ani = QPropertyAnimation(self, "opacity")
        def fade_out_finished():
            self.item.setVisibile(False)
        ani.finished.connect(fade_out_finished)

    def fade_in(self, opacity = 1.0, duration = 1.0):
        self.item.setVisible(True)
        self.fade(opacity, duration)

    def fade_out(self, opacity = 0.0, duration = 1.0):
        self.fade(opacity, duration)

    def fade(self, opacity, duration):
        ani = self.fade_in_ani
        ani.setEndValue(opacity)
        ani.setDuration(duration * 1000)
        ani.start()
