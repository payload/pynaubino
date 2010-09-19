#ifndef SPAMMER_H
#define SPAMMER_H

#include <QTimer>
class Naubino;

class Spammer : public QTimer {
    Q_OBJECT
public:
    Spammer(Naubino &naubino);
protected:
    void timerEvent(QTimerEvent *e);
private:
    Naubino *_naubino;
};

#endif // SPAMMER_H
