#include "QNaubino.h"
#include <Naubino.h>
#include <Naub.h>
#include <Joint.h>
#include <NaubJoint.h>
#include <QNaub.h>
#include <QJoint.h>
#include <QScene.h>
#include <Qb2DebugDraw.h>
#include <QGraphicsView>
#include <Box2D/Dynamics/b2World.h>
#include <Simulator.h>
#include <QStateMachine>
#include <QState>
#include <QKeyEventTransition>

QNaubino::QNaubino(Naubino &naubino, QObject *parent)
    : QObject(parent), _naubino(&naubino) {
}

void QNaubino::setNaubino(Naubino &naubino) {
    _naubino = &naubino;
}

void QNaubino::init() {
    scene   = new QScene(this);
    view    = new QGraphicsView();
    dd      = new Qb2DebugDrawItem(&world());

    scene->connect(this, SIGNAL(added(QJoint*)), SLOT(add(QJoint*)));
    scene->connect(this, SIGNAL(added(QNaub*)), SLOT(add(QNaub*)));
    scene->connect(_naubino->sim,
                  SIGNAL(timeout()),
                  SLOT(invalidate()));

    connect(_naubino, SIGNAL(added(Joint*)), SLOT(add(Joint*)));
    connect(_naubino, SIGNAL(added(Naub*)), SLOT(add(Naub*)));

    view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    scene->addItem(dd);

    view->setScene(scene);
    view->show();

    initMenu();
}

b2World& QNaubino::world() const {
    return _naubino->world();
}

void QNaubino::add(Naub *naub) {
    QNaub *qnaub = new QNaub();
    qnaub->setNaub(naub);
    qnaub->connect(naub,
                   SIGNAL(removed(Naub*)),
                   SLOT(remove()));
    naub->connect(qnaub,
                  SIGNAL(selected(Pointer*)),
                  SLOT(select(Pointer*)));
    naub->connect(qnaub,
                  SIGNAL(deselected(Pointer*)),
                  SLOT(deselect(Pointer*)));
    connect(qnaub,
            SIGNAL(removed(QNaub*)),
            SLOT(remove(QNaub*)));
    emit added(qnaub);
}

void QNaubino::add(Joint *joint) {
    if (dynamic_cast<NaubJoint*>(joint) == NULL) return;
    QJoint *qjoint = new QJoint();
    qjoint->setJoint(joint);
    qjoint->connect(joint,
                    SIGNAL(removed(Joint*)),
                    SLOT(remove()));
    qjoint->connect(joint,
                    SIGNAL(unjoined(Joint*)),
                    SLOT(remove()));
    connect(qjoint,
            SIGNAL(removed(QJoint*)),
            SLOT(remove(QJoint*)));
    emit added(qjoint);
}

void QNaubino::remove(QNaub *obj) {
    obj->deleteLater();
}

void QNaubino::remove(QJoint *obj) {
    obj->deleteLater();
}

class Menu : public QStateMachine {
public:
    Menu(QNaubino &qnaubino) : _qnaubino(&qnaubino) {}
    QNaubino& qnaubino() const { return *_qnaubino; }
    Naubino& naubino() const { return _qnaubino->naubino(); }
private:
    QNaubino *_qnaubino;
};

class PlayState : public QState {
public:
    PlayState(Menu &parent) : QState(&parent), _menu(&parent) {}
protected:
    void onEntry(QEvent *event) {
        Q_UNUSED(event);
        _menu->naubino().start();
    }
    void onExit(QEvent *event) {
        Q_UNUSED(event);
        _menu->naubino().pause();
    }
private:
    Menu *_menu;
};

void QNaubino::initMenu() {
    Menu *menu = new Menu(*this);

    QState *no_play = new QState(menu);
    QState *play = new PlayState(*menu);

    QState *sf = new QState(no_play);
    QState *start = new QState(sf);
    QState *fail = new QState(sf);

    QState *tutorial = new QState(no_play);
    QState *highscore = new QState(no_play);

    no_play->  addTransition(scene, SIGNAL(play     ()), play);
    play->     addTransition(scene, SIGNAL(highscore()), fail);
    sf->       addTransition(scene, SIGNAL(tutorial ()), tutorial);
    sf->       addTransition(scene, SIGNAL(highscore()), highscore);
    tutorial-> addTransition(scene, SIGNAL(highscore()), highscore);
    highscore->addTransition(scene, SIGNAL(tutorial ()), tutorial);

    no_play->setInitialState(sf);
    sf->     setInitialState(start);
    menu->   setInitialState(no_play);

    menu->start();

    /*
    MenuButton *playBtn = new MenuButton(this);
    MenuButton *highscoreBtn = new MenuButton(this);
    MenuButton *tutorialBtn = new MenuButton(this);

    Vec v(-2.7, -1.7);
    Vec a;
    highscoreBtn->setPos(Vec(v+a).q());
    highscoreBtn->setScale(1.3);
    a = Vec(0.5, 0.0);
    playBtn->setPos(Vec(v+a).q());
    a = Vec(0.25, 0.4);
    tutorialBtn->setPos(Vec(v+a).q());

    connect(playBtn, SIGNAL(click()), SIGNAL(play()));
    connect(highscoreBtn, SIGNAL(click()), SIGNAL(highscore()));
    connect(tutorialBtn, SIGNAL(click()), SIGNAL(tutorial()));

    _scene->addItem(playBtn);
    _scene->addItem(highscoreBtn);
    _scene->addItem(tutorialBtn);


    */
}
