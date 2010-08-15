#include "Cycler.h"
#include "Naubino.h"
#include "Naub.h"

Cycler::Cycler(Naubino *naubino, QObject *parent) :
    QObject(parent), naubino(naubino)
{
    connect(naubino, SIGNAL(mergedNaub(Naub*)), SLOT(mergedNaub(Naub*)));
}

void Cycler::mergedNaub(Naub *naub) {
    Gabow *g = new Gabow();
    g->c = 1;
    foreach (Naub *n, *naubino->naubs) {
        n->temp = 0;
    }
    gabow(naub, NULL, g);
    foreach(QList<Naub *> *scc, g->sccs)
        sccFound(scc);
}

/*
http://en.wikipedia.org/wiki/Gabow's_algorithm

u is the vertex i am coming from and is used to
apply Gabow on undirected graphs.
*/
void Cycler::gabow(Naub *v, Naub *u, Gabow *g) {
    Naub *x;
    v->temp = g->c++;
    g->s.push(v);
    g->p.push(v);
    foreach (Naub *w, v->jointNaubs->keys()) {
        if (w->temp == 0) gabow(w, v, g);
        if (w != u && !g->in_sccs.contains(w))
            while (!g->p.isEmpty() && g->p.top()->temp > w->temp)
                g->p.pop();
    }
    if (!g->p.isEmpty() && g->p.top() == v) {
        QList<Naub *> *scc = new QList<Naub *>();
        do scc->append(x = g->s.pop()); while (x != v);
        // save only non trivial sccs
        if (scc->count() > 1) g->sccs.append(scc);
        foreach (Naub *n, *scc) g->in_sccs.insert(n);
        g->p.pop();
    }
}
