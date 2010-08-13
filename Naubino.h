#ifndef NAUBINO_H
#define NAUBINO_H

#include <QtCore>
#include <Box2D.h>

class Naub;

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
    void start();

protected:
    void addNaub();
signals:
    void newNaub(Naub *naub);

public slots:
    void calc();

private:
    void setup();

    void setupWorld();
    b2World *world;

    void setupCalcTimer();
    QTimer *calcTimer;

    void testSetting();

    friend class Naub;
};

#endif // NAUBINO_H
