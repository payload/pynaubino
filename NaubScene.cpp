#include "NaubScene.h"
#include "Naub.h"

#include <QPen>
#include <Qt>
#include <QGraphicsItem>
#include <QList>
#include <QTimerEvent>
#include <QTimer>

NaubScene::NaubScene() {
	QTimer *advanceTimer = new QTimer();
	connect(advanceTimer, SIGNAL(timeout()), this, SLOT(advance()));
	advanceTimer->start( 1000 / 25 );

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

void NaubScene::timerEvent(QTimerEvent *event) {
	Q_UNUSED(event);

	/*
	foreach (Naub *naub, naubs)
		{
		naub->moveBy( qreal(1), qreal(1) );
	}
	*/
}
