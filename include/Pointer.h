#ifndef POINTER_H
#define POINTER_H

#include <QObject>
class b2Body;
class b2World;
class Vec;

class Pointer : public QObject {
    Q_OBJECT
public slots:
    void setPos(const Vec &pos);
public:
    Pointer(b2World &world, QObject *parent = 0);

    b2Body& body() const { return *_body; }
private:
    b2Body *_body;
    b2World *_world;
};

#endif // POINTER_H
