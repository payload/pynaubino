import libavg as avg



def screenshot(node):
    if isinstance(node, avg.ImageNode):
        return avg.Bitmap(node.getBitmap())
    with SaveParent(node):
        return drawOffscreen(node.size, lambda parent:
            parent.appendChild(node))



def screenshotImageNode(node):
    img = avg.ImageNode()
    img.setBitmap(screenshot(node))
    return img



def drawOffscreen(size, what, unlink=True):
    canvas = avg.player.createCanvas(
        # XXX buggy on some platforms https://www.libavg.de/site/issues/467
        #mipmap = True,
        multisamplesamples = 8,
        autorender  = False,
        size        = size)
    root = canvas.getRootNode()
    what(root)
    canvas.render()
    bitmap = canvas.screenshot()
    while unlink and root.getNumChildren():
        root.removeChild(0)
    avg.player.deleteCanvas(canvas.getID())
    return bitmap



class SaveParent(object):

    def __init__(self, *nodes):
        self.nodes = list(nodes)

    def __enter__(self):
        self.nodes = list(self.__save())
        for node, _, _ in self.nodes:
            node.unlink()

    def __save(self):
        for node in self.nodes:
            parent = node.parent
            if parent:
                index = parent.indexOf(node)
                yield (node, parent, index)
            else:
                yield (node, None, None)

    def __exit__(self, ex_type, ex_value, traceback):
        for node, parent, index in sorted(self.nodes, key = lambda x: x[2]):
            if node.parent:
                node.unlink()
            if parent:
                parent.insertChild(node, index)
