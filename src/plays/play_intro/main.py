#from utils                  import *
from kivy.clock             import Clock
from kivy.core.window       import Window
from kivy.app               import App
from kivy.uix.widget        import Widget
from kivy.uix.label         import Label
from kivy.uix.screenmanager import Screen, ScreenManager, FadeTransition
from kivy.uix.floatlayout   import FloatLayout
from kivy.uix.relativelayout import RelativeLayout
from kivy.animation         import Animation
from kivy.vector            import Vector
from kivy.graphics          import *
from kivy.properties        import *



class NaubinoLabel(Label):

    def get_o_center(self):
        o1x, o1y    = self.anchors.get('o1', (0, 0))
        o2x, o2y    = self.anchors.get('o2', (0, 0))
        ow          = (o2x - o1x) * 0.9
        oh          = ow
        w, h        = self.texture_size
        x           = self.x - w*0.5 + o1x + (o2x - o1x) * 0.05 + ow*0.5
        y           = self.y + h * 0.2 + oh*0.5
        return x, y

    o_center = AliasProperty(get_o_center, None, bind = 'x y anchors'.split())

class FirstNaub(Widget): pass

class Intro(RelativeLayout):

    def __init__(self):
        super(Intro, self).__init__()
        self.fade_in    = Animation(
            opacity     = 1,
            transition  = 'in_expo')
        naub            = FirstNaub()
        self.naub       = naub
        #self.add_widget(naub)
        self.fade_in_splash()

    def fade_in_splash(self):
        label           = NaubinoLabel(
            opacity     = 0)
        self.add_widget(label)
        self.fade_in.start(label)
        self.label = label
        Clock.schedule_once(lambda t:
            self.fade_in_first_naub(), 2)

    def fade_in_first_naub(self):
        naub, label     = self.naub, self.label

    def screenplay(self):
        self.fade_in_splash()
        self.wait_for("touch_down")
        self.fade_in_first_naub()
        self.fade_out_splash()
        self.move_first_naub()
        self.explode_first_naub()
        pass






class MyApp(App):

    def build(self):
        return Intro()



def main():
    app = MyApp()
    app.run()

if __name__ == '__main__':
    main()
