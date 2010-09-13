#ifndef CYCLER_H
#define CYCLER_H

#include <QObject>
#include <QList>
#include <QStack>

class Naub;
class Tarjan;

class Cycler : public QObject {
    Q_OBJECT
public slots:
    void testForCycle(Naub *naub);
signals:
    void cycleFound(QList<Naub*> *cycle);
private:
    void tarjan(Naub &v, Naub *u, Tarjan &t);
};

class Tarjan {
private:
    Tarjan();
    ~Tarjan();
    QStack<Naub *> *s;
    QList<QList<Naub *> *> *sccs;
    QList<Naub *> *naubs;
    int index;
    friend class Cycler;
};

class NaubTarjan {
public:
    NaubTarjan();
private:
    int index;
    int lowlink;
    bool in_s;
    bool visited;
    friend class Cycler;
};

#endif // CYCLER_H
