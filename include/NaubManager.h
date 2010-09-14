#ifndef NAUBMANAGER_H
#define NAUBMANAGER_H

#include "Prereqs.h"

#include <QObject>

class Naub;
class Joint;

class NaubManager : public QObject {
    Q_OBJECT
signals:
    void added(Naub *naub);
    void added(Joint *joint);
    void removed(Naub *naub);
    void joined(Joint *joint);
    void merged(Naub *a, Naub *b);
    void updated();
public slots:
    void add(Naub *naub);
    void remove(Naub *naub);
    void join(Joint *joint);
    void merge(Naub *a, Naub *b);
    void update();
};


#endif // NAUBMANAGER_H

