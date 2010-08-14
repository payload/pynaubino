#include "Pointer.h"
#include "Naubino.h"

Pointer::Pointer(Naubino *naubino) : naubino(naubino) {

}

void Pointer::setPos(Vec pos) {
    body->SetTransform(pos, 0);
}
