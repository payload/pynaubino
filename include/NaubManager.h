#ifndef NAUBMANAGER_H
#define NAUBMANAGER_H

#include <QtCore>
#include "Color.h"
#include "Vec.h"
#include "Naub.h"

class NaubManager : public QObject
{
    Q_OBJECT
public:
    explicit NaubManager();
    ~NaubManager();

    Naub& add(Vec pos);
    Naub& add(Vec pos, Color color);
    void remove(Naub &naub);

    int count();
    void update();

signals:
    void newNaub(Naub &naub);
public slots:

private:
    QList<Naub *> *naubs_;
};

#endif // NAUBMANAGER_H
