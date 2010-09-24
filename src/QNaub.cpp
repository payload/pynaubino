#include "QNaub.h"
#include <Naub.h>
#include <QBrush>

void QNaub::select(Pointer *pointer) {
    emit selected(pointer);
}

void QNaub::deselect(Pointer *pointer) {
    emit deselected(pointer);
}

void QNaub::remove() {
    emit removed(this);
}

void QNaub::paint(QPainter *painter,
                  const QStyleOptionGraphicsItem *option,
                  QWidget *widget) {
    if (_naub == NULL) throw "give me a naub!";
    setPos(_naub->pos().q());
    if (brush().color() != _naub->color())
        setBrush(QBrush( _naub->color() ));
    QGraphicsEllipseItem::paint(painter, option, widget);
}

QNaub::QNaub() : QObject(), QGraphicsEllipseItem() {
    setAcceptHoverEvents(true);
    setAcceptTouchEvents(true);
    setRect(-15, -15, 30, 30);
    setBrush( Qt::black );
    pointer = NULL;
}

void QNaub::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (pointer != NULL) select(pointer);
    QGraphicsEllipseItem::mouseReleaseEvent(event);
}

void QNaub::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if (pointer != NULL) deselect(pointer);
    QGraphicsEllipseItem::mouseReleaseEvent(event);
}
