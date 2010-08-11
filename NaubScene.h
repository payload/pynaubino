#ifndef NAUBSCENE_H
#define NAUBSCENE_H

#include "Naub.h"
#include "NaubContext.h"

#include <QGraphicsScene>
#include <QObject>
#include <QTimer>
#include <QList>
#include <Box2D/Box2D.h>

class NaubScene : public QGraphicsScene {
	Q_OBJECT
 public:
	NaubScene();
	void start();
	void setup();
	Naub *addNaub(qreal x = 0, qreal y = 0);
	void addNaubPair(qreal x = 0, qreal y = 0);
 protected slots:
	void calc();
	void setupCalcTimer();
	void setupWorld();
 private:
	QTimer *calcTimer;
	b2World *world;
	NaubContext *context;
	QList<Naub *> *naubs;
};

#endif
