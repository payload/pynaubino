#ifndef QSCENE_H
#define QSCENE_H

#include <QGraphicsScene>
class QNaub;
class QJoint;
class Pointer;
class b2World;

class QScene : public QGraphicsScene {
    Q_OBJECT
public slots:
    void add(QNaub *qnaub);
    void add(QJoint *qjoint);
public:
    QScene(b2World *world);
    Pointer *pointer; // TODO payload: :p
protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
};

#endif // QSCENE_H
