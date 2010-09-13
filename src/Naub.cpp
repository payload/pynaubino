#include "Naub.h"

void Naub::select() {
    emit selected();
}

void Naub::deselect() {
    emit deselected();
}

void Naub::contact(Naub *naub) {
    /*
    emit remove(naub);
    emit join(this, naub);
    emit merge(this, naub);
    */
}

void Naub::update() {
    emit changed(this);
}
