#ifndef VEC_H
#define VEC_H

#include <Box2D.h>
#include <QPointF>

class Vec : public b2Vec2
{
public:
    Vec();
    Vec(float32 x, float32 y);
    Vec(b2Vec2 vec);
    Vec(QPointF vec);
};

#endif // VEC_H
