#include "View.h"

#include <QGraphicsItem>

#include "Naubino.h"
#include "Qb2DebugDraw.h"
#include "Scene.h"


//#define DEBUG_PHYSICS


View::View(Scene *scene) : QGraphicsView(scene) {
    setRenderHint(QPainter::Antialiasing);
    setSceneRect(-300, -200, 600, 400);

    QGraphicsItem *border = scene->addRect(-300, -200, 600, 400);
    border->setZValue(-90);

#ifdef DEBUG_PHYSICS
    setRenderHint(QPainter::Antialiasing, false);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    _debugDraw = new Qb2DebugDrawItem(&scene->naubino().world());
    _debugDraw->setZValue(-100);
    scene->addItem(_debugDraw);
#endif
}

