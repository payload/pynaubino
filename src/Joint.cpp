#include "Joint.h"

void Joint::join() {
    emit joined(this);
}

void Joint::unjoin() {
    emit unjoined(this);
}

void Joint::update() {
    emit changed(this);
}
