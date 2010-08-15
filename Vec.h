#ifndef VEC_H
#define VEC_H

#include <Box2D.h>
#include <QtCore>
#include <QPointF>

class Vec : public b2Vec2
{
public:
    Vec(float32 x, float32 y) : b2Vec2(x, y) {}
    Vec(b2Vec2 vec) : b2Vec2(vec.x, vec.y) {}
    Vec(QPointF vec) : b2Vec2(vec.x(), vec.y()) {}
    Vec() : b2Vec2() {}
    QPointF q() { return QPointF(x, y); }
    static Vec rand() {
        qreal x = qrand()*2.0f*M_PI/RAND_MAX;
        return Vec(qCos(x), qSin(x));
    }
};

#endif // VEC_H
