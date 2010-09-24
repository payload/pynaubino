#include "ContactListener.h"

#include "Naub.h"

void ContactListener::PostSolve(b2Contact *contact,
                                const b2ContactImpulse *impulse) {
    Naub *a = static_cast<Naub *>(contact->GetFixtureA()->GetUserData());
    Naub *b = static_cast<Naub *>(contact->GetFixtureB()->GetUserData());
    emit naubOnNaub(a, b);
}
