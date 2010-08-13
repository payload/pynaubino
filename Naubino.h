#ifndef NAUBINO_H
#define NAUBINO_H

#include <QtCore>
#include <Box2D.h>

class QNaub;

static const float32 FRAMERATE = 1.0f / 30.0f;
static const float32 B2_TIMESTEP = FRAMERATE;
static const int32 B2_VELITERATIONS = 10;
static const int32 B2_POSITERATIONS = 10;

class Naubino : public QObject
{
    Q_OBJECT
public:
    explicit Naubino(QObject *parent = 0);
    void start();

signals:
    void newQNaub(QNaub *naub);

public slots:

private:
    void setupCalcTimer();
    void calc();
    QTimer *calcTimer;
};

#endif // NAUBINO_H
