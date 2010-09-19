#ifndef QSCENE_H
#define QSCENE_H

#include <QGraphicsScene>
class QNaub;
class QJoint;
class Pointer;
class b2World;
class QNaubino;

class QScene : public QGraphicsScene {
    Q_OBJECT
public slots:
    void add(QNaub *qnaub);
    void add(QJoint *qjoint);
public:
    QScene(QNaubino *qnaubino);
    virtual ~QScene();
    Pointer *pointer; // TODO payload: :p
protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    QNaubino *_qnaubino;
};

#endif // QSCENE_H
