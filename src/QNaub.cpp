#include "QNaub.h"
#include <Naub.h>
#include <QBrush>

void QNaub::select(Pointer *pointer) {
    emit selected(pointer);
}

void QNaub::deselect(Pointer *pointer) {
    emit deselected(pointer);
}

void QNaub::update(Naub *naub) {
    setPos(naub->pos().q());
}

void QNaub::remove(Naub *naub) {
    Q_UNUSED(naub);
}

QNaub::QNaub() : QObject(), QGraphicsEllipseItem() {
    setAcceptHoverEvents(true);
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
