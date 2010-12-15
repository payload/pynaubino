from os.path import isfile

class Highscore:
    def __init__(self):
        self.filename = filename = u"highscore"

    def submit_score(self, name, score, filename=None):
        if not filename: filename = self.filename
        escape = self.__escape
        score = str(score)
        line = escape(score) +"\t"+ escape(name) +"\n"
        
        file = open(filename, "a")
        file.write(line)
        file.close()

    def load_score(self, filename=None):
        if not filename: filename = self.filename
        if not isfile(filename): return []
        parse_line = self.__parse_line
        
        file = open(filename, "r")
        score = file.readlines()
        file.close()

        score = [x.strip() for x in score]
        score = [x.split("\t") for x in score]
        score = [x for x in score if len(x) == 2]
        score = [parse_line(x) for x in score]
        score = [x for x in score if x != None]
        score.sort(key=lambda x: x[0])
        score.reverse()
        return score

    def __parse_line(self, x):
        try: return (int(x[0]), x[1])
        except ValueError as e: return None

    def __escape(self, s):
        s = s.replace("\n", " ")
        s = s.replace("\t", " ")
        return s
