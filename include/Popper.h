#ifndef POPPER_H
#define POPPER_H

#include <QObject>
#include <QList>

class Naub;
class Naubino;

class Popper : public QObject {
    Q_OBJECT
public:
    Popper(Naubino *naubino);
public slots:
    void popNaubs(QList<Naub*> *naubs);
private:
    Naubino *_naubino;
};

#endif // POPPER_H
