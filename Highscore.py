from io import open
import os.path

class Highscore(object):
    def __init__(self):
        self.filename = filename = u"highscore"

    def submit_score(self, name, score, filename=None):
        if not filename: filename = self.filename
        escape = self.__escape
        score = unicode(score)
        line = escape(score) +u","+ escape(name) +u"\n"
        file = open(filename, u"a")
        file.write(line)
        file.close()

    def load_score(self, filename=None):
        if not filename: filename = self.filename
        if os.path.isfile(filename):
            file = open(filename, u"r")
            score = file.readlines()
            file.close()
        else:
            score = u""
        score = [x.strip() for x in score]
        score = [x.split(u',') for x in score]
        score = [x for x in score if len(x) == 2]
        score = [(int(x[0]), x[1]) for x in score]
        score.sort(key=lambda x: x[0])
        score.reverse()
        return score

    def __escape(self, s):
        s = s.replace(u'\n', u'')
        s = s.replace(u'\t', u'')
        s = s.replace(u'\\', u'\\\\')
        s = s.replace(u',', u'\\COMMA')
        return s

    def __unescape(self, s):
        s = s.replcae(u'\n', u'')
        s = s.replace(u'\t', u'')
        s = s.replace(u'\\\\', u'\\')
        s = s.replace(u'\\COMMA' , u',' )
        return s
