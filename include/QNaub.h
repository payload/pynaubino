#ifndef QNAUB_H
#define QNAUB_H


#include "Prereqs.h"

#include <QObject>
#include <QGraphicsEllipseItem>

class Naub;
class Scene;


class QNaub : public QObject, public QGraphicsEllipseItem {
    Q_OBJECT
    Q_PROPERTY(qreal scale READ scale WRITE setScale)
public:
    QNaub(Scene *scene, Naub *naub);
    ~QNaub();

    Naub& naub();
    const Naub& naub() const;
    Scene& scene();
    const Scene& scene() const;

    void naubChanged();
    void naubDeleted();

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

public slots:
    void deleted();

private:
    Naub *_naub;
    Scene *_scene;
};


#endif // QNau_bH

