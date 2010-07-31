#ifndef NAUBSCENE_H
#define NAUBSCENE_H

#include "Naub.h"

#include <QGraphicsScene>
#include <QTimerEvent>
#include <QList>

class NaubScene : public QGraphicsScene {
 public:
	NaubScene();
 protected:
	void timerEvent(QTimerEvent *event);
 private:
	QList<Naub *> naubs();
};

#endif
