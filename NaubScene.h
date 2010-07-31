#ifndef NAUBSCENE_H
#define NAUBSCENE_H

#include "Naub.h"

#include <QGraphicsScene>

class NaubScene : public QGraphicsScene {
 public:
	NaubScene();
	QList<Naub *> naubs();
 protected:
 private:
};

#endif
