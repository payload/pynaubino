#include "NaubPairSpammer.h"

#include <qmath.h>
#include "Naubino.h"

NaubPairSpammer::NaubPairSpammer(Naubino *naubino) : QTimer(),
        _naubino(naubino) {
}

NaubPairSpammer::~NaubPairSpammer() {
    _naubino = 0;
}

void NaubPairSpammer::timerEvent(QTimerEvent *e) {

    qreal w = 5, h = 2.5;
    qreal rx = w, ry = h, x = qrand() * 2.0f / RAND_MAX * M_PI;
    Vec pos( rx*qCos(x), ry*qSin(x) );
    Vec jadd(0.3, 0);

    Naubino &naubino = *_naubino;
    Naub &a = naubino.addNaub(pos - jadd);
    Naub &b = naubino.addNaub(pos + jadd);
    naubino.joinNaubs(a, b);
    naubino.joinWithCenter(a);
    naubino.joinWithCenter(b);

    QTimer::timerEvent(e);
}
