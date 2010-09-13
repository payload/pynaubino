#ifndef MENU_H
#define MENU_H

#include <QStateMachine>
#include <QObject>
#include <QGraphicsObject>

class Scene;

class MenuButton : public QObject, public QGraphicsItemGroup {
    Q_OBJECT
public:
    MenuButton(QObject *parent = 0);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
signals:
    void click();
};

class Menu : public QStateMachine {
    Q_OBJECT
public:
    Menu(Scene *scene);
signals:
    void play();
    void highscore();
    void tutorial();
private:
    Scene *_scene;
};

#endif // MENU_H
