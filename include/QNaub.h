#ifndef QNAUB_H
#define QNAUB_H


#include "Prereqs.h"

#include <QObject>
#include <QGraphicsObject>
#include <QGraphicsEllipseItem>
#include <QPropertyAnimation>

class Naub;
class Scene;


class QNaub :  public QObject, public QGraphicsItemGroup {
    Q_OBJECT
    Q_PROPERTY(qreal scale READ scale WRITE setScale);
    Q_PROPERTY(qreal contactScale
               READ contactScale
               WRITE setContactScale);
public:
    QNaub(Scene *scene, Naub *naub);
    ~QNaub();

    Naub& naub();
    const Naub& naub() const;
    Scene& scene();
    const Scene& scene() const;

    void handleContact(Naub *other);
    void naubChanged();
    void naubDeleted();

    qreal contactScale() const {
        return _contactItem == NULL ? 0 : _contactItem->scale();
    }
    void setContactScale(qreal contactScale) {
        if (_contactItem != NULL) _contactItem->setScale(contactScale);
    }
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

public slots:
    void naubDeletionAnimationFinished();

private:
    Naub *_naub;
    Scene *_scene;
    QPropertyAnimation *_contactAni;
    int _contactHighlight;

    QGraphicsEllipseItem *_naubItem;
    QGraphicsEllipseItem *_contactItem;
};


#endif // QNau_bH

