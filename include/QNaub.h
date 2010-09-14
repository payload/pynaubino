#ifndef QNAUB_H
#define QNAUB_H

#include <QObject>
#include <QGraphicsEllipseItem>

class Naub;

class QNaub : public QObject, public QGraphicsEllipseItem {
    Q_OBJECT
signals:
    void selected();
    void deselected();
public slots:
    void select();
    void deselect();
    void update(Naub *naub);
    void remove(Naub *naub);
public:
    QNaub();
    virtual ~QNaub();
};

#endif // QNAUB_H
