from os.path import isfile

class Highscore:
    def __init__(self):
        self.filename = filename = "highscore"

    def submit_score(self, name, score, filename=None):
        if not filename: filename = self.filename
        escape = self.__escape
        score = str(score)
        line = escape(score) +","+ escape(name) +"\n"
        
        file = open(filename, "a")
        file.write(line)
        file.close()

    def load_score(self, filename=None):
        if not filename: filename = self.filename
        if not isfile(filename): return []
        
        file = open(filename, "r")
        score = file.readlines()
        file.close()

        score = [x.strip() for x in score]
        score = [x.split(',') for x in score]
        score = [x for x in score if len(x) == 2]
        score = [(int(x[0]), x[1]) for x in score]
        score.sort(key=lambda x: x[0])
        score.reverse()
        return score

    def __escape(self, s):
        s = s.replace('\n', '')
        s = s.replace('\t', '')
        s = s.replace('\\', '\\\\')
        s = s.replace(',', '\\COMMA')
        return s

    def __unescape(self, s):
        s = s.replcae('\n', '')
        s = s.replace('\t', '')
        s = s.replace('\\\\', '\\')
        s = s.replace('\\COMMA' , ',' )
        return s