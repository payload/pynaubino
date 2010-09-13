#include "Menu.h"
#include <Scene.h>

#include <Vec.h>

MenuButton::MenuButton(QObject *parent)
    : QObject(parent), QGraphicsItemGroup() {
    QGraphicsEllipseItem *item = new QGraphicsEllipseItem(this);
    addToGroup(item);
    item->setRect(-15, -15, 30, 30);
    item->setBrush(QBrush( Qt::black ));
}

void MenuButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    Q_UNUSED(event);
    emit click();
}

Menu::Menu(Scene *scene) : QStateMachine(), _scene(scene) {

    QState *no_play = new QState(this);
    QState *play = new QState(this);

    QState *sf = new QState(no_play);
    QState *start = new QState(sf);
    QState *fail = new QState(sf);

    QState *tutorial = new QState(no_play);
    QState *highscore = new QState(no_play);

    no_play->addTransition(this, SIGNAL(play()), play);
    play->addTransition(this, SIGNAL(highscore()), fail);
    sf->addTransition(this, SIGNAL(tutorial()), tutorial);
    sf->addTransition(this, SIGNAL(highscore()), highscore);
    tutorial->addTransition(this, SIGNAL(highscore()), highscore);
    highscore->addTransition(this, SIGNAL(tutorial()), tutorial);

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

    no_play->setInitialState(sf);
    sf->setInitialState(start);
    setInitialState(no_play);
}
