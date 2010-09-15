#include "Joint.h"

Joint::~Joint() {
    _isJoined = false;
}

void Joint::join() {
    _isJoined = true;
    emit joined(this);
}

void Joint::unjoin() {
    _isJoined = false;
    emit unjoined(this);
}

void Joint::update() {
    emit changed(this);
}
