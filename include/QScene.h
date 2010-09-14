#ifndef QSCENE_H
#define QSCENE_H

#include <QGraphicsScene>
class QNaub;

class QScene : public QGraphicsScene {
    Q_OBJECT
public slots:
    void add(QNaub *qnaub);
};

#endif // QSCENE_H
