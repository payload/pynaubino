#ifndef SPAMMER_H
#define SPAMMER_H

#include <QtCore>

class Naubino;

class Spammer : public QTimer
{
    Q_OBJECT
public:
    explicit Spammer(Naubino *naubino);
    virtual ~Spammer();
    Naubino *naubino;
protected:
    virtual void timerEvent(QTimerEvent *e);
signals:
public slots:
};

#endif // SPAMMER_H
