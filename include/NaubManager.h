#ifndef NAUBMANAGER_H
#define NAUBMANAGER_H


#include "Prereqs.h"

#include <QSet>

#include "Color.h"
#include "Vec.h"
#include "Naub.h"

class Naubino;

class NaubManager {
public:
    NaubManager(Naubino *naubino);
    ~NaubManager();

    Naub* add(const Vec& pos);
    Naub* add(const Vec& pos, const QColor& color);
    void remove(Naub *naub);

    int count() const;
    void update();

private:
    Naubino *_naubino;
    b2World *_world;
    QSet<Naub *> _naubs;
};


#endif // NAUBMANAGER_H

