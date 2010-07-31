#include "NaubSim.h"

static const float32 FRAMERATE = 1 / 30.0f;
static const float32 B2_TIMESTEP = FRAMERATE;
static const int32 B2_VELITERATIONS = 10;
static const int32 B2_POSITERATIONS = 10;

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
	world->Step(B2_TIMESTEP, B2_VELITERATIONS, B2_POSITERATIONS);
	foreach (Naub *naub, scene->naubs()) {
		if (!naub->isSetup) naub->setup(world);
		naub->adjust();
	}
}

void NaubSim::start() {
	calcTimer->start( FRAMERATE * 1000 );
}
