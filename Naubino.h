#ifndef NAUBINO_H
#define NAUBINO_H

#include <QtCore>
#include <QColor>
#include <Box2D.h>

class Naub;
class Joint;
class Vec;
class Pointer;
class Event;
class Cycler;
class Scorer;

static const float32 FRAMERATE = 1.0f / 30.0f;
static const float32 B2_TIMESTEP = FRAMERATE;
static const int32 B2_VELITERATIONS = 10;
static const int32 B2_POSITERATIONS = 10;

class Naubino : public QObject
{
    Q_OBJECT
public:
    explicit Naubino(QObject *parent = 0);

    QList<Naub *> *naubs;
    b2World *world;
    b2Body *center;
    b2DistanceJointDef *centerJointDef;
    QTimer *calcTimer;
    QList<Pointer *> *pointers;
    QList<Event *> *events;

    Cycler *cycler;
    Scorer *scorer;

    Naub* addNaub(Vec pos, QColor color);
    void deleteNaub(Naub *naub);

    Joint* joinNaubs(Naub *a, Naub *b);
    void unjoinNaubs(Naub *a, Naub *b);
    void unjoinNaubs(Joint *j);

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
    void newNaub(Naub *naub);
    void newJoint(Joint *joint);
    void mergedNaub(Naub *naub);

public slots:
    void calc();
};

#endif // NAUBINO_H
