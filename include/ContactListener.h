#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H

#include <Box2D/Dynamics/b2WorldCallbacks.h>
#include <Box2D/Dynamics/Contacts/b2Contact.h>
#include <QObject>

class Naub;

class ContactListener : public QObject, public b2ContactListener {
    Q_OBJECT
private:
    void PostSolve(b2Contact *contact,
                   const b2ContactImpulse *impulse);
signals:
    void naubOnNaub(Naub *a, Naub *b);
};

#endif // CONTACTLISTENER_H
