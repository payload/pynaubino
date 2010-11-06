from abc import ABCMeta, abstractmethod, abstractproperty

class Application(metaclass=ABCMeta):
    @abstractmethod
    def exec_(self): pass

class GraphicsScene(metaclass=ABCMeta):
    @abstractproperty
    def pointer(self): pass
    @abstractmethod
    def add_item(self, *item): pass
    @abstractmethod
    def remove_item(self, *item): pass

class GraphicsView(metaclass=ABCMeta):
    @abstractmethod
    def __init__(self, scene : GraphicsScene): pass

    