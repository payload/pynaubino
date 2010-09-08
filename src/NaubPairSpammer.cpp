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

    Naub *a = _naubino->addNaub(pos - jadd);
    Naub *b = _naubino->addNaub(pos + jadd);
    _naubino->joinNaubs(a, b);
    _naubino->joinWithCenter(a);
    _naubino->joinWithCenter(b);

    QTimer::timerEvent(e);
}
