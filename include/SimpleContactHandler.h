#ifndef SIMPLECONTACTHANDLER_H
#define SIMPLECONTACTHANDLER_H

#include <QObject>
#include <QList>

class Naub;

class NaubOnNaubEvent {
public:
    Naub *a;
    Naub *b;
};

class SimpleContactHandler : public QObject {
    Q_OBJECT
public:
    ~SimpleContactHandler();
public slots:
    void naubOnNaub(Naub *a, Naub *b);
    void handle();
private:
    QList<NaubOnNaubEvent *> _events;
};

#endif // SIMPLECONTACTHANDLER_H
