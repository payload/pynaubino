#include "NaubSim.h"

NaubSim::NaubSim(NaubScene *scene) : scene(scene) {
	setup();
}

void NaubSim::setup() {
	setupWorld();
	setupCalcTimer();
}

void NaubSim::setupWorld() {
	world = new b2World(/* gravity = */ b2Vec2(0, 0),
											/* doSleep = */ true);
}

void NaubSim::setupCalcTimer() {
		calcTimer = new QTimer();
		connect(calcTimer, SIGNAL(timeout()), this, SLOT(calc()));
}

void NaubSim::calc() {
	
	foreach (Naub *naub, scene->naubs())
		naub->adjust();
}

void NaubSim::start() {
	calcTimer->start( 1000 / 30 );
}
