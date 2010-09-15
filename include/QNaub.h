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
public slots:
    void select(Pointer *pointer);
    void deselect(Pointer *pointer);
    void update(Naub *naub);
    void remove(Naub *naub);
public:
    QNaub();
    Pointer *pointer; // TODO payload: :p
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // QNAUB_H
