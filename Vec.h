#ifndef VEC_H
#define VEC_H

#include <QVector2D>
#include <Box2D/Box2D.h>

class Vec : public QVector2D {
 public:
	Vec(qreal x = 0, qreal y = 0);
	b2Vec2 toB2Vec2();
  static Vec fromB2Vec2(b2Vec2 vec);
};

#endif
