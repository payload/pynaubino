#ifndef VEC_H
#define VEC_H

#include <Box2D.h>

class Vec : public b2Vec2
{
public:
    Vec();
    Vec(float32 x, float32 y);
    Vec(b2Vec2 vec);
};

#endif // VEC_H
