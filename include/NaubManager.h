#ifndef NAUBMANAGER_H
#define NAUBMANAGER_H


#include "Prereqs.h"

#include "Color.h"
#include "Vec.h"
#include "Naub.h"



class NaubManager {
public:
    NaubManager(b2World &world);
    ~NaubManager();

    Naub& add(Vec pos);
    Naub& add(Vec pos, Color color);
    void remove(Naub &naub);

    int count();
    void update();
private:
    b2World& world();
    QList<Naub *>& naubs();

    QList<Naub *> *naubs_;
    b2World *world_;
};

#endif // NAUBMANAGER_H
