#include "Spammer.h"
#include "Naubino.h"
#include "Vec.h"

Spammer::Spammer(Naubino *naubino) :
    QTimer(), naubino(naubino)
{
    setInterval(3000);
}

Spammer::~Spammer() {
    naubino = 0;
}

void Spammer::timerEvent(QTimerEvent *e) {
    qreal w = 5, h = 2.5;
    qreal rx = w, ry = h, x = qrand() * 2.0f / RAND_MAX * M_PI;
    naubino->randomPair(Vec( rx*qCos(x), ry*qSin(x) ));
    QTimer::timerEvent(e);
}
