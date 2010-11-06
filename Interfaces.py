from abc import ABCMeta, abstractmethod, abstractproperty

class Application(metaclass=ABCMeta):
    @abstractmethod
    def exec_(self): pass
    @abstractmethod
    def Timer(self, interval, callback): pass

class GraphicsScene(object, metaclass=ABCMeta):
    naubino = abstractproperty()
    @abstractmethod
    def add_item(self, *item): pass
    @abstractmethod
    def remove_item(self, *item): pass
    @abstractmethod
    def add_naub(self, naub): pass
    @abstractmethod
    def remove_naub(self, naub): pass
    @abstractmethod
    def pre_remove_naub(self, naub): pass
    @abstractmethod
    def add_naub_joint(self, joint): pass
    @abstractmethod
    def remove_naub_joint(self, joint): pass
    @abstractmethod
    def pre_remove_naub_joint(self, joint): pass
    @abstractmethod
    def add_update_object(self, obj): pass
    @abstractmethod
    def remove_update_object(self, obj): pass
    @abstractmethod
    def step(self, dt): pass

class GraphicsView(metaclass=ABCMeta):
    @abstractmethod
    def __init__(self, scene : GraphicsScene): pass

class Timer(metaclass=ABCMeta):
    @abstractmethod
    def __init__(self, interval, callback): pass
    @abstractmethod
    def start(self): pass
    @abstractmethod
    def stop(self): pass