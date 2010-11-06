from Interfaces import *

try:
    import pygame2.sdl.constants as constants
    import pygame2.sdl.image as image
    import pygame2.sdl.event as event
    import pygame2.sdl.video as video
except ImportError:
    raise ImportError("No pygame2.sdl support")

class Application(Application):
    def __init__(self):
        super(Application, self).__init__()

    def exec_(self):
        okay = True
        while okay:
            for ev in event.get():
                if ev.type == constants.QUIT:
                    okay = False
                if ev.type == constants.KEYDOWN and ev.key == constants.K_ESCAPE:
                    okay = False
        video.quit()
 
class GraphicsScene(GraphicsScene):
    def pointer(self): pass
    def add_item(self, *item): pass
    def remove_item(self, *item): pass

class GraphicsView(GraphicsView):
    def __init__(self, scene : GraphicsScene):
        video.init()

        import pygame2.examples
        imgresource = pygame2.examples.RESOURCES.get("logo.bmp")
        surface = image.load_bmp(imgresource)

        screen = video.set_mode(surface.width + 10, surface.height + 10)

        screen.fill(pygame2.Color (255, 255, 255))
        screen.blit(surface, (5, 5))
        screen.flip()
