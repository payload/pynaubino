#include "Vec.h"

Vec::Vec(qreal x, qreal y) : QVector2D(x, y) {
}

b2Vec2 Vec::toB2Vec2() {
	return b2Vec2(x(), y());
}

/*static*/ Vec Vec::fromB2Vec2(b2Vec2 vec) {
	return Vec(vec.x, vec.y);
}
