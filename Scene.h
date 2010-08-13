#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>

class Naubino;
class Naub;

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(Naubino *naubino, QObject *parent = 0);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
signals:

public slots:
    void newNaub(Naub *naub);
};

#endif // SCENE_H
