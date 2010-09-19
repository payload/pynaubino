#ifndef NAUB_H
#define NAUB_H

#include "Prereqs.h"

#include <QColor>
#include <Box2D/Box2D.h>
#include "Vec.h"
class Joint;
class Pointer;
class Naubino;

class Naub : public QObject {
    Q_OBJECT
signals:
    void added(Joint *joint);

    void selected(Pointer *pointer);
    void deselected(Pointer *pointer);
    void removed(Naub *naub);
    void touched(Naub *a, Naub *b);
    void joined(Naub *a, Naub *b);
    void unjoined(Naub *a, Naub *b);
public slots:
    void select(Pointer *pointer);
    void deselect(Pointer *pointer);
    void remove();
    void touch(Naub *naub);
    void join(Naub *naub);
    void unjoin(Naub *naub);
public:
    Naub();
    void setNaubino(Naubino &naubino);
    void init();
    virtual ~Naub();

    inline const Vec pos() const { return Vec(_body->GetPosition()); }
    void setPos(const Vec &pos);
    inline const QColor& color() const { return _color; }
    inline b2World& world() const { return *_world; }
    inline b2Body& body() const { return *_body; }
    inline QList<Naub*>& joinedNaubs() const { return *_joinedNaubs; }
    inline Naubino& naubino() const { return *_naubino; }
private:
    int bfsDistance(Naub *naub);

    Naubino *_naubino;
    b2World *_world;
    b2Body *_body;
    QColor _color;
    bool _isSelected;
    QList<Naub*> *_joinedNaubs;
};

#endif // NAUB_H

