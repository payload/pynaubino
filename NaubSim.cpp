#include "NaubSim.h"

static const float32 FRAMERATE = 1.0f / 30.0f;
static const float32 B2_TIMESTEP = FRAMERATE;
static const int32 B2_VELITERATIONS = 10;
static const int32 B2_POSITERATIONS = 10;

NaubSim::NaubSim(NaubScene *scene) : scene(scene) {
	setup();
	scene->addNaubPair(world);
}

void NaubSim::setup() {
	setupWorld();
	setupCalcTimer();
}

void NaubSim::setupWorld() {
	b2Vec2 gravity(0.0f, 0.0f);
	bool doSleep = true;
	world = new b2World(gravity, doSleep);
}

void NaubSim::setupCalcTimer() {
		calcTimer = new QTimer();
		connect(calcTimer, SIGNAL(timeout()), this, SLOT(calc()));
}

void NaubSim::calc() {
	world->Step(B2_TIMESTEP, B2_VELITERATIONS, B2_POSITERATIONS);
	world->ClearForces();
	foreach (Naub *naub, scene->naubs())
		naub->adjust();
}

void NaubSim::start() {
	calcTimer->start( FRAMERATE * 1000 );
}
