from kivy.app import App
from kivy.uix.widget import Widget
from kivy.properties import NumericProperty, ReferenceListProperty
from kivy.vector import Vector
from kivy.clock import Clock
from kivy.graphics import *
from kivy.metrics import mm
from utils import *
import anims

from kivy.config import Config
#Config.set('graphics', 'fullscreen', 'auto')

from kivy.lang import Builder
from kivy.uix.screenmanager import Screen, ScreenManager

class MenuScreen(Screen):

    def __init__(self, **kwargs):
        super(MenuScreen, self).__init__(**kwargs)

import naubino_base, naubino_mode, naubivy

class ArenaModeScreen(Screen):

    def on_enter(self):
        naubino     = naubino_base.Naubino()
        mode        = naubino_mode.Arena(naubino)
        game        = naubivy.Game(naubino)
        game_mode   = naubivy.Arena(naubino, mode, game)
        Clock.schedule_interval(game.update, 1.0/60.0)
        self.add_widget(game)
        game.start()

class FlybyModeScreen(Screen):

    def on_enter(self):
        naubino     = naubino_base.Naubino()
        mode        = naubino_mode.Flyby(naubino)
        game        = naubivy.Game(naubino)
        game_mode   = naubivy.Flyby(naubino, mode, game)
        Clock.schedule_interval(game.update, 1.0/60.0)
        self.add_widget(game)
        game.start()


Builder.load_string("""
<MenuScreen>:
    name:           "menu"
    AnchorLayout:
        anchor_x:       "center"
        anchor_y:       "center"
        BoxLayout:
            orientation:    "vertical"
            size_hint:  (0.1, 0.5)
            Label:
                text:       "Naubino"
                color:      (0, 0, 0, 1)
            Button:
                text:       "Arena Mode"
                on_press:   root.manager.current = "arena"
            Button:
                text:       "Flyby Mode"
                on_press:   root.manager.current = "flyby"
            Button:
                text:       "Quit"
                on_press:   root.quit()
""")



class NaubinoApp(App):
    def build(self):

        from kivy.core.window import Window
        Window.clearcolor   = (1, 1, 1, 1)

        menu_screen         = MenuScreen()
        arena_screen        = ArenaModeScreen(name = "arena")
        flyby_screen        = FlybyModeScreen(name = "flyby")

        sm                  = ScreenManager()
        sm.add_widget(menu_screen)
        sm.add_widget(arena_screen)
        sm.add_widget(flyby_screen)

        return sm




def main():
    app = NaubinoApp()
    app.run()

if __name__ == '__main__':
    main()
