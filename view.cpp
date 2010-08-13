#include "view.h"
#include "scene.h"
#include <QDebug>

View::View(Scene *scene, QWidget *parent) :
    QGraphicsView(scene, parent)
{
}
