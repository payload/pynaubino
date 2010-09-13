#include "Vec.h"

#include <qmath.h>


Vec::Vec() : b2Vec2(0.0, 0.0) { }
Vec::Vec(float x, float y) : b2Vec2(x, y) { }
Vec::Vec(const b2Vec2& vec) : b2Vec2(vec.x, vec.y) { }
Vec::Vec(const QPointF& vec) : b2Vec2(vec.x()/100.0, vec.y()/100.0) { }
QPointF Vec::q() const { return QPointF(x*100.0, y*100.0); }

qreal Vec::Angle() {
    return qAtan2(x, y);
}

Vec Vec::rotate(qreal angle) {
    qreal l = Length();
    qreal a = Angle() + angle;
    return Vec( qCos(a)*l, qSin(a)*l );
}

Vec Vec::rand() {
    qreal x = qrand()*2.0f*M_PI/RAND_MAX;
    return Vec(qCos(x), qSin(x));
}

