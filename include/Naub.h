#ifndef NAUB_H
#define NAUB_H

#include "Prereqs.h"

#include <QColor>
#include <Box2D/Box2D.h>
#include "Vec.h"

class Naub : public QObject {
    Q_OBJECT
signals:
    void remove(Naub *naub);
    void changed(Naub *naub);
    void join(Naub *a, Naub *b);
    void merge(Naub *a, Naub *b);
    void selected();
    void deselected();
public slots:
    void select();
    void deselect();
    void contact(Naub *naub);
    void update();
public:
    const Vec& pos() const { return _pos; }
    const QColor& color() const { return _color; }
private:
    b2Body *_body;
    Vec _pos;
    QColor _color;
};

#endif // NAUB_H

