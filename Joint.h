#ifndef JOINT_H
#define JOINT_H

#include <QGraphicsItem>

class Naub;

class Joint : public QObject {
	Q_OBJECT;
 public:
	Joint(Naub *a, Naub * b);
	Naub *a;
	Naub *b;
	QGraphicsItem *graphics;
  void adjust();
 signals:
	void isAdjusted();
};

#endif
