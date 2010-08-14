#ifndef NAUBINO_H
#define NAUBINO_H

#include <QtCore>
#include <Box2D.h>

class Naub;
class Joint;
class Vec;

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
    QList<Joint *> *joints;
    void start();

protected:
    Naub* addNaub(Vec pos);
    Joint* joinNaubs(Naub *a, Naub *b);
    void joinWithCenter(Naub *naub);
    void randomPair(Vec pos);
signals:
    void newNaub(Naub *naub);
    void newJoint(Joint *joint);

public slots:
    void calc();

private:
    void setup();

    void setupWorld();
    b2World *world;

    void setupCenter();
    b2Body *center;
    void setupCenterJointDef();
    b2DistanceJointDef *centerJointDef;

    void setupCalcTimer();
    QTimer *calcTimer;

    void testSetting();

    friend class Naub;
    friend class Joint;
};

#endif // NAUBINO_H
