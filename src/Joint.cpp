#include "Joint.h"
#include "Naub.h"

void Joint::join(Naub *a, Naub *b) {
    emit joined(this);
}

void Joint::unjoin() {
    emit unjoined(this);
}

void Joint::update() {
    emit changed(this);
}
