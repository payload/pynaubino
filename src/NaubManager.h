#ifndef NAUBMANAGER_H
#define NAUBMANAGER_H

#include <QtCore>
#include "Vec.h"
#include "Naub.h"

class NaubManager : public QObject
{
    Q_OBJECT
public:
    explicit NaubManager(Naubino *naubino);
    ~NaubManager();

    const QList<Naub *>& naubs();
    Naub* add(Vec pos);
    Naub* add(Vec pos, QColor color);
    void remove(Naub *naub);
    int count();
signals:
    void newNaub(Naub *naub);
public slots:

private:
    Naubino *naubino;
    QList<Naub *> *naubs_;
};

#endif // NAUBMANAGER_H
