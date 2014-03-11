import naubino_base, naubino_mode, autoplay, naubivy
from utils              import *
from kivy.clock         import Clock
from kivy.core.window   import Window
from kivy.app           import App



class MyApp(App):

    def build(self):
        naubino             = naubino_base.Naubino()
        game                = naubivy.Game(naubino)
        self.game           = game
        #self.clock          = Clock.schedule_interval(self.step, 0.0166)
        self.hunters        = []
        self.initialise()
        Window.clearcolor   = (1, 1, 1, 1)
        for i in range(10 * 60):
            self.step(0.0166)
        return game

    def initialise(self):
        naubino         = self.game.naubino
        for i in xrange(-10, 10):
            x           = i % 4
            y           = i / 4
            pos         = (x, y)
            naubino.create_naub_pair(pos)
        naubino.step(0.0166)
        naubs           = naubino.naubs
        self.hunter(naubs[0], naubs[-1])
    
    def hunter(self, a, b):
        naubino     = self.game.naubino
        hunter      = autoplay.Hunter(naubino, a, b)
        self.hunters.append(hunter)

    def step(self, dt):
        hunters = self.hunters
        for h in hunters[:]:
            if not h.step():
                hunters.remove(h)
        self.game.update(dt)
        return bool(hunters)

def main():
    app = MyApp()
    #app.run()
    for i in range(10):
        app.build()

if __name__ == '__main__':
    main()