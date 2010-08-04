#include "NaubScene.h"
#include "Naub.h"

#include <QPen>
#include <Qt>
#include <QGraphicsItem>
#include <QList>
#include <QTimer>
#include <QVector2D>
#include <Box2D/Box2D.h>

NaubScene::NaubScene() {
	addText("NaubScene");
}

QList<Naub *> NaubScene::naubs() {
	QList<Naub *> naubs;
	foreach (QGraphicsItem *item, items())
		if (Naub *naub = qgraphicsitem_cast<Naub *>(item))
			naubs << naub;
	return naubs;
}

void NaubScene::addNaubPair(b2World *world) {
	Naub *naub0 = new Naub(world,  100);
	Naub *naub1 = new Naub(world, -100);
	addItem(naub0);
	addItem(naub1);
}
