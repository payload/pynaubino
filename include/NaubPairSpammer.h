#ifndef NAUBPAIRSPAMMER_H
#define NAUBPAIRSPAMMER_H

#include <QTimer>

class Naubino;

class NaubPairSpammer : public QTimer {
    Q_OBJECT
public:
    NaubPairSpammer(Naubino *naubino);
    ~NaubPairSpammer();
protected:
    void timerEvent(QTimerEvent * e);
    Naubino *_naubino;
};

#endif // NAUBPAIRSPAMMER_H
