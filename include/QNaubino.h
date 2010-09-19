#ifndef QNAUBINO_H
#define QNAUBINO_H

#include <QObject>
class Naubino;
class Naub;
class Joint;
class QNaub;
class QJoint;
class QScene;
class QGraphicsView;
class Qb2DebugDrawItem;
class b2World;

class QNaubino : public QObject {
    Q_OBJECT
signals:
    void added(QNaub *qnaub);
    void added(QJoint *qjoint);
public slots:
    void add(Naub *naub);
    void add(Joint *joint);
    void remove(QNaub *obj);
    void remove(QJoint *obj);
public:
    QNaubino(Naubino &naubino, QObject *parent = 0);
    void setNaubino(Naubino &naubino);
    void init();
    QScene *scene;
    QGraphicsView *view;
    Qb2DebugDrawItem *dd;
    b2World& world() const;
private:
    Naubino *_naubino;
};

#endif // QNAUBINO_H
