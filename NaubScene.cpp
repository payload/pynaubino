#include "NaubScene.h"
#include "Naub.h"

#include <QPen>
#include <Qt>
#include <QGraphicsItem>
#include <QList>
#include <QTimer>

NaubScene::NaubScene() {
	addText("NaubScene");
	addItem(new Naub());
}

QList<Naub *> NaubScene::naubs() {
	QList<Naub *> naubs;
	foreach (QGraphicsItem *item, items())
		if (Naub *naub = qgraphicsitem_cast<Naub *>(item))
			naubs << naub;
	return naubs;
}

