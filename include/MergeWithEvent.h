#ifndef MERGEWITHEVENT_H
#define MERGEWITHEVENT_H

#include "Event.h"

class Naub;

class MergeWithEvent : public Event
{
public:
    Naub *a;
    Naub *b;

    MergeWithEvent(Naubino *naubino);
    bool filter(b2Contact *contact, const b2ContactImpulse *impulse);
    void handle();
protected:
    int shortDistance(Naub *a, Naub *b);
};

#endif // MERGEWITHEVENT_H
