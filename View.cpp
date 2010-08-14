#include "View.h"
#include "Scene.h"
#include "Qb2DebugDraw.h"
#include "Naubino.h"

#include <QtGui>

#define DEBUG_PHYSICS

View::View(Scene *scene, QWidget *parent) :
    QGraphicsView(scene, parent)
{
#ifdef DEBUG_PHYSICS
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    debugDraw = new Qb2DebugDrawItem(scene->naubino->world);
    debugDraw->setZValue(-100);
    scene->addItem(debugDraw);
#endif
}
