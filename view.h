#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>

class Scene;

class View : public QGraphicsView
{
    Q_OBJECT
public:
    explicit View(Scene *scene, QWidget *parent = 0);
signals:

public slots:

};

#endif // VIEW_H
