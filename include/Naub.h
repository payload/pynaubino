#ifndef NAUB_H
#define NAUB_H

#include "Prereqs.h"

#include <QColor>
#include <Box2D/Box2D.h>
#include "Vec.h"

class Naub : public QObject {
    Q_OBJECT
signals:
    void removed(Naub *naub);
    void changed(Naub *naub);
    void joined(Naub *a, Naub *b);
    void merged(Naub *a, Naub *b);
    void selected();
    void deselected();
public slots:
    void select();
    void deselect();
    void contact(Naub *naub);
    void update();
public:
    Naub(b2World *world);
    virtual ~Naub();

    const Vec& pos() const { return _pos; }
    void setPos(const Vec &pos) {
        if (_body != NULL) _body->SetTransform(pos, _body->GetAngle());
        _pos = pos;
    }

    const QColor& color() const { return _color; }
private:
    b2World *_world;
    b2Body *_body;
    Vec _pos;
    QColor _color;
};

#endif // NAUB_H

