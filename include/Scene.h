#ifndef SCENE_H
#define SCENE_H

#include <QtGui>

class Naubino;
class Naub;
class NaubJoint;
class Pointer;

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(Naubino *naubino, QObject *parent = 0);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    Naubino *naubino;
    Pointer* getMainPointer();

    QGraphicsTextItem *dtext;
signals:

public slots:
    void newNaub(Naub *naub);
    void newJoint(NaubJoint *joint);
};

#endif // SCENE_H
