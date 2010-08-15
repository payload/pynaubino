#ifndef SCORER_H
#define SCORER_H

#include <QtCore>

class Naubino;
class Naub;

class Scorer : public QObject
{
    Q_OBJECT
public:
    explicit Scorer(Naubino *naubino, QObject *parent = 0);
    Naubino *naubino;
signals:

public slots:
    void sccFound(QList<Naub *> *scc);
};

#endif // SCORER_H
