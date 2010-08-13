#include "Vec.h"

Vec::Vec(float32 x, float32 y) : b2Vec2(x, y) {}
Vec::Vec(b2Vec2 vec) : b2Vec2(vec.x, vec.y) {}
Vec::Vec() : b2Vec2() {}
