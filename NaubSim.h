#ifndef NAUBSIM_H
#define NAUBSIM_H

#include "NaubScene.h"

#include <QObject>
#include <QTimer>
#include <Box2D/Box2D.h>

class NaubSim : public QObject {
	Q_OBJECT
 public:
	NaubSim(NaubScene *scene);
	void start();
	void setup();
 protected slots:
	void calc();
	void setupCalcTimer();
	void setupWorld();
 private:
	NaubScene *scene;
	QTimer *calcTimer;
	b2World *world;
};

#endif
