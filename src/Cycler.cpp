#include "Cycler.h"
#include "Naubino.h"
#include "Naub.h"
#include "Color.h"
#include "NaubManager.h"

Tarjan::Tarjan() {
    s = new QStack<Naub *>();
    sccs = new QList< QList<Naub *> *>();
    index = 1;
}

NaubTarjan::NaubTarjan() {
    index = 0;
    lowlink = 0;
    in_s = false;
}

Cycler::Cycler(Naubino *naubino) :
    QObject(), naubino(naubino) {
    connect(naubino, SIGNAL(mergedNaub(Naub&)), SLOT(mergedNaub(Naub&)));
}

void Cycler::mergedNaub(Naub &naub) {
    Tarjan t;
    foreach (Naub *n, naubino->naubs->naubs()) {
        n->tarjan->index   = 0;
        n->tarjan->lowlink = 0;
        n->tarjan->in_s    = false;
        n->tarjan->visited = false;
    }
    tarjan(naub, 0, t);
    foreach(QList<Naub *> *scc, *t.sccs) {
        sccFound(*scc);
        delete scc;
    }
}

/*
http://en.wikipedia.org/wiki/Tarjan's_strongly_connected_components_algorithm

"u" to prevent moving back in our undirected graph
*/
void Cycler::tarjan(Naub &v, Naub *u, Tarjan &t) {
    v.tarjan->index = t.index;
    v.tarjan->lowlink = t.index;
    t.index++;
    t.s->push(&v);
    v.tarjan->in_s = true;
    v.tarjan->visited = true;
    foreach (Naub *w, v.jointNaubs->keys()) {
        if (w != u) {
            if (w->tarjan->index == 0) {
                tarjan(*w, &v, t);
                v.tarjan->lowlink = qMin(v.tarjan->lowlink, w->tarjan->lowlink);
            } else {
                if (w->tarjan->in_s)
                    v.tarjan->lowlink = qMin(v.tarjan->lowlink, w->tarjan->index);
            }
        }
    }
    if (v.tarjan->lowlink == v.tarjan->index && t.s->count() > 1) {
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
