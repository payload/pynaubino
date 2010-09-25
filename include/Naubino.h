#ifndef NAUBINO_H
#define NAUBINO_H

#include <QObject>
class Simulator;
class Naub;
class Joint;
class b2World;
class b2Body;

class Naubino : public QObject {
    Q_OBJECT
signals:
    void added(Naub *naub);
    void added(Joint *joint);
    void naubOnNaub(Naub *a, Naub *b);
public slots:
    void add(Naub *naub);
    void add(Joint *joint);
private slots:
    void remove(Joint *obj);
    void remove(Naub *obj);
public:
    Naubino(QObject *parent = NULL);
    Simulator *sim;
    b2World& world() const;
    b2Body *center;
};

#endif // NAUBINO_H
