#ifndef NAUBMANAGER_H
#define NAUBMANAGER_H


#include "Prereqs.h"

#include <QSet>

#include "Color.h"
#include "Vec.h"
#include "Naub.h"


class NaubManager {
public:
    NaubManager(b2World *world);
    ~NaubManager();

    Naub* add(const Vec& pos);
    Naub* add(const Vec& pos, const Color& color);
    void remove(Naub *naub);

    int count() const;
    void update();

private:
    b2World *_world;
    QSet<Naub *> _naubs;
};


#endif // NAUBMANAGER_H

