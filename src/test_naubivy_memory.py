import naubino_base, naubino_mode, autoplay, naubivy
from utils          import *
from kivy.clock     import Clock
from kivy.base      import EventLoop
from kivy.core.window import Window
from kivy.app       import App
import guppy.heapy.RM

class MyApp(App):

    def build(self):
        naubino             = naubino_base.Naubino()
        game                = naubivy.Game(naubino)
        self.game           = game
        self.clock          = Clock.schedule_interval(self.step, 0.0166)
        self.hunters        = []
        Window.on_key_up    = self.on_key_up
        Window.clearcolor   = (1, 1, 1, 1)
        return game
    
    def on_key_up(self, key, *_):
        try:    key = chr(key)
        except: return
        if key in '\r\n':
            self.initialise()

    def initialise(self):
        naubino         = self.game.naubino
        chain_a         = naubino.create_naub_chain(10, (0, -40))
        chain_b         = naubino.create_naub_chain(10, (0,  40))
        naubino.step(0.0166)
        hunter_0        = autoplay.Hunter(naubino, chain_a[ 0], chain_b[ 0])
        hunter_1        = autoplay.Hunter(naubino, chain_b[-1], chain_a[-1])
        self.hunters.extend([hunter_0, hunter_1])

    def step(self, dt):
        hunters = self.hunters
        for h in hunters[:]:
            if not h.step():
                hunters.remove(h)
        self.game.update(dt)

def main():
    app = MyApp()
    app.run()

if __name__ == '__main__':
    main()