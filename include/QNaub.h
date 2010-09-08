#ifndef QNAUB_H
#define QNAUB_H


#include "Prereqs.h"

#include <QObject>
#include <QGraphicsEllipseItem>
#include <QPropertyAnimation>

class Naub;
class Scene;


class QNaub : public QObject, public QGraphicsEllipseItem {
    Q_OBJECT
    Q_PROPERTY(qreal scale READ scale WRITE setScale);
    Q_PROPERTY(bool _contactHighlight
               READ contactHighlight
               WRITE setContactHighlight);
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

    bool contactHighlight() const { return _contactHighlight; }
    void setContactHighlight(bool contactHighlight) {
        _contactHighlight = contactHighlight;
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
    bool _contactHighlight;
};


#endif // QNau_bH

