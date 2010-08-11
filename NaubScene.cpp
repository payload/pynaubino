#include <QtDebug>
#include "NaubScene.h"

static const float32 FRAMERATE = 1.0f / 30.0f;
static const float32 B2_TIMESTEP = FRAMERATE;
static const int32 B2_VELITERATIONS = 10;
static const int32 B2_POSITERATIONS = 10;

#include "NaubGraphics.h"

NaubScene::NaubScene() {
	setup();
	addEllipse(0, 0, 4, 4);
	for (qreal x = 0; x < 3.14159*2; x += 3.14159*2/3) {
		addNaubPair(cos(x) * 150, sin(x) * 150);
	}
}

Naub *NaubScene::addNaub(qreal x, qreal y) {
	Naub *naub = new Naub(context, Vec(x, y));
	*naubs << naub;
	return naub;
}

void NaubScene::addNaubPair(qreal x, qreal y) {
	qreal pair_size = 40;
	qreal ps = pair_size * 0.5;
	Naub *n0 = addNaub(x - ps, y);
	Naub *n1 = addNaub(x + ps, y);
	n0->join(n1);
}

void NaubScene::setup() {
	naubs = new QList<Naub *>();
	setupWorld();
	context = new NaubContext(world);
	addItem(context->root);
	setupCalcTimer();
}

void NaubScene::setupWorld() {
	b2Vec2 gravity(0.0f, 0.0f);
	bool doSleep = true;
	world = new b2World(gravity, doSleep);
}

void NaubScene::setupCalcTimer() {
		calcTimer = new QTimer();
		connect(calcTimer, SIGNAL(timeout()), this, SLOT(calc()));
}

void NaubScene::calc() {
	world->Step(B2_TIMESTEP, B2_VELITERATIONS, B2_POSITERATIONS);
	foreach (Naub *naub, *naubs) {
		naub->adjust();
	}
	world->ClearForces();
}

void NaubScene::start() {
	calcTimer->start( FRAMERATE * 1000 );
}
