#ifndef NAUBINO_H
#define NAUBINO_H

#include <QtCore>
#include <QColor>
#include <Box2D.h>

class NaubManager;
class JointManager;

class Naub;
class NaubJoint;
class Vec;
class Pointer;
class Event;
class Cycler;
class Scorer;
class Spammer;
class CenterJoint;

class Naubino : public QObject
{
    Q_OBJECT
public:
    explicit Naubino();

    NaubManager *naubs;
    JointManager *joints;
    b2World *world;
    b2Body *center;
    b2DistanceJointDef *centerJointDef;
    QTimer *calcTimer;
    QList<Pointer *> *pointers;
    QList<Event *> *events;
    QList<b2MouseJoint *> *pointerJoints;
    b2Body *ground_body;

    int timeperframe;

    Cycler *cycler;
    Scorer *scorer;
    Spammer *spammer;

    void friction(Naub &naub);

    void joinWithCenter(Naub *naub);
    void unjoinFromCenter(Naub *naub);

    void mergeNaubs(Naub *a, Naub *b);

    void select(Naub *naub, Pointer *pointer);
    void deselect(Naub *naub, Pointer *pointer);

    void setup();
    void setupWorld();
    void setupCenter();
    void setupCenterJointDef();
    void setupCalcTimer();
    void setupPointers();

    void testSetting();
    void randomPair(Vec pos);
    void start();
    void setColor( QColor color );
signals:
    void mergedNaub(Naub &naub);

public slots:
    void calc();
};

#endif // NAUBINO_H
