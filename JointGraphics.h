#ifndef JOINTGRAPHICS_H
#define JOINTGRAPHICS_H

#include <QGraphicsLineItem>

class Joint;

class JointGraphics : public QObject, public QGraphicsLineItem {
	Q_OBJECT;
 public:
	JointGraphics(Joint *joint);
	Joint *joint;
 public slots:
	void adjust();
};

#endif
