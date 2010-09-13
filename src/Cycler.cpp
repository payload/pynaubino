#include "Cycler.h"
#include "Naub.h"

#include <QDebug>

void Cycler::testForCycle(Naub *naub) {
    Tarjan t;
    tarjan(*naub, NULL, t);
    qDebug() << "sccs" << t.sccs->count();
    foreach(QList<Naub *> *scc, *t.sccs) {
        emit cycleFound(scc);
        delete scc; scc = 0;
    }
}

Tarjan::Tarjan() {
    s = new QStack<Naub *>();
    sccs = new QList< QList<Naub *> *>();
    index = 1;
}

Tarjan::~Tarjan() {
    delete s; s = 0;
    delete sccs; sccs = 0;
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
void Cycler::tarjan(Naub &v, Naub *u, Tarjan &t) {
    v.tarjan.index = t.index;
    v.tarjan.lowlink = t.index;
    t.index++;
    t.s->push(&v);
    v.tarjan.in_s = true;
    v.tarjan.visited = true;
    foreach (Naub *w, v.jointNaubs().keys()) {
        qDebug() << "index" << w->tarjan.index;
        if (w != u) {
            if (w->tarjan.index == 0) {
                tarjan(*w, &v, t);
                v.tarjan.lowlink = qMin(v.tarjan.lowlink, w->tarjan.lowlink);
            } else {
                if (w->tarjan.in_s)
                    v.tarjan.lowlink = qMin(v.tarjan.lowlink, w->tarjan.index);
            }
        }
    }
    if (v.tarjan.lowlink == v.tarjan.index && t.s->count() > 1) {
        QList<Naub *> *scc = new QList<Naub *>();
        Naub *w;
        int c = 0;
        do {
            w = t.s->pop();
            scc->append(w);
            c++;
        } while(w != &v);
        if (c > 1) t.sccs->append(scc);
    }
}
