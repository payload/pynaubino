#ifndef NAUBINOCONTACTLISTENER_H
#define NAUBINOCONTACTLISTENER_H

#include <Box2D.h>
#include "Naub.h"
#include "Naubino.h"
#include "Event.h"
#include "MergeWithEvent.h"

class NaubinoContactListener : public b2ContactListener
{
public:
    NaubinoContactListener(Naubino *naubino);
    Naubino *naubino;

    void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
};

#endif // NAUBINOCONTACTLISTENER_H
