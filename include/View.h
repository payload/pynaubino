#ifndef VIEW_H
#define VIEW_H


#include "Prereqs.h"

#include <QGraphicsView>


class Qb2DebugDrawItem;
class Scene;


class View : public QGraphicsView {
    Q_OBJECT
public:
    View(Scene *scene);

private:
    Qb2DebugDrawItem *_debugDraw;
};


#endif // VIEW_H

