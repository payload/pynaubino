#ifndef CYCLER_H
#define CYCLER_H

#include <QObject>
#include <QList>
#include <QMap>
#include <QStack>

class Naub;
class Tarjan;
class NaubTarjan;

class Cycler : public QObject {
    Q_OBJECT
public slots:
    void testForCycle(Naub *naub);
signals:
    void cycleFound(QList<Naub*> &cycle);
private:
    void tarjan(Naub &v, Naub *u);

    QStack<Naub *> s;
    QList<QList<Naub *> *> sccs;
    QList<Naub *> naubs;
    QMap<Naub*,NaubTarjan*> tarjans;

    int index;
};

#endif // CYCLER_H
