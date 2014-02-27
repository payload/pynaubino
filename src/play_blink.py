from kivy.app           import App
from kivy.uix.widget    import Widget
from kivy.graphics      import *
from kivy.core.window   import Window
from kivy.vector        import Vector
import anims

class MyApp(App):

    def build(self):
        dot         = Widget()
        with dot.canvas:
            self.color = Color(0.5, 0.5, 1)
            Ellipse(
                pos     = (100, 100),
                size    = (100, 100))
        anim = anims.cycle(v = (0.2, 0.8), duration = 0.1)
        anim.start(self.color)
        anims.Clock.schedule_once(lambda *_: anim.stop(self.color), 3)
        return dot

if __name__ == '__main__':
    app = MyApp()
    app.run()