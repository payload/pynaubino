#include "View.h"
#include "Scene.h"
#include "Qb2DebugDraw.h"
#include "Naubino.h"

#include <QtGui>

//#define DEBUG_PHYSICS

View::View(Scene *scene, QWidget *parent) :
    QGraphicsView(scene, parent)
{
    setRenderHint(QPainter::Antialiasing);
    setSceneRect(-300, -200, 600, 400);

    QGraphicsItem *border = scene->addRect(-300, -200, 600, 400);
    border->setZValue(-90);

#ifdef DEBUG_PHYSICS
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    debugDraw = new Qb2DebugDrawItem(scene->naubino->world);
    debugDraw->setZValue(-100);
    scene->addItem(debugDraw);
#endif
}
