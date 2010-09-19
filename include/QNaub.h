#ifndef QNAUB_H
#define QNAUB_H

#include <QObject>
#include <QGraphicsEllipseItem>
class Naub;
class Pointer;

class QNaub : public QObject, public QGraphicsEllipseItem {
    Q_OBJECT
signals:
    void selected(Pointer *pointer);
    void deselected(Pointer *pointer);
    void removed(QNaub *qnaub);
public slots:
    void select(Pointer *pointer);
    void deselect(Pointer *pointer);
    void remove();
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);
public:
    QNaub();
    void setNaub(Naub *naub) { _naub = naub; }
    Pointer *pointer; // TODO payload: :p
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    Naub *_naub;
};

#endif // QNAUB_H
