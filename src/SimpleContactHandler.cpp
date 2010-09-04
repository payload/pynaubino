#include "SimpleContactHandler.h"

#include <Naub.h>

SimpleContactHandler::~SimpleContactHandler() {
    QMutableListIterator<NaubOnNaubEvent *> i(_events);
    while(i.hasNext()) {
        i.next();
        delete i.value();
        i.remove();
    }
}

void SimpleContactHandler::naubOnNaub(Naub *a, Naub *b) {
    NaubOnNaubEvent *event = new NaubOnNaubEvent();
    event->a = a;
    event->b = b;
    _events.append(event);
}

void SimpleContactHandler::handle() {
    QMutableListIterator<NaubOnNaubEvent *> i(_events);
    while (i.hasNext()) {
        i.next();
        NaubOnNaubEvent *event = i.value();
        Naub *a = event->a;
        Naub *b = event->b;
        delete event;
        i.remove();

        if (!a->deleted() && !b->deleted())
            a->handleContact(b);
        if (!a->deleted() && !b->deleted())
            b->handleContact(a);
    }
}
