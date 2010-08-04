#ifndef NAUBSCENE_H
#define NAUBSCENE_H

#include "Naub.h"

#include <Box2D/Box2D.h>
#include <QGraphicsScene>

class NaubScene : public QGraphicsScene {
 public:
	NaubScene();
	QList<Naub *> naubs();
	void addNaubPair(b2World *world);
 protected:
 private:
};

#endif
