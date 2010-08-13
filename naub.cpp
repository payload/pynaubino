#include "naub.h"
#include <QDebug>
#include <QBrush>
#include <QEvent>
#include <QGraphicsSceneEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneMoveEvent>

Naub::Naub(qreal x, qreal y, QGraphicsItem *parent) :
    QGraphicsRectItem(x, y, 20, 20, parent)
{
    setBrush(QBrush(Qt::black));
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);
}

void Naub::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    qDebug() << "press" << this->pos();
    QGraphicsItem::mousePressEvent(event);
}

void Naub::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    qDebug() << "move" << this->pos();
    QGraphicsItem::mouseMoveEvent(event);
}

void Naub::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    qDebug() << "release" << this->pos();
    QGraphicsItem::mouseReleaseEvent(event);
}

void Naub::hoverMoveEvent(QGraphicsSceneHoverEvent *event) {
    qDebug() << "hover" << this->pos();
    QGraphicsItem::hoverMoveEvent(event);
}

void Naub::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    qDebug() << "enter" << this->pos();
    QGraphicsItem::hoverEnterEvent(event);
}

void Naub::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    qDebug() << "leave" << this->pos();
    QGraphicsItem::hoverLeaveEvent(event);
}
