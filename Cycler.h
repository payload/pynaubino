#ifndef CYCLER_H
#define CYCLER_H

#include <QtCore>

class Naubino;
class Naub;

class Cycle : public QList<Naub *> {};

struct Gabow {
    QStack<Naub *> s;
    QStack<Naub *> p;
    QList< QList<Naub *>* > sccs;
    QSet<Naub *> in_sccs;
    int c;
};

class Cycler : public QObject
{
    Q_OBJECT
public:
    explicit Cycler(Naubino *naubino);
    Naubino *naubino;
signals:
    void sccFound(QList<Naub *> &scc);
public slots:
    void mergedNaub(Naub *naub);
protected:
    void gabow(Naub *v, Naub *u, Gabow *g);
};

#endif // CYCLER_H
