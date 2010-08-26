#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>
#include "Scene.h"
#include "Qb2DebugDraw.h"

class View : public QGraphicsView
{
    Q_OBJECT
public:
    explicit View(Scene &scene);
signals:

public slots:

private:
    Qb2DebugDrawItem *debugDraw_;
};

#endif // VIEW_H
