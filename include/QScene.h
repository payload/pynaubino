#ifndef QSCENE_H
#define QSCENE_H

#include <QGraphicsScene>
class QNaub;
class Pointer;
class b2World;

class QScene : public QGraphicsScene {
    Q_OBJECT
public slots:
    void add(QNaub *qnaub);
public:
    QScene(b2World *world);
protected:
    Pointer *pointer; // TODO payload: :p
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
};

#endif // QSCENE_H
