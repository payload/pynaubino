#ifndef CYCLER_H
#define CYCLER_H

#include <QtCore>

class Naubino;
class Naub;
class Tarjan;

class Cycler : public QObject
{
    Q_OBJECT
public:
    explicit Cycler(Naubino *naubino);
    Naubino *naubino;
signals:
    void sccFound(QList<Naub *> &scc);
public slots:
    void mergedNaub(Naub &naub);
protected:
    void tarjan(Naub &v, Naub *u, Tarjan &t);
};


class Tarjan {
private:
    Tarjan();
    QStack<Naub *> *s;
    QList<QList<Naub *> *> *sccs;
    int index;
    friend class Cycler;
};

class NaubTarjan {
private:
    NaubTarjan();
    int index;
    int lowlink;
    bool in_s;
    bool visited;
    friend class Cycler;
    friend class Naub;
};

#endif // CYCLER_H
