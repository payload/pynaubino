#include "View.h"
#include "Scene.h"

#include <QtGui>

View::View(Scene *scene, QWidget *parent) :
    QGraphicsView(scene, parent)
{
}
