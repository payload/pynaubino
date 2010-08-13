#include "View.h"
#include "Scene.h"

View::View(Scene *scene, QWidget *parent) :
    QGraphicsView(scene, parent)
{
}
