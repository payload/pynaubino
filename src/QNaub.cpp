#include "QNaub.h"
#include <Naub.h>
#include <QBrush>

void QNaub::select() {

}

void QNaub::deselect() {

}

void QNaub::update(Naub *naub) {
    setPos(naub->pos().q());
}

void QNaub::remove(Naub *naub) {

}

QNaub::QNaub() : QObject(), QGraphicsEllipseItem() {
    setRect(-15, -15, 30, 30);
    setBrush( Qt::black );
}

QNaub::~QNaub() {

}
