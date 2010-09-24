#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <QList>
#include <QTimer>
class b2World;
class ContactListener;
class Naub;
class Contact;

class Simulator : public QTimer {
    Q_OBJECT
signals:
    void naubOnNaub(Naub *a, Naub *b);
private slots:
    void contact(Naub *a, Naub *b);
public:
    Simulator(QObject *parent = 0);
    virtual ~Simulator();

    b2World& world() const { return *_world; }
protected:
    virtual void timerEvent(QTimerEvent *e);
private:
    b2World *_world;
    ContactListener *_contacts;
    QList<Contact*> *_contact_list;
};

#endif // SIMULATOR_H
