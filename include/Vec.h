#ifndef VEC_H
#define VEC_H


#include "Prereqs.h"

#include <QPointF>

#include <Box2D/Box2D.h>


class Vec : public b2Vec2
{
public:
    Vec();
    Vec(float32 x, float32 y);
    Vec(const b2Vec2& vec);
    Vec(const QPointF& vec);
    QPointF q() const;
    static Vec rand();
};


#endif // VEC_H

