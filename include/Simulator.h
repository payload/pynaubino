#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <QTimer>
class b2World;

class Simulator : public QTimer {
    Q_OBJECT
public:
    Simulator(QObject *parent = 0);
    virtual ~Simulator();

    b2World& world() const { return *_world; }
protected:
    virtual void timerEvent(QTimerEvent *e);
private:
    b2World *_world;
};

#endif // SIMULATOR_H
