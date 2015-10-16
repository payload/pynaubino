import parsley, itertools, math
from utils import *
from Naub       import Naub
from NaubJoint  import NaubJoint



grammar = '''
name        = letter:c (letterOrDigit*):cs      -> "".join([c] + cs)
ref         = ref_pos | ref_name | ref_desc
ref_pos     = '{}'                              -> interpreter.ref_pos()
ref_name    = '{' name:n '}'                    -> interpreter.ref_name(n)
ref_desc    = name:n                            -> interpreter.ref_desc(n)
chain       = ref:r ('-' ref)*:rs               -> RefChain([r] + rs)
spec        = chain:c (ws chain)*:cs            -> RefGraph([c] + cs)
'''

class Interpreter(object):

    def __init__(self, args, kwargs):
        self.args       = args
        self.kwargs     = kwargs
        self.ref_pos_i  = 0
        self.refs       = {}

    def ref_pos(self):
        ref             = Ref(
            val         = self.args[self.ref_pos_i])
        self.ref_pos_i += 1
        return ref

    def ref_name(self, name):
        try:    return self.refs[name]
        except:
            ref             = Ref(
                name        = name,
                val         = self.kwargs[name])
            self.refs[name] = ref
            return ref

    def ref_desc(self, desc):
        return Ref(desc = desc)



class Ref(object):

    def __init__(self, name = None, desc = None, val = None):
        self.name   = name
        self.desc   = desc
        self.val    = val

class RefJoin(object):

    def __init__(self, a, b, val = None):
        assert a != b
        self.a      = a
        self.b      = b
        self.val    = val

class RefChain(object):

    def __init__(self, refs):
        self.refs  = refs
        self.joins = self.__join()

    @gather()
    def __join(self):
        refs = self.refs
        for a, b in zip(refs, refs[1:]):
            yield RefJoin(a, b)

class RefGraph(object):

    def __init__(self, chains):
        self.chains     = chains
        refs        = self.refs
        refs        = sorted(refs,      key = lambda ref: ref.desc)
        groups      = itertools.groupby(refs, lambda ref: ref.desc)
        groups      = {group: list(refs) for group, refs in groups}
        self.groups = groups

    @property
    def joins(self):
        joins   = (chain.joins for chain in self.chains)
        return itertools.chain(*joins)

    @property
    def refs(self):
        refs    = (chain.refs for chain in self.chains)
        return itertools.chain(*refs)

    def by_name(self, name):
        return filter(self.refs, lambda ref: ref.name == name)[0]



class NaubSpecBase(object):

    def __init__(self, _ref):
        self._ref  = _ref
        self.fill_with_default_naubs()
        self.fill_with_default_naub_joins()

    @property
    def naubs(self):
        return (ref.val for ref in self._ref.refs)

    @property
    def joins(self):
        return (join.val for join in self._ref.joins)

    @property
    def groups(self):
        return {group: [ref.val for ref in refs] for group, refs in self._ref.groups.items()}

    def fill_with_default_naubs(self):
        refs = (ref for ref in self._ref.refs if ref.val is None)
        for ref in refs:
            ref.val = Naub()

    def fill_with_default_naub_joins(self):
        joins = (join for join in self._ref.joins if join.val is None)
        for join in joins:
            join.val = NaubJoint(join.a.val, join.b.val)
            join.a.val.join_naub(join.b.val, join.val)

    def colorize(self, palette):
        groups      = self.groups
        colors      = itertools.cycle(palette)
        for color, naubs in zip(colors, groups.values()):
            for naub in naubs:
                naub.color = color

    def position_on_circle(self, radius):
        naubs           = list(self.naubs)
        circle          = math.pi * 2 / len(naubs)
        for i, naub in enumerate(naubs):
            x           = i * circle
            naub.pos    = radius * math.cos(x), radius * math.sin(x)

class NaubSpecChain(NaubSpecBase):

    def __repr__(self):
        cls         = type(self)
        return "<{name} {list}>".format(
            #module  = cls.__module__,
            name    = cls.__name__,
            list    = list(self.naubs))

class NaubSpecGraph(NaubSpecBase):

    @property
    def chains(self):
        return (NaubSpecChain(chain) for chain in self._ref.chains)



def parse_spec(spec, *args, **kwargs):
    interpreter     = Interpreter(args, kwargs)
    bindings        = dict(
        interpreter = interpreter,
        RefChain    = RefChain,
        RefGraph    = RefGraph)
    parser          = parsley.makeGrammar(grammar, bindings)
    return parser(spec).spec()

def spec(spec, *args, **kwargs):
    ref_graph       = parse_spec(spec, *args, **kwargs)
    return NaubSpecGraph(ref_graph)
