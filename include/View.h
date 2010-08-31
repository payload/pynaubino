#ifndef VIEW_H
#define VIEW_H


#include "Prereqs.h"

#include <QGraphicsView>

#include "Scene.h"

class Qb2DebugDrawItem;


class View : public QGraphicsView
{
    Q_OBJECT
public:
    View(Scene &scene);
signals:

public slots:

private:
    Qb2DebugDrawItem *debugDraw_;
};

#endif // VIEW_H
