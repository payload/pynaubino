#include "Cycler.h"
#include "Naub.h"

class NaubTarjan {
public:
    NaubTarjan();
    int index;
    int lowlink;
    bool in_s;
    bool visited;
};

void Cycler::testForCycle(Naub *naub) {
    index = 1;

    tarjan(*naub, NULL);
    foreach(QList<Naub *> *scc, sccs) {
        emit cycleFound(*scc);
        delete scc;
    }

    s.clear();
    sccs.clear();
    naubs.clear();

    foreach (NaubTarjan *tarjan, tarjans.values())
        delete tarjan;

    tarjans.clear();
    index = 0;
}

NaubTarjan::NaubTarjan() {
    index = 0;
    lowlink = 0;
    in_s = false;
    visited = false;
}

/*
http://en.wikipedia.org/wiki/Tarjan's_strongly_connected_components_algorithm

"u" to prevent moving back in our undirected graph
*/
void Cycler::tarjan(Naub &v, Naub *u) {
    naubs.append(&v);
    if (!tarjans.contains(&v))
        tarjans.insert(&v, new NaubTarjan());
    tarjans.value(&v)->index = index;
    tarjans.value(&v)->lowlink = index;
    index++;
    s.push(&v);
    tarjans.value(&v)->in_s = true;
    tarjans.value(&v)->visited = true;
    foreach (Naub *w, v.joinedNaubs()) {
        if (w != u) {
            if (!tarjans.contains(w))
                tarjans.insert(w, new NaubTarjan());
            if (tarjans.value(w)->index == 0) {
                tarjan(*w, &v);
                tarjans.value(&v)->lowlink = qMin(tarjans.value(&v)->lowlink, tarjans.value(w)->lowlink);
            } else {
                if (tarjans.value(w)->in_s)
                    tarjans.value(&v)->lowlink = qMin(tarjans.value(&v)->lowlink, tarjans.value(w)->index);
            }
        }
    }
    if (tarjans.value(&v)->lowlink == tarjans.value(&v)->index && s.count() > 1) {
        QList<Naub *> *scc = new QList<Naub *>();
        Naub *w;
        int c = 0;
        do {
            w = s.pop();
            scc->append(w);
            c++;
        } while(w != &v);
        if (c > 1) sccs.append(scc);
    }
}
