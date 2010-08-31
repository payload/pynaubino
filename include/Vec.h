#ifndef VEC_H
#define VEC_H


#include "Prereqs.h"

#include <QPointF>

#include <Box2D/Box2D.h>


class Vec : public b2Vec2
{
public:
    Vec(float32 x, float32 y);
    Vec(b2Vec2 vec);
    Vec(QPointF vec);
    Vec();
    QPointF q();
    static Vec rand();
};

#endif // VEC_H
